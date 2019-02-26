// This program is a part of NITAN MudLIB
// bunchd.c
/*
【幫派榮譽點的功能】
幫派榮譽點是一種消耗點數，僅通過特殊活動獲取。通過bunch指令可以隨時查
詢本幫派的榮譽點數。幫主可通過消耗榮譽點數換取以下特殊功能之一：

幫派榮譽點可以通過 group quest 獲得

全幫雙倍經驗2小時，消耗X點幫派榮譽點。
全幫雙倍潛能2小時，消耗X點幫派榮譽點。
全幫雙倍體會2小時，消耗X點幫派榮譽點。
全幫研究效率增加20%持續3小時，消耗X點幫派榮譽點。
全幫汲取效率增加20%持續3小時，消耗X點幫派榮譽點。
全幫冥思效率增加20%持續3小時，消耗X點幫派榮譽點。
*/

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// 幫派聲望最大是10億
#define MAX_BUNCH_FAME         1000000000

// 每個幫派最多有100個仇人
#define MAX_HATRED_PERSON       100

// 當仇人超過的時候每次移除多少個
#define HATREDP_REMOVED         10
#define BUNCH_HOME              "/data/bunch/"
#define RM_CMD                  "/cmds/wiz/rm"
#define CP_CMD                  "/cmds/wiz/cp"

mapping bunch_fame;
mapping last_bunch_fame;

// area's base_name & short
mapping area_fame;

// 幫派對仇人仇恨度的排序
private int sort_hatred(string id1, string id2, mapping hatred);
public mixed manage_areas();
public void dismiss_bunch(string fname);
public mixed query_all_areas() { return area_fame; }
public int end_bunch_war(string wname, string lname, int gold);
public int war_stop_time(string fname);
public int bunch_is_league(mixed ob1, mixed ob2);
void add_bunch_honors(string bname, int honors);

nosave string *npc_bunch = ({
        "黑白道",
        "修羅門",
        "小刀會",
        "俠義盟",
        "無極幫",
        "紫衫會",
});

nosave string *bad_weather = ({
        "受乾旱的影響，$N虧空",
        "由於暴雨襲擊，$N收成跌了",
        "$N遭到了倭寇的襲擊，被劫",
        "官府加重對$N的徵税，$N虧空",
        "疾病在$N肆虐，損失慘重",
        "龍捲風襲捲了$N，結果造成巨大損失",
        "$N發生暴動，人員傷亡慘重，損失",
        "$N突發地震，人員傷亡慘重，花費巨大",
});

nosave mapping citys = ([
        "bj"  : "北京城",
        "yz"  : "揚州城",
        "ca"  : "長安城",
        "cd"  : "成都城",
        "sz"  : "蘇州城",
        "hz"  : "杭州城",
        "xy"  : "襄陽城",
        "dl"  : "大理城",
]);

// start
#define BATTLE_TIME             1800
#define BATTLE_JOIN_TIME        300
#define LEAVE_ROOM              "/d/city/wumiao"

int battle_times = 0;
nosave int battle_open_flag = 0;
nosave int battle_start_flag = 0;
nosave int battle_time_countdown = 0;
nosave int battle_start_time = 0;

nosave object *total = ({});
mixed *bunch_topten = ({});

int check_out(object me);

int is_battle_open()
{
        return battle_open_flag;
}

int is_battle_start()
{
        return battle_start_flag;
}

void topten_bunch_add(string bunch_name)
{
        int n;
        string t;

        ++battle_times;
        bunch_topten += ({
                ([
                        "bunch_name" :  bunch_name,
                        "time"       :  time(),
                ]),
        });

        save();
}
// 返回最近第幾場取勝的幫派名稱
string query_bunch_topten(int n)
{
        mapping data;

        if( !sizeof(bunch_topten) ) return "精意山莊";
        data = bunch_topten[sizeof(bunch_topten)-n];
        return data["bunch_name"];
}

int is_top_bunch(object me)
{
        string bname;

        if( !(bname = query("bunch/bunch_name", me)) )
                return 0;

        return bname == query_bunch_topten(1);
}

void restore_status(object me)
{
        mapping my, cnd;
        string *ks;
        string where;
        int i;

        me->delete_override("unconcious");
        me->delete_override("die");
        me->delete_override("quit");
        delete_temp("override/receive_damage", me);
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->clear_condition();
        me->receive_damage("qi", 0);
        me->apply_killer(query_temp("backup/killer", me));
        me->apply_want(query_temp("backup/want", me));

        cnd=query("backup/condition", me);
        delete("backup/condition", me);
        delete_temp("block_msg/all", me);
        delete_temp("in_pkd", me);

        my = me->query_entire_dbase();
        if( my["qi"] < 1 )       my["qi"] = 1;
        if( my["eff_qi"] < 1 )   my["eff_qi"] = 1;
        if( my["jing"] < 1 )     my["jing"] = 1;
        if( my["eff_jing"] < 1 ) my["eff_jing"] = 1;

        if( stringp(where = query_temp("battle/leave_room", me)) )
                me->move(where);
        else
                me->move(LEAVE_ROOM);

        delete_temp("battle", me);

        if( !mapp(cnd) ) return;
        ks = keys(cnd);
        for( i = 0; i < sizeof(ks); i++ )
            me->apply_condition(ks[i], cnd[ks[i]]);
}

void init_player(object me)
{
        int i;
        object *obs;

        tell_object(me, HIY "你眼前忽然一花...\n" NOR);
        me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
        me->set_override("die", (: call_other, __FILE__, "check_out" :));
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        //set_temp("override/receive_damage", (:call_other,__FILE__,"receive_damage":), me);
        set_temp("backup/killer", me->query_killer(), me);
        set_temp("backup/want", me->query_want(), me);
        set_temp("in_pkd", 1, me);

        set("backup/condition", me->query_condition(), me);
        me->clear_condition();

        obs = all_inventory(me);
        for( i=0; i<sizeof(obs); i++ )
        {
                if( query("id", obs[i]) == "mian ju" )
                        obs[i]->move();
        }

        if( !arrayp(total) )
                total = ({ me });
        else
        if( member_array(me, total) == -1 )
                total += ({ me });

        me->move("/maze/binghuodao/haitan"+(1+random(2)));
}

// 參與戰爭
void join_battle(object me)
{
        string where;
        mapping cnd;
        string id = me->query_id(1);

        /*
        if( battle_start_flag )
                return tell_object(me, "戰場已經開啟，報名終止。\n");
        */

        if( me->is_busy() )
                return tell_object(me, BUSY_MESSAGE);

        if( me->is_fighting() )
                return tell_object(me, "你目前正在戰鬥中，還是先處理目前的對手再説吧。\n");

        if( me->query_condition("killer") )
                return tell_object(me, "官府正在通緝你，你還敢在這兒拋頭露面？\n");

        if( !battle_open_flag )
                return tell_object(me, "戰爭沒有發出集結，目前無法報名。\n");

        if( me->is_ghost() )
                return tell_object(me, "等你還陽後，再報名吧。\n");

        init_player(me);

        CHANNEL_D->channel_broadcast("war", "目前共有 "+sizeof(total)+
                                            " 位玩家報名參與"HIY"第"HIG+chinese_number(battle_times+1)+HIY"屆幫派爭奪戰。"NOR);

}

void stop_battle()
{
        object ob;
        object player;

        set_heart_beat(0);

        foreach( ob in total )
        {
                if( !objectp(ob) )
                        continue;

                //ob->remove_all_killer();
                ob->remove_all_enemy(1);
                restore_status(ob);
                tell_object(ob, "你被傳離戰場...\n");
        }

        total = allocate(0);
        battle_open_flag = 0;
        battle_start_flag = 0;
        battle_time_countdown = 0;
}

public void win_battle(object me, string bunch_name)
{
        stop_battle();

        CHANNEL_D->channel_broadcast("news", HIY + "恭喜幫派【" + bunch_name + "】獲得了第" + HIG +
                              chinese_number(battle_times+1) + HIY "屆幫派爭奪戰的勝利！\n" NOR);
        CHANNEL_D->channel_broadcast("news", HIY + "本屆幫派爭奪戰中，" + me->name() + HIY + "(" + me->query_id(1) +
                              ")居功至偉，獲得了豐厚的獎勵！\n" NOR);
        CHANNEL_D->channel_broadcast("news", HIY + "幫派" + bunch_name + "所有人員在接下來二十四小時內擁有冰火島歷練獨家所有權！\n" NOR);

        tell_object(me, HIY "你在本屆幫戰中成為最後的奪旗者，獲得了二百萬經驗、二百萬潛能和二百萬實戰體會獎勵！\n" NOR);
        addn("combat_exp", 2000000, me);
        addn("potential", 2000000, me);
        addn("experience", 2000000, me);

        topten_bunch_add(bunch_name);
        add_bunch_honors(bunch_name, 1000);
        set_heart_beat(1800 + random(30));
}

// 某戰場開始接受報名 TIME_D 調用
void start_join()
{
        CHANNEL_D->channel_broadcast("war", HIY"榮耀"NOR YEL"之戰"HIR"發出戰爭集結，即將在 "+(BATTLE_JOIN_TIME/60)+
                                            " 分鐘後發動"HIY"第"HIG+chinese_number(battle_times+1)+HIY"屆幫派爭奪戰，"HIR"請準備加入戰役(help bunch_war)。\n"NOR);

        total = ({});
        battle_open_flag = 1;

        battle_start_time = BATTLE_JOIN_TIME;

        set_heart_beat(1);

        //tell_object(users(), "\a");
}

void start_battle()
{
        object *all_player = ({});
        object ob;
        object player;
        string where;
        int i;

        if( sizeof(total) < 5 )
        {
                set_heart_beat(1800);
                total = allocate(0);
                battle_open_flag = 0;
                battle_start_time = 0;
                CHANNEL_D->channel_broadcast("war", "報名參與"HIY"第"HIG+chinese_number(battle_times+1)+HIY"屆幫派爭奪戰"HIR"的玩家不足 5 人，取消本次戰役。");
                return;
        }

        CHANNEL_D->channel_broadcast("war", "開始出征！共計 "+sizeof(total)+
                                            " 位玩家參與"HIY"第"HIG+chinese_number(battle_times+1)+HIY"屆幫派爭奪戰，"HIR"計時 "+(BATTLE_TIME/60)+" 分鐘結束。");

        ob = new("/maze/binghuodao/npc/xiexun");
        ob->move("/maze/binghuodao/jitan");

        battle_start_flag = 1;
        battle_time_countdown = BATTLE_TIME;
}

public int query_bunch_battle(object me)
{
        string str;
        int i,n,t;

        str = "";

        str += HIG "\n當前天下第一幫：" + HIY + query_bunch_topten(1) + NOR;
        str += HIG "\n當前幫戰的狀態：";
        str += battle_start_flag ? HIR "當前幫戰進行中。" NOR : (battle_start_time > 0 ? HIY "幫戰準備中，即將開始。" NOR :"當前幫戰未進行。");
        str += "\n";
        str += battle_start_flag ? HIR "當前幫戰還剩餘" + time_period(battle_time_countdown) + "結束。" NOR : "";
        str += "\n";

        str += HIG "\n最近十屆幫派爭奪戰獲勝幫派：\n" NOR;
        str += sprintf("%-15s%-15s%-40s\n", "屆數", "幫派", "勝利日期");
        str += "----------------------------------------------------------\n";

        if( n = sizeof(bunch_topten) )
        {
                // 顯示最近10屆
                if( n > 10 )
                        t = n - 10;
                else
                        t = 0;

                for( i = t; i < n; i ++ )
                {
                        if( me->query_bunch() == bunch_topten[i]["bunch_name"] )
                        {
                                str += sprintf(HIG "%-15d%-15s%-40s\n" NOR,
                                                i + 1,
                                                bunch_topten[i]["bunch_name"],
                                                TIME_D->replace_ctime(atoi(bunch_topten[i]["time"])));
                        }
                        else
                        {
                                str += sprintf("%-15d%-15s%-40s\n",
                                                i + 1,
                                                bunch_topten[i]["bunch_name"],
                                                TIME_D->replace_ctime(atoi(bunch_topten[i]["time"])));
                        }
                }
        }
        str += "----------------------------------------------------------\n";
        str+= HIG "綠色代表你當前所在幫派。\n" NOR;
        tell_object(me, str);
        return 1;
}

void auto_check()
{
        object ob;
        string msg;
        string room;
        object *lost;
        int i;

        lost = ({ });
        for (i = 0; i < sizeof(total); i++)
        {
                if( !objectp(total[i]))
                        continue;
                room = base_name(environment(total[i]));
                if( !sscanf(room, "/maze/binghuodao%*s") )
                {
                        // not in pk room
                        restore_status(total[i]);
                        total[i] = 0;
                        continue;
                }
                if( query("qi", total[i])<1 || query("jing", total[i])<1 )
                        lost += ({ total[i] });
        }

        foreach (ob in lost)
                check_out(ob);

        total -= ({ 0 });
}

int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        string room;

        room = base_name(environment(me));
        if( !sscanf(room, "/maze/binghuodao%*s") )
        {
                // not in battle room
                total -= ({ me });
                return 0;
        }

        my = me->query_entire_dbase();
        my["eff_qi"] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["qi"] = 1;
        my["jing"] = 1;

        tell_object(me, HIR "\n你覺得眼前一陣模糊...這下完了！\n" NOR);
        if( ob = me->query_last_damage_from() )
        {
                msg = me->name(1) + "慘遭" + ob->name(1) + "的毒手，被無情ＰＫ。";
        } else
                 msg = me->name(1) + "運氣不佳，本領有限、已經慘遭ＰＫ。";

        message("vision", msg, environment(me), ({ me }));

        restore_status(me);
        total -= ({ me });

        message("vision", "一個黑影倏的竄了出來，隨即就是“啪”的"
                "一聲，就見" + me->name() +"摔倒了地上，一副半死不"
                "活的樣子。\n", environment(me), ({ me }));
        tell_object(me, "半昏半迷中，你覺得被人拎了起來，又"
                "重重的摔倒了地上。\n");

        if( !living(me) )
                me->revive();

        return 1;
}
// end

void create()
{
        mapping data;

        seteuid(getuid());
        set("channel_id", HIY "幫派通告" NOR);
        restore();
        set_heart_beat(1800);
        // 轉移到timed.c中調用
        //SCHEDULE_D->set_event(7200, 1, this_object(), "manage_areas");

        if (! mapp(bunch_fame)) bunch_fame = ([ ]);
        if (! mapp(area_fame)) area_fame = ([ ]);
}

void remove()
{
        save();
}
// 要在 CMDS:REBOOT 裏面加上調用
public void mud_shutdown()
{
        save();
}

// 心跳：維護幫派的通常信息
void heart_beat()
{
        int t;
        int last;
        string *all_fam;
        string fam;

        t = time();
        last = query("last_check");
        if ((t / 86400) != (last / 86400))
        {
                // 天數發生了變化：複製幫派的名望信息
                all_fam = keys(bunch_fame) - ({ 0 });
                last_bunch_fame = ([ ]);

                foreach (fam in all_fam)
                        last_bunch_fame[fam] = bunch_fame[fam];
        }
        set("last_check", t);
        /*
        all_fam = keys(bunch_fame) - ({ 0 });
        foreach (fam in all_fam)
        {
                if (query(fam + "/war_endtime") &&
                    time() > query(fam + "/war_endtime"))
                        war_stop_time(fam);
        }
        */

        if( battle_start_time > 0 )
        {
                switch(--battle_start_time)
                {
                        case 0:
                                start_battle();
                                break;
                        case 60:
                        case 120:
                        case 180:
                        case 300:
                        case 600:
                        case 900:
                                CHANNEL_D->channel_broadcast("war", HIY"榮耀"NOR YEL"之戰"HIR"發出戰爭集結，即將在 "+(battle_start_time/60)+
                                            " 分鐘後發動"HIY"第"HIG+chinese_number(battle_times+1)+HIY"屆幫派爭奪戰，"HIR"請準備加入戰役(help bunch_war)。"NOR);
                                break;
                }

                return;
        }

        if( !battle_start_flag )
                return;

        if( --battle_time_countdown <= 0 )
        {
                CHANNEL_D->do_channel(this_object(), "news", HIM "很遺憾，本屆天下第一幫爭奪戰在由於超時而結束了!\n" NOR);
                stop_battle();
                return;
        }

        if( sizeof(total) )
                auto_check();

        if( battle_time_countdown == 60 || battle_time_countdown == 180 )
                CHANNEL_D->channel_broadcast("war", HIR"戰"NOR RED"爭"HIR"："+HIY"第"HIG+chinese_number(battle_times+1)+
                                                    HIY"屆幫派爭奪戰"HIR"即將在 "+(battle_time_countdown/60)+" 分鐘後結束..."NOR);
}

public mixed manage_areas()
{
        string  bunch_name, bad_area, *item, *all_area,
                *all_bunch, *lost, str;
        object  room, player, npc;
        int     weiwang, jizhi, kaifa, zhongcheng, count, i;
        int     area_money, bad_money, rest_money, npc_money, cost;
        mapping data = ([ ]);

        all_area = keys(area_fame) - ({ 0 });

        if (! arrayp(all_area) || ! sizeof(all_area))
                return;

        if (random(sizeof(all_area)) > 10)
        {
                bad_area = all_area[random(sizeof(all_area))];

                if (undefinedp(area_fame[bad_area]["ziyuan"]))
                        bad_area = "";
        }
        else
                bad_area = "";

        foreach (string area in all_area)
        {
                reset_eval_cost();

                bunch_name = area_fame[area]["bunch_name"];

                if (bunch_name == "獨立中")
                        continue;

                if (! (room = get_object(area)))
                        continue;

                // 盤點時候幫派 NPC 不在時候則無收入
                if (undefinedp(area_fame[area]["npc_id"]) ||
                    ! objectp(npc = present(area_fame[area]["npc_id"], room)))
                        continue;

                if (! mapp(query(bunch_name)))
                {
                        message("channel:rumor", HIM"【泥潭幫會】由於幫派瓦解，" +
                                query("short", room)+"宣佈脱離幫會"+"「"+bunch_name+
                                "」" + "的控制！\n" NOR, users());

                        delete("bunch", npc);
                        area_fame[area]["bunch_name"] = "獨立中";
                        continue;
                }

                if (area_fame[area]["money"] < -1000000 ||
                    query(bunch_name + "/money") < -100000000)
                {
                        message("channel:rumor", HIM"【泥潭幫會】由於經營不善，" +
                                query("short", room)+"宣佈脱離幫會"+"「"+bunch_name+
                                "」" + "的控制！\n" NOR, users());

                        // 調整幫派威望
                        weiwang = bunch_fame[bunch_name];
                        weiwang -= 1000;
                        if (weiwang < 0) weiwang = 0;
                        bunch_fame[bunch_name] = weiwang;

                        delete("bunch", npc);
                        area_fame[area]["bunch_name"] = "獨立中";
                        continue;
                }

                zhongcheng = area_fame[area]["zhongcheng"];
                if (! intp(zhongcheng) || zhongcheng < 10)
                        zhongcheng = 10;

                zhongcheng -= random(2);

                if (zhongcheng >= 100)
                        zhongcheng = 100;

                set("bunch/zhongcheng", zhongcheng<10?10:zhongcheng, npc);
                area_fame[area]["zhongcheng"] = (zhongcheng < 10 ? 10 : zhongcheng);

                jizhi = area_fame[area]["jizhi"];
                kaifa = area_fame[area]["kaifa"];
                jizhi += random(2);
                kaifa -= random(2);

                area_money = area_fame[area]["money"];
                if (! stringp(area_money) && ! intp(area_money))
                        area_money = 0;

                if (! intp(jizhi) || jizhi < 6)
                        jizhi = 6;
                else if (jizhi > 60)
                        jizhi = 60;

                if (! intp(kaifa) || kaifa < 20)
                        kaifa = 20;
                else if (kaifa > 100)
                        kaifa = 100;

                area_fame[area]["kaifa"] = kaifa;
                area_fame[area]["jizhi"] = jizhi;

                if (area == bad_area)
                {
                        if (jizhi && kaifa < 80)
                        {
                                bad_money = kaifa * jizhi * 10000;
                                area_money -= bad_money;
                        } else
                        { // 開發度高的，一般來説自然災害影響不大
                                bad_area = "";
                                area_money += (kaifa / 2) * (jizhi / 2) * 1000;
                        }
                } else
                        area_money += (kaifa / 2) * (jizhi / 2) * 2000;

                rest_money = area_money - 1000000;
                if (rest_money < 0)
                        rest_money = 0;

                area_fame[area]["money"] = area_money - rest_money;
                area_fame[area]["last_money"] = rest_money;

                data[bunch_name] += rest_money;
        }

        all_bunch = keys(bunch_fame);

        if (! arrayp(all_bunch) || ! sizeof(all_bunch))
                return;

        lost = ({ });
        foreach (string bunch in all_bunch)
        {
                reset_eval_cost();

                npc_money = query(bunch + "/npc_money");
                set(bunch + "/last_npc_money", npc_money);
                set(bunch + "/npc_money", 0);

                set(bunch + "/last_area_money", data[bunch]);

                data[bunch] += npc_money;
                if (data[bunch] < 0) data[bunch] = 0;

                data[bunch] /= 2;

#ifndef LONELY_IMPROVED
                if (query(bunch + "/money") < 2000000000)
#endif
                        addn(bunch + "/money", data[bunch]);

                cost = 200 * (sizeof(BUNCH_D->query_bunch_areas(bunch)) * 2 +
                              sizeof(query(bunch + "/member")));

                addn(bunch + "/money", -cost);
                data[bunch] /= 2;

                addn(bunch + "/bangzhu_money", data[bunch]);
                set(bunch + "/last_bangzhu_money", data[bunch]);

                if (query(bunch + "/money") < -100000000)
                {
                        message("channel:rumor", HIW "【泥潭幫會】由於幫派資產長期嚴重虧損，幫會「" +
                                                 bunch + "」無法維持日常開支，土崩瓦解了！\n" NOR, users());
                        lost += ({ bunch });
                        map_delete(data, bunch);
                }
        }

        if (arrayp(lost) && sizeof(lost) > 0)
        {
                foreach (bunch_name in lost)
                        dismiss_bunch(bunch_name);
        }
        lost = ({ });

        if (! arrayp(users()) || ! sizeof(users()))
                return;

        // give all online player banghui's money
        item = keys(data);

        for (i = 0; i < sizeof(item); i++)
        {
                reset_eval_cost();

                count = 0;

                foreach (player in users())
                {
                        reset_eval_cost();

                        if (! playerp(player)) continue;

                        if( !query("bunch/bunch_name", player) ||
                            query("bunch/bunch_name", player) != item[i] )
                                continue;

                        count++;
                }

                if (count == 0) count = 1;
                data[item[i]] /= count;
        }

        foreach (player in users())
        {
                reset_eval_cost();

                if (! playerp(player)) continue;

                if( !query("bunch/bunch_name", player))continue;

                if( !data[query("bunch/bunch_name", player)])continue;

                tell_object(player,HIG"幫派「"+query("bunch/bunch_name", player)+"」"+"發餉，你的存款增加了"+
                                    MONEY_D->money_str(data[query("bunch/bunch_name", player)])+"！\n"NOR);

#ifndef LONELY_IMPROVED
                if( query("balance", player)>2000000000 )
                        tell_object(player, RED "你在錢莊的錢已達到二十萬兩黃金，快點花吧！\n" NOR);
                else
#endif
                        addn("balance", data[player->query("bunch/bunch_name")], player);
        }

        if (bad_area == "")
                message("channel:rumor", HIM "【幫派】某人：各地盤收入良好，請各位幫主速來錢莊轉帳！\n" NOR,
                        users());
        else
        {
                str = bad_weather[random(sizeof(bad_weather))];
                str = replace_string(str, "$N", bad_area);

                message("channel:rumor", HIM "【幫派】某人：" + str +
                                         MONEY_D->money_str(bad_money) + "！\n" NOR, users());
        }
        save();
}

// 返回幫派聲望：如果參數為空，返回mapping類型，包含了所有同
// 盟的聲望；如果參數是人物， 則返回該人物所在的那個幫派的聲
// 望；如果參數是幫派，則返回該幫派的聲望。
public mixed query_bunch_fame(mixed ob)
{
        string fname;

        if (stringp(ob))
                return bunch_fame[ob];

        if (objectp(ob))
        {
                if( stringp(fname=query("bunch/bunch_name", ob)) )
                        return bunch_fame[fname];
                else
                        return 0;
        }

        return bunch_fame;
}

// 查詢昨天的幫派名望信息
public mapping query_all_last_bunch_fame()
{
        if (! mapp(last_bunch_fame))
                // 沒有昨天的信息，返回今天的
                return bunch_fame;

        // 返回昨天的幫派聲望信息
        return last_bunch_fame;
}

// 查詢幫派的仇恨信息：輸入的ob可以是幫派的名字，也可是
// 中的人物。
public mapping query_bunch_hatred(mixed ob)
{
        mapping hatred;
        string fname;

        if (objectp(ob))
                fname=query("bunch/bunch_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! mapp(hatred = query(fname + "/hatred")))
                return 0;

        return hatred;
}

// 變化幫派聲望：輸入的ob可以是幫派的名字，也可是幫派中的人物。
public void add_bunch_fame(mixed ob, int n)
{
        int new_fame;
        string fname;

        if (objectp(ob))
                fname=query("bunch/bunch_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || undefinedp(query(fname + "/member")))
                return;

        // 計算新的幫派聲望
        new_fame = bunch_fame[fname] + n;
        if (new_fame < 0) new_fame = 0;
        if (new_fame > MAX_BUNCH_FAME)
                new_fame = MAX_BUNCH_FAME;
        bunch_fame[fname] = new_fame;
}

// 幫派間仇殺
public void bunch_kill(object killer, object victim)
{
        int kexp;
        int vexp;
        string vfam;
        string kfam;
        string kid;
        int fame_delta;
        mapping hatred;
        mixed *d;

        // 只有玩家之間的仇殺才計算在內
        if (! objectp(killer) || ! playerp(killer) ||
            ! objectp(victim) || ! playerp(victim))
                return;

        // 巫師之間的比劃可不能算數
        if (wizardp(killer) || wizardp(victim))
                return;

        // 查看這兩個玩家所處的幫派
        kfam=query("bunch/bunch_name", killer);
        vfam=query("bunch/bunch_name", victim);

        if (! stringp(kfam) && ! stringp(vfam))
                // 都不在幫派內，不必繼續了
                return;

        kexp=query("combat_exp", killer);
        vexp=query("combat_exp", victim);

        if (kfam == vfam)
        {
                if( !killer->is_killing(query("id", victim)) )
                        // 失手所殺，不予理會
                        return;

                // 幫派內殘殺？不與理會，直接扣除幫派和個人1/10威望。
                add_bunch_fame(kfam, -bunch_fame[kfam] / 10);
                addn("weiwang", -query("weiwang", killer)/10, killer);
                return;
        } else
        if (bunch_is_league(kfam, vfam))
        {
                if( !killer->is_killing(query("id", victim)) )
                        // 失手所殺，不予理會
                        return;
                // 同盟幫派內殘殺？直接扣除幫派和個人1/20威望。
                add_bunch_fame(kfam, -bunch_fame[kfam] / 20);
                addn("weiwang", -query("weiwang", killer)/20, killer);
                return;
        }

        if (kexp < vexp*3 && vexp >= 100000)
        {
                // 殺手的經驗不是遠遠的大於對方，並且被殺的
                // 人有一定的經驗，這將導致幫派聲望的降低。
                fame_delta=vexp+query("score", killer)*2+
                             query("weiwang", killer)*10;
                fame_delta /= 1000;
        } else
                // 對手經驗太少，或是差距太大，不影響聲望
                fame_delta = 0;

        // 查看殺手所在的幫派是否仇恨死者：如果仇恨，則能夠
        // 帶動聲望的變化。
        if (stringp(kfam))
        {
                string path;

                path=kfam+"/hatred/"+query("id", victim);
                d = query(path);
                if (arrayp(d) && sizeof(d) >= 2 && intp(d[1]))
                {
                        // 仇恨死者，幫派獲得額外的聲望
                        if (d[1] > 2000)
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        "聽説" + killer->name(1) + "擊斃了" +
                                        victim->name(1) + "，為" +
                                        kfam + "出了一口惡氣。");
                        fame_delta += d[1] / 3;

                        // 對此人的仇恨降低(降低的要比增加的要多)，
                        // 具體可以看fame_delta 與仇恨度公司的差異
                        d[1] -= fame_delta;
                        if (d[1] <= 0)
                                delete(path);
                        else
                                set(path, d);
                }
        }

        // 調整兩個幫派的聲望
        add_bunch_fame(killer,  fame_delta);
        add_bunch_fame(victim, -fame_delta);

        // 統計該殺手對本門的殘害程度
        if (! stringp(vfam))
                return;

        // 仇恨程度和聲望的變化都是在一個數量級上(K經驗)，但
        // 是仇恨程度低於聲望的變化。
        vexp = vexp/1000 + 1;
        if (vexp > 5000)
                vexp = (vexp - 5000) / 16 + 2000;
        else
        if (vexp > 1000)
                vexp = (vexp - 1000) / 4 + 1000;

        kid=query("id", killer);
        if (! mapp(hatred = query(vfam + "/hatred")))
        {
                set(vfam + "/hatred/" + kid,
                    ({ killer->name(), vexp }));
                return;
        }

        // 每個幫派最多記錄若干個仇人
        if (! undefinedp(d = hatred[kid]))
        {
                if (! arrayp(d) || sizeof(d) < 2 ||
                    ! intp(d[1]) || ! stringp(d[0]))
                {
                        // 這個ID的數據出了故障
                        d = 0;
                }
        } else
        if (sizeof(hatred) >= MAX_HATRED_PERSON)
        {
                string *ids;
                int i;

                // 過濾去掉一些人，為什麼不去掉一個？這是為
                // 了防止過濾頻繁的進行過濾操作。
                ids = sort_array(keys(hatred),
                                 (: sort_hatred :), hatred);
                for (i = 0; i < sizeof(ids) && i < HATREDP_REMOVED; i++)
                        map_delete(hatred, ids[i]);
        }

        if (! arrayp(d))
                d = ({ killer->name(1), vexp });
        else
        {
                d[0] = killer->name(1);
                d[1] += vexp;
        }

        // 記錄這個人的信息
        hatred[kid] = d;
}

// 去掉所有幫派對某個人的仇恨信息
public void remove_hatred(string id)
{
        mixed dbase, bunch, hatred;
        string fam;

        if (! mapp(dbase = query_entire_dbase()))
                // 現在還沒有仇恨信息
                return;

        // 查閲所有的
        foreach (fam in keys(dbase))
        {
                reset_eval_cost();

                if (! mapp(bunch = dbase[fam]))
                        continue;

                if (mapp(hatred = bunch["hatred"]))
                        // 去掉該幫派對某人的仇恨信息
                        map_delete(hatred, id);

                if (! mapp(hatred) || sizeof(hatred) < 1)
                        // 這個幫派已經沒有仇恨信息
                        map_delete(bunch, "hatred");
        }

        save();
}

public mixed valid_new_build(object ob, string id, string name)
{
        object env;

        if (! env = environment(ob))
                return "好像出現了點問題，請和巫師聯繫！\n";

        if (! env->is_create_bunch_room())
                return "這裏不可以用來建設幫派總壇，請另選地點。\n";

        if (env->query_room_id(id) || env->query_room_name(name))
                return "這裏已經有個房間使用了這個代號了。\n";

        if (file_size(BUNCH_HOME + id + "/center.c") > 0)
                return "已經有別的幫派使用了這個ID代號了。\n";
        // ......
        return 0;
}

// 查看是否可以創建這個
public mixed valid_new_bunch(string fname)
{
        if (query(fname + "/member"))
                return "人家早就有叫這個的啦，你就別湊熱鬧了。\n";

        if (member_array(fname, npc_bunch) != -1)
                return "江湖上早有這個現成的幫派，你還想做什麼？\n";

        if (! undefinedp(FAMILY_D->query_family_fame(fname))
                || ! undefinedp(LEAGUE_D->query_league_fame(fname)))
                return "江湖上已經有" + fname + "了，你還想做什麼？\n";

        return 0;
}

// 創建幫派
public void create_bunch(string fname, string id, string type, int base, object *obs)
{
        mapping data;
        string master, zone, entry, center, quester;
        object ob, env, creater;
        string code, city, position;

        bunch_fame[fname] = base;
        if (! mapp(last_bunch_fame))
                last_bunch_fame = ([ fname : base ]);
        else
                last_bunch_fame[fname] = base;

        foreach (ob in obs)
        {
                data = ([ "time"  : time(),
                          "bunch_name"  : fname,
                          "bunch_id"  : id,
                          "type"  : type  ]);

                if (ob->is_team_leader())
                {
                        creater = ob;
                        master=query("id", ob);
                        position = base_name(env = environment(ob));
                        zone = domain_file(position);

                        data += ([ "level" : 7,
                                   "title" : "幫主" ]);
                } else
                {
                        data += ([ "level" : 6,
                                   "title" : "元老" ]);
                }

                set("bunch", data, ob);

                ob->save();
        }

        quester = BUNCH_HOME + id + "/npc/quester.c";
        assure_file(quester);

        switch(zone)
        {
                case "beijing": city = "bj"; break;
                case "city": city = "yz";  break;
                case "changan": city = "ca"; break;
                case "city3": city = "cd"; break;
                case "suzhou": city = "sz"; break;
                case "hangzhou": city = "hz"; break;
                case "xiangyang": city = "xy"; break;
                case "dali": city = "dl"; break;
                default: city = "yz"; break;
        }

        code = @CODE
// Create by BUNCH_D written by Lonely
// quester.c

#include <ansi.h>
inherit NPC;
CODE;
        code += "#define PLACE          \"" + city + "\"\n";
        code += "#define TYPE           \"" + type + "\"\n";
        code += "#define WAIT_TIME      60\n\n";

        if (type == "bad")
        {
                code += sprintf("mapping bunch_bad = ([\n\t\"bunch_name\" : \"%s\",\n\t\"id\" : \"%s\",\n\t" +
                                "\"place\" : \"%s\",\n\t\"boss\" : \"%s\",\n\t\"place_name\" : \"%s\",\n\t" +
                                "\"type\"  : \"%s\",\n\t]);\n", fname, id,
                                city, creater->name(), citys[city], type);
        } else
        {
                code += sprintf("mapping bunch_good = ([\n\t\"bunch_name\" : \"%s\",\n\t\"id\" : \"%s\",\n\t" +
                                "\"place\" : \"%s\",\n\t\"boss\" : \"%s\",\n\t\"place_name\" : \"%s\",\n\t" +
                                "\"type\"  : \"%s\",\n\t]);\n", fname, id,
                                city, creater->name(), citys[city], type);
        }
        code += @CODE

void create()
{
        set_name("任務使者", ({ "quester" }));
        set("gender", "男性");
        set("age", 23);
        set("long", "他是一個長得很英俊的男子，看上去風流倜儻。\n");
CODE;
        if (type == "bad")
        {
                code += @CODE
        set("bunch/bunch_name", bunch_bad["bunch_name"]);
        set("shen_type", -1);
CODE;
        } else
        {
                code += @CODE
        set("bunch/bunch_name", bunch_good["bunch_name"]);
        set("shen_type", 1);
CODE;
        }
        code += @CODE
        set("per", 29);
        set("combat_exp", 1000000);

        set("attitude", "peaceful");

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 2);
}

CODE;
        if (type == "bad")
                code += "#include <boss_bad.h>\n";
        else
                code += "#include <boss_good.h>\n";

        write_file(quester, code, 1);

        center = BUNCH_HOME + id + "/center.c";
        assure_file(center);

        code = @CODE
// Create by BUNCH_D written by Lonely
// center.c

#include <ansi.h>
#include <room.h>
inherit ROOM;
CODE;
        code += "#define PLACE   \"" + city + "\"\n";
        code += "#define TYPE    \"" + type + "\"\n";

        code += @CODE

// int is_bunch_room() { return 1; }
int sort_by_id(mapping quest1, mapping quest2);

void create()
{
CODE;
        code += sprintf("\tset\(\"short\", \"%s總壇\"\);\n", fname);

        code += sprintf("\tset(\"long\", \"房間的牆上有一塊牌子(paizi)。加入幫派" +
                        "%s的玩家，可以在這裏選擇任務去完成。\\n\");\n", fname);

        code += "\tset(\"objects\", ([\n\t\t__DIR__\"npc/quester\" : 1,\n\t]));\n";
        code += "\tset(\"exits\", ([\n\t\t\"south\" : __DIR__\"room9\", \n\t]));\n";
        code += "\n\tsetup();\n}\n\n";
        // code += "\treplace_program(ROOM);\n}\n";
        code += sprintf("#include <bang_%s.h>\n", type);

        write_file(center, code, 1);

        entry = BUNCH_HOME + id + "/entry.c";
        assure_file(entry);

        code = @CODE
// Create by BUNCH_D written by Lonely
// entry.c

#include <ansi.h>
#include <room.h>
inherit ROOM;

int is_bunch_room() { return 1; }

void create()
{
        set("short", "空房間 - 請使用 cshort 來編輯標題");
        set("long", "這是一間什麼也沒有的空房間，請利用 clong 來編輯房間敍述。\n");

        set("exits", ([
                "north" : __DIR__"room0",
CODE;
        code += sprintf("\t\t\"out\" : \"%s\", \n\t]));\n", base_name(env));
        code += "\n\tsetup();\n}\n\n";

        write_file(entry, code, 1);

        env->create_room(fname, id, entry);
        DATABASE_D->db_remove_item(base_name(env));
        DATABASE_D->db_create_item(env, env->save_dbase_data());
        env->save();
        CP_CMD->copy_dir("/d/room/bunch/", BUNCH_HOME + id + "/");

        message("vision",creater->name()+"找了一堆工人來在"+query("short", env)+
                "敲敲打打的，建造出一些房間。\n", env);

        data = ([
                "bunch_id"      : id,                // 幫派代號
                "bunch_name"    : fname,             // 幫派名稱
                "time"          : time(),            // 幫派成立時間
                "master"        : master,            // 幫派幫主
                "color"         : NOR,               // 幫派顏色
                "money"         : 10000000,          // 幫派資金
                "member"        : obs->query_id(0),  // 幫派成員
                "type"          : type,              // 幫派正邪
                "tax"           : 5,                 // 幫派税率
                "alert"         : 0,                 // 幫派警戒(1~4)
                "league"        : ({}),              // 幫派同盟
                "char_status"   : 0,                 // 幫派人材
                "weapon_status" : 0,                 // 幫派武器
                "char_money"    : 0,                 // 投資在人材的金額
                "weapon_money"  : 0,                 // 投資在武器的金額
                "senior"        : obs->query_id(0),  // 元老（不可提升）
                "room_position" : position,          // 幫派所在文件路徑
                "room_entry"    : entry,             // 幫派入口文件路徑
                "room_name"     : fname,             // 幫派入口處房間名
                "room_id"       : id,                // 幫派入口房間代碼
                "room_zone"     : zone,              // 幫派所在位置區域
                "war_target"    : "NULL",            // 幫派戰爭敵對幫派
                "war_kill"      : 0,                 // 戰爭殺死對手數量
                "war_endtime"   : 0,                 // 幫派戰爭結束時間
                "war_win"       : 0,                 // 幫派戰爭勝利次數
                "war_lose"      : 0,                 // 幫派戰爭失敗次數
        ]);
        set(fname, data);

        save();
}

// 解散幫派
public void dismiss_bunch(string fname)
{
        string *ids;
        string id, dir, pos;
        object ob, npc, room;

        // 清除名望信息
        map_delete(bunch_fame, fname);
        if (mapp(last_bunch_fame)) map_delete(last_bunch_fame, fname);

        // 清除幫派中的所有玩家的相關信息
        ids = query(fname + "/member");
        dir = query(fname + "/room_id");
        pos = query(fname + "/room_position");

        if (arrayp(ids))
        {
                // 幫派中還有玩家，清除他們的信息
                foreach (id in ids)
                {
                        // 處理中
                        reset_eval_cost();
                        UPDATE_D->clear_user_data(id, "bunch");
                }
        }

        ids = BUNCH_D->query_bunch_areas(fname);

        if (arrayp(ids))
        {
                // 幫派中還有地盤，清除他們的信息
                foreach (id in ids)
                {
                        // 處理中
                        reset_eval_cost();
                        area_fame[id]["bunch_name"] = "獨立中";

                        ob = get_object(id);
                        if (! ob) continue;

                        if (objectp(npc = present(area_fame[id]["npc_id"], ob)))
                                delete("bunch", npc);
                }
        }

        RM_CMD->rm_dir(BUNCH_HOME + dir);

        if (stringp(pos))
        {
                room = get_object(pos);
                if (objectp(room))
                {
                        message("vision", "突然幾個童子飛也似"
                                  "的衝了過來，手裏操着各種傢伙"
                                  "，嚷嚷道：閃開！都閃開！\n",
                                  room);
                        room->destroy_room(dir);
                        room->save();
                }
        }

        // 清除幫派的所有信息
        delete(fname);
        save();
}

// 查詢幫派中的弟兄
public string *query_bunch_members(mixed ob)
{
        string *member;
        string fname;

        if (objectp(ob))
                fname=query("bunch/bunch_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! arrayp(member = query(fname + "/member")))
                return 0;

        return member;
}

// 查詢幫派中的地盤
public string *query_bunch_areas(mixed ob)
{
        string *areas, *aname;
        string fname, afile;

        if (objectp(ob))
                fname=query("bunch/bunch_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        aname = keys(area_fame);
        areas = ({ });
        foreach (afile in aname)
        {
                if (area_fame[afile]["bunch_name"] == fname)
                        areas += ({ afile });
        }

        return areas;
}

public string *query_bunch_league(mixed ob)
{
        string *member;
        string fname;

        if (objectp(ob))
                fname=query("bunch/bunch_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! arrayp(member = query(fname + "/league")))
                return 0;

        return member;
}

// 查詢地盤的信息
public mixed query_area_info(string afile, string info)
{
        if (! stringp(afile) || ! stringp(info))
                return 0;

        if (! mapp(area_fame) || ! sizeof(area_fame))
                return 0;

        if (undefinedp(area_fame[afile]))
                return 0;

        if (info == "dbase")
                return area_fame[afile];

        return area_fame[afile][info];
}

// 查詢幫派的信息
public mixed query_bunch_info(string fname, string info)
{
        if (stringp(fname) && stringp(info))
        {
                if (info == "dbase")
                        return query(fname);

                return query(fname + "/" + info);
        }
        else
                return 0;
}

// 在幫派中變動其他參數，例如幫派資產、幫主等。
public void add_bunch_info(string fname, string info, mixed n)
{
        if (! mapp(query(fname)))
                return;

        if (intp(n))
                addn(fname + "/" + info, n);
        else
        if (stringp(n))
                set(fname + "/" + info, n);
        else
                set(fname + "/" + info, n);
}

// 改變地盤中的參數值
public void add_area_info(string afile, string info, mixed value)
{
        if (undefinedp(area_fame[afile]))
                return;

        if (intp(value))
                area_fame[afile][info] += value;
        else
        if (stringp(value))
                area_fame[afile][info] = value;
        else
                area_fame[afile][info] = value;
}

public void set_area_info(string afile, string info, mixed value)
{
        if (undefinedp(area_fame[afile]))
                return;

        area_fame[afile][info] = value;
}

public void remove_area_from_areas(string area_file)
{
        map_delete(area_fame, area_file);
}

// 從幫派中去掉一個人
public varargs void remove_member_from_bunch(mixed fname, string id)
{
        mapping bunch;
        string *member;
        string *areas;
        string area;
        object room, npc;
        string dir, pos;

        if (objectp(fname))
        {
                // fname is user object
                id=query("id", fname);
                if( !stringp(fname=query("bunch/bunch_name", fname)) )
                        return;
        } else
        if (! stringp(fname))
                // or fname must be a bunch name
                return;

        if (! mapp(bunch = query(fname)) ||
            ! arrayp(member = bunch["member"]))
                // no such bunch or no member in the
                return 0;

        member -= ({ id, 0 });
        if (sizeof(member) < 1)
        {
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "聽説" + fname + "人才凋零，昔日幫眾盡皆散去，從此江湖再無此幫派了。");

                map_delete(bunch_fame, fname);
                if (mapp(last_bunch_fame)) map_delete(last_bunch_fame, fname);

                dir = query(fname + "/room_id");
                pos = query(fname + "/room_position");
                areas = BUNCH_D->query_bunch_areas(fname);

                if (arrayp(areas))
                {
                        // 幫派中還有地盤，清除他們的信息
                        foreach (area in areas)
                        {
                                // 處理中
                                reset_eval_cost();
                                area_fame[area]["bunch_name"] = "獨立中";

                                room = get_object(area);
                                if (! room) continue;

                                if (objectp(npc = present(area_fame[area]["npc_id"], room)))
                                        delete("bunch/bunch_name", npc);
                        }
                }

                RM_CMD->rm_dir(BUNCH_HOME + dir);

                if (stringp(pos))
                {
                        room = get_object(pos);
                        if (objectp(room))
                        {
                                message("vision", "突然幾個童子飛也似"
                                        "的衝了過來，手裏操着各種傢伙"
                                        "，嚷嚷道：閃開！都閃開！\n",
                                        room);
                                room->destroy_room(dir);
                                room->save();
                        }
                }

                delete(fname);
        } else
                bunch["member"] = member;
}

// 在幫派中增加一個人
public void add_member_into_bunch(string fname, string id)
{
        string *member;

        if (! arrayp(member = query(fname + "/member")))
                return 0;

        if (member_array(id, member) != -1)
                return 0;

        member += ({ id });
        set(fname + "/member", member);
        save();
}

// 增加地盤到幫派控制中
public void add_area_into_bunch(string fname, string afile, string aname, object ob)
{
        string bname;
        mapping data;
        string *areas;

        areas = keys(area_fame);
        if (member_array(afile, areas) == -1)
        {
                data = ([
                        "area_name"  : aname,
                        "bunch_name" : fname,
                        "npc_id":query("id", ob),
                        "npc_name":query("name", ob),
                        "kaifa"      : 10,
                        "zijin"      : 10,
                        "zhongcheng" : 10,
                        "money"      : 0,
                        "last_money" : 0,
                ]);

                area_fame[afile] = data;
        } else
        {
                bname = area_fame[afile]["bunch_name"];
                if (bname != "獨立中")
                        message("channel:rumor",  HIM "【幫派】某人：" + aname +
                                "宣佈脱離幫派「" + bname + "」的控制！\n" NOR, users());
                area_fame[afile]["bunch_name"] = fname;
                area_fame[afile]["zhongcheng"] = 10;
        }

        set("bunch/bunch_name", fname, ob);
        set("bunch/zhongcheng", 10, ob);
        set("bunch/max_zhongcheng", 100, ob);

        message("channel:rumor",HIM"【幫派】某人："+query("name", ob)+
                "加入幫派「" + fname + "」！\n" NOR, users());

        message("channel:rumor", HIM "【幫派】某人：" + aname +
                "被幫派「" + fname + "」吞併！\n" NOR, users());

        return;
}

// 查詢兩個幫派是否為同盟
public int bunch_is_league(mixed ob1, mixed ob2)
{
        string *lea;
        string bun1, bun2;

        if (stringp(ob1)) bun1 = ob1;
        else
        if (objectp(ob1))
                bun1=query("bunch/bunch_name", ob1);

        if (stringp(ob2)) bun2 = ob2;
        else
        if (objectp(ob2))
                bun2=query("bunch/bunch_name", ob2);

        if (! stringp(bun1) || ! stringp(bun2))
                return 0;

        lea = query(bun1 + "/league");

        if (! arrayp(lea) || sizeof(lea) < 1)
                return 0;

        foreach (string bun in lea)
                if (bun = bun2)
                        return 1;

        return 0;
}

// 增加一個同盟幫派
public int add_league_into_bunch(mixed ob1, mixed ob2)
{
        string *lea;
        string bun1, bun2;

        if (stringp(ob1)) bun1 = ob1;
        else
        if (objectp(ob1))
                bun1=query("bunch/bunch_name", ob1);

        if (stringp(ob2)) bun2 = ob2;
        else
        if (objectp(ob2))
                bun2=query("bunch/bunch_name", ob2);

        if (! stringp(bun1) || ! stringp(bun2))
                return 0;

        lea = query(bun1 + "/league");

        if (! arrayp(lea))
                lea = ({ bun2 });
        else
        if (member_array(bun2, lea) == -1)
                lea += ({ bun2 });

        set(bun1 + "/league", lea);

        lea = query(bun2 + "/league");

        if (! arrayp(lea))
                lea = ({ bun1 });
        else
        if (member_array(bun1, lea) == -1)
                lea += ({ bun1 });

        set(bun2 + "/league", lea);

        return 1;
}

// 移除一個同盟幫派
public int remove_league_from_bunch(mixed ob1, mixed ob2)
{
        string *lea;
        string bun1, bun2;

        if (stringp(ob1)) bun1 = ob1;
        else
        if (objectp(ob1))
                bun1=query("bunch/bunch_name", ob1);

        if (stringp(ob2)) bun2 = ob2;
        else
        if (objectp(ob2))
                bun2=query("bunch/bunch_name", ob2);

        if (! stringp(bun1) || ! stringp(bun2))
                return 0;

        lea = query(bun1 + "/league");

        if (! arrayp(lea) || sizeof(lea) < 1)
                return 0;

        if (member_array(bun2, lea) == -1)
                return 0;

        lea -= ({ bun2 });

        set(bun1 + "/league", lea);

        lea = query(bun2 + "/league");

        if (! arrayp(lea) || sizeof(lea) < 1)
                return 0;

        if (member_array(bun1, lea) == -1)
                return 0;

        lea -= ({ bun1 });

        set(bun2 + "/league", lea);

        return 1;
}

// 宣佈戰爭
public int announce_war_start(string fname, string bname)
{
        message("channel:rumor", HIR "\n\t轟動武林～～驚動萬教～～\n\t"
                HIC + fname + HIR "與" HIM + bname + HIR "的幫派矛盾激化，開始全面開戰……\n" NOR, users());

        set(fname + "/war_target", bname);
        set(bname + "/war_target", fname);
        set(fname + "/war_endtime", time() + 3600);
        set(bname + "/war_endtime", time() + 3600);

        return 1;
}

public int war_stop_time(string fname)  // 第一種停止模式-時間到
{
        int kill_1, kill_2, money;
        string bname, wname, lname;

        bname = query_bunch_info(fname, "war_target");

        kill_1 = query_bunch_info(fname, "war_kill");
        kill_2 = query_bunch_info(bname, "war_kill");

        if (kill_1 > kill_2)
        {
                wname = fname;
                lname = bname;
                money = kill_1 * 10000 + 100000;
        }
        else
        if (kill_1 < kill_2)
        {
                wname = bname;
                lname = fname;
                money = kill_2 * 10000 + 100000;
        }
        else
        {
                message("channel:rumor", HIR "\n\t轟動武林～～驚動萬教～～\n\t"
                        HIC + fname + HIR "與" HIM + bname + HIR "的幫派對決終於結束……\n\t"
                        HIC + fname + HIR "總共殺掉" HIM + bname + HIG " " + CHINESE_D->chinese_number(kill_1) + HIR "位幫眾，\n\t"
                        HIM + bname + HIC "總共殺掉" HIC + fname + HIG " " + CHINESE_D->chinese_number(kill_2) + HIR "位幫眾，\n\t"
                        HIR + "雙方皆死傷慘重，故以平手作收。\n" NOR, users());

                end_bunch_war(bname, fname, 0);

                return 1;
        }

        message("channel:rumor", HIR "\n\t轟動武林～～驚動萬教～～\n\t"
                HIC + wname + HIR "與" HIM + lname + HIR "的幫派對決終於結束……\n\t"
                HIC + wname + HIR "總共殺掉" HIM + lname + HIG " " + CHINESE_D->chinese_number(kill_1) + HIR "位幫眾，\n\t"
                HIM + lname + HIC "總共殺掉" HIC + wname + HIG " " + CHINESE_D->chinese_number(kill_2) + HIR "位幫眾，\n\t"
                HIM + lname + HIC "戰敗，必須賠償" HIC + wname + HIY " " +
                CHINESE_D->chinese_number(money) + HIR "兩黃金。\n" NOR, users());

                end_bunch_war(wname, lname, money);

                return 1;
}

public int war_stop_kill(string fname)   // 第二種停止模式..幫主被作掉......
{
        string bname, master;
        int number, money;

        bname = query_bunch_info(fname, "war_target");
        master = query_bunch_info(fname, "master");
        number = query_bunch_info(bname, "war_kill");
        money = number * 1000 + 100000;

        message("channel:rumor", HIC "\t號外!!號外!!轟動武林的" + HIG + bname + HIC "和" HIG + fname + HIC "的幫派對決總於有了結果了!!!!\n"
                HIG "       " + bname + HIC "殺掉了" HIG + fname + HIC "幫派幫主:" HIG + master + HIC "\n" +
                "\t一時之間" + HIG + fname + HIC + "因為幫主被做掉，以致軍心大亂!!!一路敗退!!!\n" + HIC +
                "\t最後判定::" + HIG + fname + HIC + "必須要付出" + CHINESE_D->chinese_number(money) + "兩的賠償金!!!\n" NOR, users());


        end_bunch_war(bname, fname, money);
        return 1;
}

public int war_stop_money(string lname, int money)   // 第三種停止模式..求和......
{
        string wname, master;

        wname = query_bunch_info(lname, "war_target");
        master = query_bunch_info(lname, "master");

        message("channel:rumor", HIC "\t號外!!號外!!轟動武林的" + HIG + wname + HIC "和" + HIG + lname + HIC + "的幫派對決總於有了結果了!!!!\n" + HIG +
         "   " + wname + HIC + "願接受" + HIG + lname + HIC + "的幫主" + HIG + master + HIC + "求和!!!雙方同意結束戰鬥狀態!!!\n" + HIC +
         "\t最後" + HIG + lname + HIC + "願給予" + HIG + wname + HIC + "共" + CHINESE_D->chinese_number(money) + "兩的求和金!!!\n" NOR, users());

        end_bunch_war(wname, lname, money);

        return 1;
}

public int end_bunch_war(string wname, string lname, int gold)
{
        if (! query(wname + "/member") ||
            ! query(lname + "/member"))
                return 0;

        if (intp(gold) && gold > 0)
        {
                addn(wname + "/war_win", 1);
                addn(lname + "/war_lose", 1);
                addn(wname + "/money", gold);
                addn(lname + "/money", -gold);
        }

        set(wname + "/war_kill", 0);
        set(lname + "/war_kill", 0);
        set(wname + "/war_endtime", 0);
        set(lname + "/war_endtime", 0);
        set(wname + "/war_target", "NULL");
        set(lname + "/war_target", "NULL");

        save();
        return 1;
}

// 增加幫派榮譽點
void add_bunch_honors(string bname, int honors)
{
        addn(bname + "/honors", honors);
        save();
}

int query_bunch_honors(string bname)
{
        return query(bname + "/honors");
}

// 外部調用高效練功
int query_bunch_efficient(string bname, string arg)
{
        if( !bname ) return 0;
        return query(bname + "/efficient/" + arg);
}

void set_bunch_efficient(string bname, string arg, int time)
{
        set(bname + "/efficient/" + arg, time()+time);
        SCHEDULE_D->set_event(time, 0, this_object(), "remove_bunch_efficient", bname, arg); 
        save();
}

void remove_bunch_efficient(string bname, string arg)
{
        delete(bname + "/efficient/" + arg);
        save();
}

// 排序：升序
private int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return -1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return 1;

        return d1[1] - d2[1];
}

public string query_save_file() { return DATA_DIR "bunchd"; }

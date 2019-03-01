// Ward.c 王朝戰爭主控制程序
// Created by Lonely 2000.7.20
// Rewrite by Lonely@nitan3 2007/11/28


#include <ansi.h>
#include <room.h>
#include <combat.h>
#include <command.h>

#define BATTLE_TIME             3000
#define BATTLE_JOIN_TIME        180
#define END_TIME        3000
#define MENG_TIME       300
#define SONG_TIME       500
#define MOVE_TIME       4
#define COST_TIME       60
#define TRAIN_TIME      3
#define ASSI_TIME       180
#define RIDE_CMD        "/cmds/std/ride"
#define UNRIDE_CMD      "/cmds/std/unride"

inherit F_DBASE;

class ward_info
{
        int economy;     /* 經濟國力 */
        int horses;      /* 戰馬數量 */
        int weapons;     /* 兵甲數量 */
        int stones;      /* 石木數量 */
        int arrows;      /* 羽箭數量 */
        int soilders;    /* 兵源數量 */
        int moneys;      /* 餉銀數量 */
        int forages;     /* 糧草數量 */
        int count;       /* 將軍人數 */
        object marshal;  /* 主    帥 */
        object *generals;/* 將 軍 們 */
}

class ward_info song_info;
class ward_info meng_info;
nosave int have1;
nosave int have2;
nosave int start_time;
nosave int valid_check;
nosave int mg_event_id;
nosave int sc_event_id;
nosave int xl_event_id;
nosave int yd_event_id;
nosave int xh_event_id;
nosave int wc_event_id;
nosave int ap_event_id;
nosave int xt_event_id;
nosave int battle_open_flag = 0;
nosave int battle_start_flag = 0;
nosave int battle_time_countdown = 0;
nosave int battle_start_time = 0;
nosave mapping battle_player = allocate_mapping(0);
nosave string battle_name = HIY"國家的榮耀"NOR;
nosave string *ip_numbers = allocate(0);
public string join_kingwar(object ob);
public int start_kingwar();
protected int check_out(object me);
protected int check_quit(object me);
protected void init_general(object me);
protected void init_player(object me);
protected void init_marshal(object me);
protected void auto_check();
protected void auto_fight();
public void auto_move();
public void auto_cost();
public void auto_train();
varargs void do_attack(object me, object target, string zhen, string craft,
                       object env, string dir, object room);
public void attack_over(object me);
protected void remove_enemy();
protected void calculate_score(int flag);
public void fail_kingwar();
public void win_kingwar();
public void finish_kingwar();
protected void restore_status(object me);
protected void restore_kingwar();
protected void message_ward(string msg);
public int query_stones(object me);
public int query_arrows(object me);
public int expend_stones(object me, int count);
public object query_marshal() { return song_info->marshal; }
public object *query_generals() { return song_info->generals; }
public string query_continue_time() { return time_period(time() - start_time); }
public string *query_ip_numbers() { return ip_numbers; }
#include <war.h>

string *zhen1 = ({ "普通陣","魚鱗陣","鋒矢陣","鶴翼陣","偃月陣","方圓陣","雁行陣","長蛇陣","雲龍陣" });
mapping zhen2 = ([
        "普通陣" : ({  0,  -5,   5,  -5,   5,  -5,   5,  -5,   5 }),
        "魚鱗陣" : ({  5,   0,  10,  10,  -5,  10,  -5,   5, -10 }),
        "鋒矢陣" : ({ -5, -10,   0,  10,   5,  -5,  10, -10,   5 }),
        "鶴翼陣" : ({  5,  10, -10,   0,  -5,  -5, -10,  10,   5 }),
        "偃月陣" : ({ -5,   5,  -5,   5,   0, -10, -10,  10,  10 }),
        "方圓陣" : ({  5, -10,   5,   5,  10,   0,  -5,  -5,  -5 }),
        "雁行陣" : ({ -5,   5, -10,  10,  10,   5,   0, -10,  -5 }),
        "長蛇陣" : ({  5,  -5,  10, -10, -10,   5,  10,   0,  -5 }),
        "雲龍陣" : ({ -5,  10,  -5,  -5, -10,   5,   5,   5,   0 }),
]);
int zhen_power(string type1, string type2)
{
        int i, type2_i = 0;

        for (i = 0; i < sizeof(zhen1); i++)
        {
                if (type2 == zhen1[i])
                {
                        type2_i = i;
                        break;
                }
        }

        if (! type2_i) return 0;
        if (undefinedp(zhen2[type1])) return 0;
        if (type2_i > sizeof(zhen2[type1][type2_i]))
                return 0;

        return zhen2[type1][type2_i];
}

int clean_up() { return 1; }

int in_battle(object me)
{
        return battle_start_flag && !undefinedp(battle_player[me->query_id(1)]);
}

int inside_battlefield(object me)
{
        object env = environment(me);

        if( !objectp(env) )
                return 0;

        if( sscanf(base_name(env), "/maze/battle%*s") )
                return 0;

        return 1;
}

int sort_user(object ob1, object ob2)
{
        return (query("level", ob2) - query("level", ob1));
}

/*
void remove(string euid)
{
        if (! this_player())
                return;

        if (sizeof(song_info->generals))
                error("戰爭精靈：目前還有玩家正在參與王朝戰爭，你不能摧毀戰爭精靈。\n");
}
*/
void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "戰爭精靈");
        CHANNEL_D->do_channel(this_object(), "sys", "王朝戰爭已經啟動。");

        song_info = new(class ward_info);
        meng_info = new(class ward_info);

        meng_info->marshal = 0;
        song_info->marshal = 0;
        have1 = 0;
        have2 = 0;
        valid_check = 0;
}

void valid_inquiry()
{
        valid_check = 1;
        return;
}

int do_inquiry(object me, string arg)
{
        object ob;
        object *total;
        mixed *info;
        string str, quest;
        int i, group;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                tell_object(me, "現在前方沒有任何戰事！\n");
                return 0;
        }

        valid_inquiry();

        if (stringp(arg) && arg == "meng")
        {
                if (! valid_check && ! wizardp(me))
                {
                        tell_object(me, "你的軍隊目前還沒有人偵探到蒙古軍隊的情報。\n");
                        return 0;
                }

                total = meng_info->generals;
                info = ({ meng_info->forages, meng_info->moneys,
                           meng_info->weapons, meng_info->horses,
                          meng_info->stones,  meng_info->arrows,
                          meng_info->soilders,meng_info->economy,
                          meng_info->count });
        }
        else
        {
                total = song_info->generals;
                info = ({ song_info->forages, song_info->moneys,
                          song_info->weapons, song_info->horses,
                          song_info->stones,  song_info->arrows,
                          song_info->soilders,song_info->economy,
                          song_info->count });
        }

        group = 0;
        for (i = 0; i < sizeof(total); i++)
                if (objectp(total[i]))
                        group+=query_temp("warquest/group", total[i]);

        str = (arg == "meng" ? "蒙古" : "大宋") + "目前國力及軍力狀況";
        str += "\n\n";
        str += HIC "≡" HIY "──────────────────────────" HIC "≡\n" NOR;

        str += sprintf(WHT "糧草：%-10d擔\t\t    餉銀：%-10d兩\n" NOR, info[0], info[1]);
        str += sprintf(WHT "兵甲：%-10d件\t\t    戰馬：%-10d匹\n" NOR, info[2], info[3]);
        str += sprintf(WHT "石木：%-10d筐\t\t    羽箭：%-10d支\n" NOR, info[4], info[5]);
        str += sprintf(WHT "兵源：%-10d人\t\t    國力：%-10d點\n" NOR, info[6], info[7]);
        str += sprintf(WHT "將領：%-10d名\t\t    士兵：%-10d營\n" NOR, sizeof(total), group);

        str += HIC "\n目前尚可調度的將領名冊如下：\n" NOR;

        for (i = 0; i < sizeof(total); i++)
        {
                if (! objectp(total[i]))
                        continue;

                ob = total[i];

                quest=query_temp("warquest/quest", ob);
                if (! quest) quest = "留守大營，未派遣中";

                str += sprintf("%s%-" + (35+color_len(ob->short(1))) + "s 統軍：%-10d營\n" NOR,
                                (ob == me ? HIC : WHT), ob->short(1),
                                query_temp("warquest/group", ob));
                str += sprintf("%s任務：%-29s 位置：%s\n", (ob == me ? NOR : NOR), quest, environment(ob)->short(1));
        }
        str += "\n\n";
        str += "戰爭已經進行時間 " + query_continue_time() + " \n";
        str += HIB "已陣亡將領" + chinese_number(info[8] - sizeof(total)) + "名\n" NOR;
        str += HIC "≡" HIY "──────────────────────────" HIC "≡\n" NOR;
        write(str);
        return 1;
}

int query_moneys(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->moneys;
        else
                return meng_info->moneys;
}

int change_moneys(int count)
{
        song_info->moneys += count;
        return 1;
}

int expend_moneys(object me, int count)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                song_info->moneys -= count;
        else
                meng_info->moneys -= count;

        return 1;
}

int query_economy(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->economy;
        else
                return meng_info->economy;
}

int query_horses(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->horses;
        else
                return meng_info->horses;
}

int query_weapons(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->weapons;
        else
                return meng_info->weapons;
}

int query_stones(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->stones;
        else
                return meng_info->stones;
}

int query_arrows(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->arrows;
        else
                return meng_info->arrows;
}

int expend_stones(object me, int count)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                song_info->stones -= count;
        else
                meng_info->stones -= count;

        return 1;
}

int query_soilders(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->soilders;
        else
                return meng_info->soilders;
}

int expend_soilders(object me, int count)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                song_info->soilders -= count;
        else
                meng_info->soilders -= count;

        return 1;
}

int query_forages(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->forages;
        else
                return meng_info->forages;
}

void refresh_map()
{
        int i;
        object ob;
        object *dirs;

        dirs = get_dir("/maze/battle3/" + "*.c");
        for( i=0; i<sizeof(dirs); i++ )
        {
                ob = find_object("/maze/battle3/" + dirs[i]);
                if( objectp(ob = find_object("/maze/battle3/" + dirs[i])) )
                        destruct(ob);
        }
}

void init_marshal(object me)
{
        object bingfu, kaijia;

        set_temp("title", HIW"大宋兵馬大元帥"NOR, me);
        set_temp("warquest/party", "song", me);
        set("eff_qi",query("max_qi",  me)+1000*query("degree_jungong", me), me);
        set("qi",query("eff_qi",  me), me);
        set_temp("warquest/train", "infantry", me);
        //me->set_override("quit", (: call_other, __FILE__, "fail_kingwar" :));
        me->set_override("die", (: call_other, __FILE__, "marshal_die" :));

        if (! objectp(kaijia = present("kai jia", me)))
        {
                kaijia = new("/maze/battle3/song/obj/tiejia");
                kaijia->move(me);
        }

        if (! objectp(bingfu = present("bing fu", me)))
        {
                bingfu = new("/adm/npc/obj/bingfu");
                set("owner", query("id",  me), bingfu);
                bingfu->move(me);
        }
        /*
        tell_object(me, HIC "\n大人，朝中可用之兵已經所剩無幾，僅此數營步兵，尚可一戰，此次\n" +
                        "出征，任重道遠，無奈事關我大宋國運，還望大人盡力而為，望大人\n" +
                        "早日得勝，凱旋回朝！御馬監有為將軍備的千裡馬，可助大人腳力。\n\n" NOR);
        */
        song_info->count = 1;
        song_info->marshal = me;
        song_info->generals = ({ me });

        set("kingwar_time", time(), me);
}

// set player's override functions
void init_player(object me)
{
        string where;
        object entry;

        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        me->set_override("die", (: call_other, __FILE__, "general_die" :));
        // me->set_temp("override/exert", (: call_other, __FILE__, "exert" :));

        set_temp("backup/killer", me->query_killer(), me);
        set_temp("backup/want", me->query_want(), me);
        set_temp("in_pkd", 1, me);

        set("backup/condition", me->query_condition(), me);
        me->clear_condition();

        set_temp("warquest/time", time(), me);
        where = query_temp("warquest/entrance", me);
        entry = get_object(where);
        me->move(entry);
        tell_object(me, HIY "你定神一看，這才發現自己已經到了" +
                            environment(me)->short() + HIY "。\n");

        if( query_temp("warquest/party", me) == "song" )
        {
                song_info->count++;
                song_info->generals += ({ me });
        }
        else
        {
                meng_info->count++;
                meng_info->generals += ({ me });
        }


}

void init_general(object me)
{
        string array1, array2, party;
        int degree, flag = 0;
        object ling, horse;

        if (me == meng_info->marshal)
                flag = 1;

        party=query_temp("warquest/party", me);
        degree=4+random(query("combat_exp", me)/5000000+1);

        if (! flag)
        {
                if (degree > 12) degree = 12;
        } else
        {
                if (degree > 16) degree = 16;
        }

        if (! arrayp(meng_info->generals) || ! sizeof(meng_info->generals))
                meng_info->generals = ({ });

        if (! arrayp(song_info->generals) || ! sizeof(song_info->generals))
                song_info->generals = ({ });

        array1 = zhen1[random(sizeof(zhen1))];
        array2 = zhen1[random(sizeof(zhen1))];

        if (party == "meng")
        {
                // 一個營的軍隊為2000氣
                addn("eff_qi", degree*2000, me);
                set("qi",query("eff_qi",  me), me);
                set_temp("warquest/group", degree, me);
                set_temp("warquest/array", array1, me);
                set("degree_jungong", degree, me);
                ling = new("/adm/npc/obj/lingjian");
                set("owner",query("id",  me), ling);
                ling->move(me, 1);

                if (degree > 10) set_temp("title", HIR "蒙古萬夫長" NOR, me);
                else if (degree > 8) set_temp("title", HIG "蒙古軍那顏" NOR, me);
                else if (degree > 5) set_temp("title", HIY "蒙古千夫長" NOR, me);
                else set_temp("title", HIC "蒙古百夫長" NOR, me);

                horse = new("/maze/battle3/meng/horse");
                horse->move(environment(me));
                RIDE_CMD->do_ride(me, horse);
                meng_info->soilders -= degree * 2000;
                meng_info->weapons -= degree * 4000;
                meng_info->horses -= degree * 2000;
                meng_info->generals += ({ me });
                meng_info->count++;
                return;
        } else
        if (party == "song")
        {
                set_temp("title", degree_desc[degree-4], me);
                set("degree_jungong", degree, me);
                set_temp("warquest/array", array2, me);
                ling = new("/adm/npc/obj/lingjian");
                set("owner",query("id",  me), ling);
                ling->move(me, 1);
                song_info->generals += ({ me });
                song_info->count++;
                return;
        }
}

int marshal_die()
{
        message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                MAG "，蒙古騎兵大敗宋軍于襄陽！！\n" +
                "              宋軍主帥 " HIR + query("name", song_info->marshal) + " ( " + query("id", song_info->marshal) + " ) " NOR +
                MAG "戰死沙場，以身殉國！！\n              靖康恥猶未雪，臣子恨何時滅啊！\n" NOR);

        fail_kingwar();
        return 0;
}


// start war
int start_kingwar()
{
        object marshal, general, jianjun, room;
        int i;

        refresh_map();
        ip_numbers = ({ });

        message_ward(CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                MAG "蒙古可汗大舉南侵，大宋派出\n " +
                ""+"兵馬大元帥郭靖"+
                MAG + "，興師北上抗敵......\n" NOR);

        room = get_object("/maze/battle3/syuanmen1");
        if (objectp(room))
                set("defence", 200, room);

        room = get_object("/maze/battle3/myuanmen1");
        if (objectp(room))
                set("defence", 200, room);

        meng_info->economy = 1000000;
        meng_info->moneys = 10000000;
        meng_info->forages = 10000000;
        meng_info->weapons = 4000000;
        meng_info->stones = 500000;
        meng_info->horses = 2000000;
        meng_info->arrows = 500000;
        meng_info->soilders = 2000000;

        // 布置蒙古軍隊
        marshal = new("/maze/battle3/meng/kehan");
        marshal->move("/maze/battle3/mying1");
        set_temp("warquest/quest", "揮軍南下，入侵大宋", marshal);
        meng_info->marshal = marshal;
        meng_info->count = 0;
        init_general(marshal);
        general = new("/maze/battle3/meng/mengj");
        general->move("/maze/battle3/mying1");
        set_temp("warquest/quest", "守衛蒙營，保衛可汗", general);
        init_general(general);

        for (i = 0; i < 4; i++)
        {
                general = new("/maze/battle3/meng/mengj");
                general->move("/maze/battle3/mying");
                set_temp("warquest/quest", "守衛蒙營，保護可汗", general);
                init_general(general);
                general = new("/maze/battle3/meng/mengj");
                general->move("/maze/battle3/dhunya");
                init_general(general);
                set_temp("warquest/quest", "守衛蒙營，保護可汗", general);
        }

        for (i = 0; i < 2; i++)
        {
                general=new("/maze/battle3/meng/mengj");
                general->move("/maze/battle3/caoyuan");
                set_temp("warquest/quest", "守衛草原，阻止入侵", general);
                init_general(general);
        }

        for (i = 0; i < 2; i++)
        {
                general = new("/maze/battle3/meng/mengj");
                general->move("/maze/battle3/myuanmen1");
                set_temp("warquest/quest", "守衛蒙營，阻止入侵", general);
                init_general(general);
        }

        // 初始化宋朝軍隊數據
        song_info->economy = 1200000;
        song_info->moneys = 50000000;
        song_info->forages = 240000;
        song_info->stones = 240000;
        song_info->arrows = 240000;
        song_info->horses = 60000;
        song_info->weapons = 240000;
        song_info->soilders = 120000;

        // 布置大宋軍隊
        marshal = new("/maze/battle3/npc/guo");
        marshal->move("/maze/battle3/sying1");
        set_temp("warquest/quest", "揮軍北上，抵抗入侵", marshal);
        init_marshal(marshal);

        // 布置宋軍
        for(i = 0; i < 4; i++)
        {
                general = new("/maze/battle3/song/songb");
                general->move("/maze/battle3/sying1");
                init_general(general);
        }

        start_time = time();
        mg_event_id = SCHEDULE_D->set_event(MENG_TIME, 1, this_object(), "continue_kingwar", "meng");
        sc_event_id = SCHEDULE_D->set_event(SONG_TIME, 1, this_object(), "continue_kingwar", "song");
        xl_event_id = SCHEDULE_D->set_event(TRAIN_TIME, 1, this_object(), "auto_train");
        yd_event_id = SCHEDULE_D->set_event(MOVE_TIME, 1, this_object(), "auto_move");
        xh_event_id = SCHEDULE_D->set_event(COST_TIME, 1, this_object(), "auto_cost");
        wc_event_id = SCHEDULE_D->set_event(END_TIME, 0, this_object(), "finish_kingwar");
        ap_event_id = SCHEDULE_D->set_event(ASSI_TIME, 1, this_object(), "check_assignment");
        //xt_event_id = SCHEDULE_D->set_event(1, 1, this_object(), "auto_beat");
        // set_heart_beat(1);

        return 1;
}

// 參與戰爭
void join_kingwar(object me)
{
        string where;
        mapping cnd;
        string id = me->query_id(1);

        if( battle_start_flag )
                return tell_object(me, "戰場已經開啟，報名終止。\n");

        if( me->is_busy() )
                return tell_object(me, BUSY_MESSAGE);

        if( me->is_fighting() )
                return tell_object(me, "你目前正在戰鬥中，還是先處理目前的對手再說吧。\n");

        if( me->query_condition("killer") )
                return tell_object(me, "官府正在通緝你，你還敢在這兒拋頭露面？\n");

        if( !battle_open_flag )
                return tell_object(me, "戰爭沒有發出集結，目前無法報名。\n");

        if( me->is_ghost() )
                return tell_object(me, "等你還陽後，再報名吧。\n");

        if( query("level", me) < 10 )
                return tell_object(me, "你這點本事就別進去啦。\n");

        where = base_name(environment(me));
        if( sscanf(where, "/d/newbie/%s") )
                return tell_object(me, "你還沒有正式闖到江湖呢，不能參加報名！\n");

        if( !undefinedp(battle_player[id]) )
        {
                if( !battle_start_flag )
                        return tell_object(me, "你已經報名參與這次的戰爭，請耐心等候召集。\n");

                if( inside_battlefield(me) )
                        return tell_object(me, "你已經在戰場中，快點殺敵吧。\n");

                if( !query_temp("battle_rejoin", me) )
                        return tell_object(me, "你必須使用戰爭勛章方可重新進入戰場。\n");

                delete_temp("battle_rejoin", me);
                set_temp("battle/leave_room", where, me);
                init_player(me);
                return;
        }

        if( member_array(query_ip_number(me), ip_numbers) != -1 )
                return tell_object(me, "你所在的IP已經報名過了!\n");

        ip_numbers += ({ query_ip_number(me) });
        battle_player[id] = allocate_mapping(0);

        CHANNEL_D->channel_broadcast("war", "目前共有 "+sizeof(battle_player)+
                                            " 位玩家報名參與「"+battle_name+HIR"」");
}
// 取消參與戰爭
void cancel_battle(object me)
{
        string id = me->query_id(1);

        if( undefinedp(battle_player[id]) )
                return tell_object(me, "你原本就沒有報名參與這次的戰爭。\n");

        if( battle_start_flag )
                return tell_object(me, "這次的戰爭已經開始，你無法取消，可用quit指令逃離戰場。\n");

        map_delete(battle_player, id);
        ip_numbers -= ({ query_ip_number(me) });

        addn("honors", -100, me); // 扣減榮譽
        if( query("honors", me) < 0 );
                set("honors", 0, me);

        CHANNEL_D->channel_broadcast("war", "目前共有 "+sizeof(battle_player)+
                                            " 位玩家報名參與「"+battle_name+HIR"」");
}

void start_battle()
{
        object *all_player = ({});
        object player;
        string where;
        int i;

        if( sizeof(battle_player) < 6 )
        {
                set_heart_beat(0);
                ip_numbers = allocate(0);
                battle_player = allocate_mapping(0);
                battle_open_flag = 0;
                battle_start_time = 0;
                CHANNEL_D->channel_broadcast("war", "報名參與「"+battle_name+HIR"」戰役的玩家不足 6 人，取消本次戰役。");
                return;
        }

        start_kingwar();

        CHANNEL_D->channel_broadcast("war", "「"+battle_name+HIR"」開始出征！共計 "+sizeof(battle_player)+
                                            " 位玩家參與「"+battle_name+HIR"」，計時 "+(BATTLE_TIME/60)+" 分鐘結束");

        foreach(string id, mapping data in battle_player)
        {
                reset_eval_cost();

                if( !objectp(player = find_player(id)) )
                        continue;

                all_player += ({ player });
        }

        // 開始分配隊伍陣營
        all_player = sort_array(all_player, (: sort_user :));

        for( i=0; i<sizeof(all_player); i++ )
        {
                if( i % 2 == 0 ) {
                        set_temp("battle/team_name", "大宋", all_player[i]);
                        set_temp("battle/entrance", "/maze/battle3/sying1", all_player[i]);
                        set_temp("warquest/party", "song", all_player[i]);
                        init_general(all_player[i]);
                } else {
                        set_temp("battle/team_name", "蒙古", all_player[i]);
                        set_temp("battle/entrance", "/maze/battle3/mying1", all_player[i]);
                        set_temp("warquest/party", "meng", all_player[i]);
                        init_general(all_player[i]);
                }

                where = base_name(environment(all_player[i])); // 記錄玩家所在位置
                        set_temp("battle/leave_room", where, all_player[i]);

                init_player(all_player[i]);
        }

        battle_start_flag = 1;
        battle_time_countdown = BATTLE_TIME;
}

// 某戰場開始接受報名 TIME_D 調用
void start_join()
{
        CHANNEL_D->channel_broadcast("war", HIY"榮耀"NOR YEL"之戰"HIR"發出戰爭集結，即將在 "+(BATTLE_JOIN_TIME/60)+
                                            " 分鐘後發動「"+battle_name+HIR"」，請使用 war join 指令加入戰役。");

        ip_numbers = allocate(0);
        battle_player = allocate_mapping(0);
        battle_open_flag = 1;

        battle_start_time = BATTLE_JOIN_TIME;

        set_heart_beat(1);

        //tell_object(users(), "\a");
}

void heart_beat()
{
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
                        case 1200:
                                CHANNEL_D->channel_broadcast("war", HIY"榮耀"NOR YEL"之戰"HIR"發出戰爭集結，即將在 "+(battle_start_time/60)+
                                                                    " 分鐘後發動「"+battle_name+HIR"」，請使用 battle 指令加入戰役。");
                                break;
                }

                return;
        }

        if( !battle_start_flag )
                return;

        if( !objectp(meng_info->marshal) ||
            !objectp(song_info->marshal) )
                return;

        // 處理自動作戰
        auto_fight();

        if( --battle_time_countdown <= 0 )
        {
                finish_kingwar();
                return;
        }

        auto_check();

        if( battle_time_countdown == 60 || battle_time_countdown == 180 )
                CHANNEL_D->channel_broadcast("war", HIR"戰"NOR RED"爭"HIR"：「"+battle_name+HIR"」即將在 "+(battle_time_countdown/60)+" 分鐘後結束..."NOR);
}

// check all the players who join the war
void auto_check()
{
        object *total;
        object ob;
        string room;
        object *lost;
        int i;

        room = base_name(environment(song_info->marshal));
        if (! sscanf(room, "/maze/battle3/%*s") &&
            ! sscanf(room, "/d/xiangyang/%*s") &&
            ! sscanf(room, "/d/wuguan/%*s"))
        {
                message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) + song_info->marshal->name(1) +
                        MAG "在戰場上臨陣脫逃，導致宋軍無首領，軍心渙散，被蒙古軍隊全線擊敗！\n" NOR);
                fail_kingwar();
                return;
        }

        lost = ({ });
        total = song_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                total = filter_array(total, (: objectp($1) && userp($1) :));
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }
                        // 檢查是否脫離戰場
                        room = base_name(environment(total[i]));
                        if (! sscanf(room, "/maze/battle3/%*s") &&
                            ! sscanf(room, "/d/xiangyang/%*s") &&
                            ! sscanf(room, "/d/wuguan/%*s"))
                        {
                                message("channel:rumor",
                                        MAG "【火線軍情】大宋：" + total[i]->name(1) +
                                        MAG "的軍隊在戰場上臨陣脫逃，宋軍軍心開始渙散，戰鬥力下降！\n" NOR, users());
                                // not in war room
                                restore_status(total[i]);
                                song_info->generals -= ({ total[i] });
                                ip_numbers -= ({ query_ip_number(total[i]) });
                                continue;
                        }
                        // 檢查率領的軍隊(壓糧沒有帶兵的除外)
                        if( !query_temp("warquest/escort", total[i]) &&
                            !query_temp("warquest/guard", total[i]) &&
                            query_temp("warquest/train", total[i]) &&
                            query("combat_exp", total[i])<20000000 &&
                            member_array(room, ward_place) == -1) {
                                if( query("qi", total[i])<query("max_qi", total[i]) )
                                // total[i]->query_temp("warquest/group") < 1)
                                        lost += ({ total[i] });
                        }
                }
        }

        // song_info->generals -= ({ 0 });
        // kickout the players who lost
        foreach (ob in lost)
                check_out(ob);

        return;
}

void check_assignment()
{
        object *total;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(ap_event_id);
                return;
        }

        if (time() - start_time < 600)
                return;

        total = song_info->generals;
        total=filter_array(total,(:objectp($1) && query_temp("warquest/guard", $1) &&
                                       (sscanf(base_name(environment($1)), "/d/xiangyang/%*s") ||
                                        sscanf(base_name(environment($1)), "/d/wuguan/%*s")) :));

        if (sizeof(total) < 1)
        {
                song_info->economy -= 100000;
                if( song_info->economy < 1000000 )
                message("channel:rumor",
                        MAG "【火線軍情】大宋：蒙古突騎兵潛進襄陽城內燒殺搶掠，急待增加守城兵力！！！\n" NOR, users());
                // message_ward(MAG "大宋兵馬大元帥疏于襄陽的城防工作，蒙古騎兵在襄陽城內燒殺搶掠。\n" NOR);
        }
        return;
}

// 軍隊作戰處理
// 分為手動控制和系統控制
void auto_fight()
{
        object *obs, ob, obb, env, room;
        object *total;
        string *dirs;
        string dir;
        string zhen, craft;
        mapping exits;
        int group, number, i, j, team;

        total = meng_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                meng_info->generals -= ({ total[i] });
                                continue;
                        }
                        if (! living(total[i])) continue;

                        ob = total[i];
                        // 糧草及餉銀短缺則出現逃兵
                        if (meng_info->moneys < 1)
                                addn("eff_qi", -1, ob);
                        if (meng_info->forages < 1)
                                addn("eff_qi", -1, ob);

                        group=(query("eff_qi", ob)-query("max_qi", ob))/2000;
                        if (group < 1) group = 1;
                        set("qi",query("eff_qi",  ob), ob);
                        set_temp("warquest/group", group, ob);

                        // 兵法輔助攻擊-恢復
                        if( query_temp("warquest/recover", ob) )
                                continue;

                        // 兵法輔助攻擊-混亂
                        if( query_temp("warquest/confusion", ob) )
                        {
                                set_temp("warquest/recover", 1, ob);
                                ob->start_call_out((: call_other, __FILE__, "recover_status", ob :), 10);
                                continue;
                        }

                        env = environment(ob);
                        obs = all_inventory(env);
                        zhen=query_temp("warquest/array", ob);
                        if( sizeof(obs)>0 && !query_temp("warquest/attack", ob) )
                        {
                                for (j = 0; j < sizeof(obs); j++)
                                {
                                        obb = obs[j];
                                        if (! obb->is_character() || ! living(obb) ||
                                            query("race", obb) != "人類" || obb->is_net_dead() )
                                                continue;

                                        if( query_temp("warquest/party", obb) != "meng" && !wizardp(obb) )
                                        {
                                                message_vision(HIW "$N" HIW "大聲下令道：騎兵準備！一排排騎兵列出整齊的「" HIY + zhen +
                                                        HIW "」，\n陽光下的蒙古軍刀閃閃發光──>" HBRED "突擊" NOR HIW "！！\n" +
                                                        "$N" HIW "一聲令下，萬馬齊鳴，蒙古騎兵開始了可怕的沖鋒！！\n" NOR, ob);

                                                craft = "突擊";
                                                set_temp("warquest/attack", 1, ob);
                                                ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                do_attack(ob, obb, zhen, craft, env);
                                                break;
                                        }
                                }
                        }

                        if( mapp(query("exits", env)) && sizeof(query("exits", env)) &&
                            !query_temp("warquest/attack", ob) )
                        {
                                exits=query("exits", env);
                                dirs = keys(exits);
                                for (j = 0; j < sizeof(dirs); j++)
                                        if (env->query_door(dirs[j], "status") & DOOR_CLOSED)
                                                dirs[j] = 0;
                                dirs -= ({ 0 });
                                if (! sizeof(dirs)) continue;
                                dir = dirs[random(sizeof(dirs))];
                                room = get_object(exits[dir]);

                                if (! objectp(room)) continue;
                                obs = all_inventory(room);
                                if (! sizeof(obs)) continue;
                                for (j = 0; j < sizeof(obs); j++)
                                {
                                        obb = obs[j];
                                        if (! obb->is_character() || ! living(obb) ||
                                            query("race", obb) != "人類" || obb->is_net_dead() )
                                                continue;

                                        if( query_temp("warquest/party", obb) != "meng" && !wizardp(obb) )
                                        {
                                                message_vision(HIC "$N" HIC "大聲下令道：弓箭手準備！\n" +
                                                        "一排排利箭在陽光下閃閃發光──>" HBRED "飛射" NOR HIC "！！\n" +
                                                        "$N" HIC "一聲令下，萬弩齊發！\n" NOR, ob);

                                                craft = "突擊";
                                                set_temp("warquest/attack", 1, ob);
                                                ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                do_attack(ob, obb, zhen, craft, env, dir, room);
                                                break;
                                        }
                                }
                        }
                }
        }

        total = song_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }
                        if (! living(total[i])) continue;

                        ob = total[i];
                        if( query_temp("warquest/group", ob)>0 )
                        {
                                // 糧草及餉銀短缺則出現逃兵
                                if (song_info->moneys < 1)
                                        addn("eff_qi", -1, ob);
                                if (song_info->forages < 1)
                                        addn("eff_qi", -1, ob);
                        }

                        group=(query("eff_qi", ob)-query("max_qi", ob))/2000;
                        if (group > 0)
                                set("qi",query("eff_qi",  ob), ob);
                        if( query_temp("warquest/group", ob)<1 )
                                delete_temp("warquest/group", ob);
                        team=query_temp("warquest/group", ob);
                        number = group - team;

                        if( number>0 && query_temp("warquest/train", ob) )
                        {
                                tell_object(ob, HIR "你訓練出" HIY + chinese_number(number) + HIR "營精銳士兵補充到你的軍隊中！\n" NOR);
                                addn_temp("warquest/group", number, ob);
                        } else
                        if( number<0 && team>0 && !query_temp("warquest/train_begin", ob) )
                        {
                                if (abs(number) > team) number = team;
                                else number = abs(number);
                                tell_object(ob, HIW "你損失了" HIR + chinese_number(number) + HIW "營的士兵！\n" NOR);
                                addn_temp("warquest/group", -number, ob);
                        }

                        // 判斷玩家是否設置為手動控制戰鬥
                        if( !query("env/auto_war", ob))continue;

                        zhen=query_temp("warquest/array", ob);
                        if (! zhen) zhen = "普通陣";

                        env = environment(ob);
                        // 必須有隊伍才能攻擊
                        if( !query_temp("warquest/attack", ob) &&
                              query_temp("warquest/group", ob)>0 &&
                            (query_temp("warquest/train", ob) == "cavalry" ||
                              query_temp("warquest/train", ob) == "archer") )
                        {
                                if( mapp(query("exits", env)) && sizeof(query("exits", env)) )
                                {
                                        exits=query("exits", env);
                                        dirs = keys(exits);
                                        for (j = 0; j < sizeof(dirs); j++)
                                                if (env->query_door(dirs[j], "status") & DOOR_CLOSED)
                                                        dirs[j] = 0;
                                        dirs -= ({ 0 });
                                        if (sizeof(dirs))
                                        {
                                                dir = dirs[random(sizeof(dirs))];
                                                room = get_object(exits[dir]);
                                                if (objectp(room))
                                                {
                                                        obs = all_inventory(room);
                                                        if (sizeof(obs) > 0)
                                                        {
                                                                for (j = 0; j < sizeof(obs); j++)
                                                                {
                                                                        obb = obs[j];
                                                                        if( !obb->is_character() || query_temp("warquest/party", obb) != "meng" )
                                                                                continue;

                                                                        if( query_temp("warquest/train", ob) == "archer" )
                                                                        {
                                                                                if( !query_temp("weapon", ob) )
                                                                                        if (! WIELD_CMD->main(ob, "bow"))
                                                                                                continue;

                                                                                craft = "騎射";
                                                                                message_vision(HIB "$N" HIB "大聲下令道：神弩營列陣「" HIR + zhen +
                                                                                        HIB "」！\n一排排利箭在陽光下閃閃發光──>" HBRED + craft +
                                                                                        NOR HIB "！！\n$N" HIB "一聲令下，萬弩齊發！\n" NOR, ob);
                                                                        } else
                                                                        {
                                                                                craft = "突破";
                                                                                ob->move(room);
                                                                                message_vision(HIC "$N" HIC "將手中寶劍一揮，大喝道：車騎營列陣「" HIR + zhen +
                                                                                        HIC "」！\n向敵軍發起沖鋒──>" HBRED + craft + NOR HIC "！！\n" NOR,
                                                                                        ob, obb);
                                                                        }
                                                                        set_temp("warquest/attack", 1, ob);

                                                                        ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                                        do_attack(ob, obb, zhen, craft, env, dir, room);
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        } else
                        if( !query_temp("warquest/attack", ob) &&
                              query_temp("warquest/group", ob)>0 &&
                              query_temp("warquest/train", ob) == "infantry" )
                        {
                                obs = all_inventory(env);
                                if (sizeof(obs) > 0)
                                {
                                        for (j = 0; j < sizeof(obs); j++)
                                        {
                                                obb = obs[j];
                                                if( !obb->is_character() || query_temp("warquest/party", obb) != "meng" )
                                                        continue;

                                                craft = "奮戰";
                                                message_vision(HIR "$N" HIR "大聲下令道：步兵營列陣！隊伍開始排出整齊的「" HIY + zhen +
                                                        HIR "」！\n在一片閃爍的刀光中，$N" HIR "指揮隊伍發起了可怕的沖鋒──>" HBYEL +
                                                        craft + NOR HIR "！\n" NOR, ob, obb);
                                                set_temp("warquest/attack", 1, ob);
                                                ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                do_attack(ob, obb, zhen, craft, env);
                                                break;
                                        }
                                }
                        }

                        if (base_name(env) == "/maze/battle3/myuanmen1" && ! ob->is_busy() &&
                            query_temp("warquest/party", ob) == "song" )
                                ob->command("break");
                }
        }
        return;
}

varargs void do_attack(object me, object target, string zhen, string craft,
                       object env, string dir, object room)
{
        object weapon, bow, blade, weapon2;
        object *ilist;
        int i, power;
        int damage, count = 0;
        string party;
        int points;

        if (! objectp(me))
                return;

        party=query_temp("warquest/party", me);

        // 守城兵法特殊攻擊
        if (craft == "落石")
        {
                for(i=0;i<query_temp("warquest/group", me);i++ )
                {
                        if (! objectp(target))
                                break;

                        if ((party == "song" && song_info->stones < 1) ||
                            (party == "meng" && meng_info->stones < 1))
                                break;

                        if (party == "song" && song_info->stones < 2000)
                                damage = song_info->stones;
                        else
                        if (party == "meng" && meng_info->stones < 2000)
                                damage = meng_info->stones;
                        else
                                damage = 2000;

                        if (random(10) > 1)
                        {
                                message_vision(HIC "無數擂石及火油從城牆上推下來，$N"
                                        HIC "一時不備，士兵死傷不少。\n" NOR, target);
                                message_vision(HIC "$N" HIC "的士兵吆喝著將無數擂石及火油從城牆上推下去，$n"
                                        HIC "一時不備，士兵死傷不少。\n" NOR, me, target);
                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage, me);
                                addn_temp("warquest/reward", 5, me);
                        } else
                        {
                                message_vision(HIC "$N" HIC "的士兵吆喝著將無數擂石及火油從城牆上推下去，$n"
                                        HIC "卻早有防備，沒有受到損失。\n" NOR, me, target);
                                message_vision(HIC "無數擂石及火油從城牆上推下來，$N"
                                        HIC "卻早有防備，沒有受到損失。\n" NOR, target);
                                addn_temp("warquest/reward", 4, me);
                        }
                        if (party == "song")
                                song_info->stones -= damage;
                        else
                                meng_info->stones -= damage;
                }
                return;
        } else
        if (craft == "射台")
        {
                for(i=0;i<query_temp("warquest/group", me);i++ )
                {
                        if (! objectp(target))
                                break;

                        if ((party == "song" && song_info->arrows < 1) ||
                            (party == "meng" && meng_info->arrows < 1))
                                break;

                        if (party == "song" && song_info->arrows < 2000)
                                damage = song_info->arrows;
                        else
                        if (party == "meng" && meng_info->arrows < 2000)
                                damage = meng_info->arrows;
                        else
                                damage = 2000;

                        if (random(10) < 9)
                        {
                                message_vision(HIC "無數羽箭從箭樓如飛蝗般射下來，$N"
                                        HIC "一時不備，士兵死傷不少。\n" NOR, target);
                                message_vision(HIC "但聽一聲梆子響，從箭垛後面鑽出無數$N的士兵，箭如飛蝗，$n"
                                        HIC "一時不備，士兵倒下了一片。\n" NOR, me, target);

                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage, me);
                                addn_temp("warquest/reward", 5, me);
                        } else
                        {
                                message_vision(HIC "無數羽箭從箭樓如飛蝗般射下來，$N"
                                        HIC "一時不備，士兵死傷不少。\n" NOR, target);
                                message_vision(HIC "但聽一聲梆子響，從箭垛後面鑽出無數$N的士兵，箭如飛蝗，$n"
                                        HIC "卻早有防備，沒有受到損失。\n" NOR, me, target);
                                addn_temp("warquest/reward", 4, me);
                        }
                        if (party == "song")
                                song_info->arrows -= damage;
                        else
                                meng_info->arrows -= damage;
                }
                return;
        }

        // 陣法效果
        count=zhen_power(zhen,query_temp("warquest/array", target));
        points = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE);

        count = points*count/100;
        count = to_int(pow(to_float(count/100), 1.0 / 3)) * 10;
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        if( query_temp("warquest/party", me) == "meng" )
        {
                // 蒙古軍隊攻擊
                if (! objectp(target) || ! target->is_character())
                {
                        addn_temp("apply/attack", -count, me);
                        addn_temp("apply/damage", -count, me);
                        addn_temp("apply/unarmed_damage", -count, me);
                        return;
                }

                weapon=query_temp("weapon", me);
                if (weapon) weapon->unequip();

                blade = present("wan dao", me);

                ilist = all_inventory(me);
                for (i = 0; i < sizeof(ilist); i++)
                {
                        if( query("is_bow", ilist[i]) )
                        {
                                bow = ilist[i];
                                break;
                        }
                }
                if (room && dir) weapon2 = bow;
                else weapon2 = blade;

                if (objectp(weapon2))
                        // WIELD_CMD->do_wield(me, weapon2);
                        weapon2->wield();

                for(i=0;i<query_temp("warquest/group", me);i++ )
                {
                        if (! objectp(target) || ! living(target) ||
                            target->is_net_dead()) break;

                        if (objectp(weapon2) &&
                            query("equipped", weapon2) && query("is_bow", weapon2) )
                        {
                                weapon2->do_shoot(query("id", target),me,weapon2,room,dir,1);
                                addn_temp("warquest/reward", 2, target);
                                continue;
                        }

                        if( query("qi", target)<0 ||
                            environment(me) != environment(target))
                                break;
                        /*
                        message_vision(HIC "$N" HIC "指揮的蒙古鐵騎，萬馬奔騰，" +
                                "如狂風驟雨般朝$n" HIC "發起了沖擊！！\n" NOR, me, target);
                        */

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                        addn_temp("warquest/reward", 2, target);
                }
                addn_temp("apply/attack", -count, me);
                addn_temp("apply/damage", -count, me);
                addn_temp("apply/unarmed_damage", -count, me);
                return;
        }

        power = 0;
        if (craft == "奮戰" || craft == "突破" || craft == "騎射")
                power = points*10/100;
        else if (craft == "奮鬥" || craft == "突進" || craft == "奔射")
                power = points*20/100;
        else if (craft == "奮迅" || craft == "突擊" || craft == "飛射")
                power = points*30/100;

        power = to_int(pow(to_float(power/100), 1.0 / 3)) * 10;
        addn_temp("apply/attack", power, me);
        addn_temp("apply/damage", power, me);
        addn_temp("apply/unarmed_damage", power, me);

        for(i=0;i<query_temp("warquest/group", me);i++ )
        {
                if (! objectp(target)) break;

                if( query_temp("warquest/train", me) == "cavalry" ||
                    query_temp("warquest/train", me) == "infantry" )
                {
                        /*
                        message_vision(HIR "$N" HIR "指揮的三軍殺聲雷動，" +
                                "如狂風驟雨般朝$n發起了攻擊！！\n" NOR, me, target);
                        */
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                        // 殺江洋大盜沒有獎勵
                        if( query_temp("warquest/party", target) == "meng" )
                                addn_temp("warquest/reward", 4, me);
                } else
                if( query_temp("warquest/train", me) == "archer" )
                {
                        bow=query_temp("weapon", me);
                        if( bow && query("is_bow", bow) )
                                bow->do_shoot(query("id", target),me,bow,room,dir,1);
                        // 殺江洋大盜沒有獎勵
                        if( query_temp("warquest/party", target) == "meng" )
                                addn_temp("warquest/reward", 4, me);
                }
        }

        if( query_temp("warquest/train", me) == "cavalry" )
        {
                message_vision(HIW "一陣沖殺過後，$N" HIW "率領著宋軍騎兵如風" +
                        "一般消失了！\n" NOR, me);
                me->move(env);
        }

        addn_temp("apply/attack", -power, me);
        addn_temp("apply/damage", -power, me);
        addn_temp("apply/unarmed_damage", -power, me);

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);
        return;
}

// 消除軍隊異常狀況
// 混亂，士氣低落...
void recover_status(object me)
{
        delete_temp("warquest/confusion", me);
        delete_temp("warquest/recover", me);

        return;
}

void attack_over(object me)
{
        string party;

        if (! objectp(me) || ! objectp(song_info->marshal))
                return;

        if( !(party=query_temp("warquest/party", me)) )
                return;

        if (party == "meng")
                message_vision(HIB "$N手中軍刀一揮，蒙古騎兵攻勢一緩，重新" +
                        "開始列陣，準備發起新一輪的沖擊！！\n" NOR, me);
        else
        if (party == "song")
                message_vision(HIW "$N" HIW "手中令旗一揮，三軍攻勢一緩，重新" +
                        "開始列陣，準備發起新一輪的攻擊！！\n" NOR, me);

        delete_temp("warquest/attack", me);

        return;
}

// 軍隊移動處理
void auto_move()
{
        mapping move_way;
        object *total, ob, room;
        string file;
        int i, count;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(yd_event_id);
                return;
        }

        total = meng_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                move_way = ward_way;
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                meng_info->generals -= ({ total[i] });
                                continue;
                        }

                        if (! living(total[i]))
                                continue;

                        ob = total[i];
                        if( !query_temp("warquest/move_from", ob) )
                                continue;

                        room = environment(ob);

                        // 兵法輔助攻擊-陷阱
                        if( query("craft/trap", room) &&
                            query("craft/trap", room) != "meng" && random(10) )
                        {
                                // 損失一營部隊
                                ob->receive_damage("qi", 2000);
                                ob->receive_wound("qi", 2000);
                                if (! ob->is_busy())
                                        ob->start_busy(2 + random(2));
                                delete("craft/trap", room);
                                message_vision(HIB "$N" HIB "率領著一支蒙古突騎兵落入陷阱，損失了部分軍隊！.....\n" NOR, ob);
                        }

                        file = base_name(room);
                        if (file == "/maze/battle3/sying1")
                        {
                                if( !query_temp("warquest/attack", ob) )
                                {
                                        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                                                MAG "蒙古騎兵大敗宋軍于襄陽！！\n" NOR);

                                        fail_kingwar();
                                        return;
                                }
                        } else
                        if (file == "/maze/battle3/syuanmen1")
                        {
                                if( query("defence", room)>0 && !query_temp("warquest/break", ob) )
                                        message("channel:rumor", MAG "【火線軍情】大宋：一名" +
                                                query_temp("title", ob)+MAG"率領的蒙古突騎兵已經攻到宋軍大營，"+
                                                "宋軍吃緊，急待增援！！！\n" NOR, users());

                                if( query("defence", room)>0 )
                                {
                                        message_vision("$N將手中長刀一揮。兵將蟻聚，湧至城邊，一邊架起雲梯" +
                                                "攀越城牆，一邊掘土而進。\n", ob);
                                        set_temp("warquest/break", 1, ob);
                                        ob->command("break");
                                } else
                                if( query_temp("warquest/break", ob)){
                                        message("channel:rumor", MAG "【火線軍情】大宋：宋軍大營" +
                                                MAG "被蒙古騎兵攻破，形勢危急！！！\n" NOR, users());
                                        delete_temp("warquest/break", ob);
                                }

                        }

                        if (! living(ob) || ob->is_fighting() ||
                            query_temp("warquest/attack", ob) ||
                            query_temp("warquest/break", ob) ||
                                ob->is_busy()) continue;

                        if (! undefinedp(move_way[file]))
                        {
                                set_temp("warquest/move_from", file, ob);
                                GO_CMD->main(ob, move_way[file]);
                        } else
                        if( query_temp("warquest/move_from", ob) )
                                ob->move(query_temp("warquest/move_from", ob));

                        message_vision(HIB "$N" HIB "率領著一支蒙古突騎兵緩緩地朝宋軍大營移動著.....\n" NOR, ob);
                        ob->start_busy(2 + random(2));
                }
        }

        total = song_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                total=filter_array(total,(:objectp($1) && query_temp("warquest/purchase", $1):));
                if (! sizeof(total)) return;

                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }
                        if (! living(total[i]))
                                continue;

                        ob = total[i];
                        room = environment(ob);
                        file = base_name(room);

                        if( query_temp("warquest/move", ob) == "forward" )
                        {
                                move_way = forward_way;
                                if (file == "/maze/battle3/eastgate1")
                                {
                                        //if( query_temp("warquest/purchase", ob) != "forage" )
                                        if( 1 )
                                        {
                                                if (! ob->is_busy())
                                                ob->start_busy(8 + random(8));
                                                switch(query_temp("warquest/purchase", ob) )
                                                {
                                                case "weapon" :
                                                        message_vision(HIY "$N" HIY "率領的大軍到達了襄陽城，命令部下開始購置兵器和盔甲，\n" +
                                                                "$N" HIY "將前線所需兵甲載上馬車，又立刻開始了行軍的奔程....\n" NOR, ob);
                                                        break;
                                                case "horse"  :
                                                        message_vision(HIY "$N" HIY "率領的大軍到達了襄陽城，命令部下開始購置戰馬，\n" +
                                                                "$N" HIY "將前線所需戰馬全部帶上，又立刻開始了行軍的奔程....\n" NOR, ob);
                                                        break;
                                                case "stone"  :
                                                        message_vision(HIY "$N" HIY "率領的大軍到達了襄陽城，命令部下開始購置石頭和檑木，\n" +
                                                                "$N" HIY "將前線所需石木載上馬車，又立刻開始了行軍的奔程....\n" NOR, ob);
                                                        break;
                                                case "arrow"  :
                                                        message_vision(HIY "$N" HIY "率領的大軍到達了襄陽城，命令部下開始購置羽箭，\n" +
                                                                "$N" HIY "將前線所需羽箭載上馬車，又立刻開始了行軍的奔程....\n" NOR, ob);
                                                        break;
                                                case "enlist" :
                                                        message_vision(HIY "$N" HIY "率領的大軍到達了襄陽城，命令部下開始招募新兵，\n" +
                                                                "$N" HIY "帶上所招募的新兵，又立刻開始了行軍的奔程....\n" NOR, ob);
                                                        break;
                                                case "forage" :
                                                        message_vision(HIY "$N" HIY "率領的解糧大軍終于到達了襄陽城，" +
                                                                "$N" HIY "將糧草載上馬車，又立刻開始了行軍的奔程....\n" NOR, ob);
                                                        break;
                                                default :
                                                        break;
                                                }
                                                set_temp("warquest/move", "backward", ob);
                                                move_way = backward_way;
                                        }
                                } else
                                if (file == "/maze/battle3/chengmen")
                                {
                                        if (! ob->is_busy())
                                        ob->start_busy(5 + random(5));
                                        message_vision(HIY "$N" HIY "率領的解糧大軍終于到達了京師汴樑，" +
                                                "$N" HIY "將糧草載上馬車，又立刻開始了行軍的奔程....\n" NOR, ob);
                                        set_temp("warquest/move", "backward", ob);
                                        move_way = backward_way;
                                }
                        } else
                        if( query_temp("warquest/move", ob) == "backward"){
                                move_way = backward_way;
                                if (file == "/maze/battle3/sying1")
                                {
                                        switch(query_temp("warquest/purchase", ob) )
                                        {
                                                case "weapon" :
                                                        message_vision(HIY "$N" HIY "率領的購置兵甲大軍終于到達了襄陽軍營，\n" +
                                                                "$N" HIY "的兵甲及時支援了大軍的軍備....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 100, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->weapons += count;
                                                        tell_object(song_info->marshal, HIY "購置兵甲的軍馬到了，你的軍備又增加了！\n" NOR);
                                                        break;
                                                case "horse"  :
                                                        message_vision(HIY "$N" HIY "率領的購置戰馬大軍終于到達了襄陽軍營，\n" +
                                                                "$N" HIY "的羽箭及時支援了大軍的軍備....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 150, ob);
                                                        count = song_info->economy / 40 + random(500);
                                                        song_info->horses += count;
                                                        tell_object(song_info->marshal, HIY "購置戰馬的軍馬到了，你的軍備又增加了！\n" NOR);
                                                        break;
                                                case "stone"  :
                                                        message_vision(HIY "$N" HIY "率領的購置石木大軍終于到達了襄陽軍營，\n" +
                                                                "$N" HIY "的羽箭及時支援了大軍的軍備....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 150, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->stones += count;
                                                        tell_object(song_info->marshal, HIY "購置石木的軍馬到了，你的軍備又增加了！\n" NOR);
                                                        break;
                                                case "arrow"  :
                                                        message_vision(HIY "$N" HIY "率領的購置羽箭大軍終于到達了襄陽軍營，\n" +
                                                                "$N" HIY "的羽箭及時支援了大軍的軍備....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 150, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->arrows += count;
                                                        tell_object(song_info->marshal, HIY "購置羽箭的軍馬到了，你的軍備又增加了！\n" NOR);
                                                        break;
                                                case "enlist" :
                                                        message_vision(HIY "$N" HIY "率領的招募新兵大軍終于到達了襄陽軍營，\n" +
                                                                "$N" HIY "的新兵及時支援了大軍的兵源....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 150, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->soilders += count;
                                                        tell_object(song_info->marshal, HIY "招募新兵的軍馬到了，你的新兵又增加了！\n" NOR);
                                                        break;
                                                case "forage" :
                                                        message_vision(HIY "$N" HIY "率領的解糧大軍終于到達了襄陽軍營，\n" +
                                                                "$N" HIY "的糧草及時支援了大軍的補給....\n" NOR, ob);

                                                        addn_temp("warquest/reward", 225, ob);
                                                        count = song_info->economy / 5 + random(10000);
                                                        song_info->forages += count;
                                                        tell_object(song_info->marshal, HIY "押解糧草的軍馬到了，你的補給又增加了！\n" NOR);
                                                        break;
                                                default :
                                                        break;
                                        }
                                        delete_temp("warquest/purchase", ob);
                                        delete_temp("warquest/move", ob);
                                        delete_temp("warquest/move_from", ob);
                                        delete_temp("warquest/quest", ob);

                                        if (! ob->is_busy())
                                                ob->start_busy(5 + random(5));

                                        continue;
                                }
                        }
                        if (! living(ob) || ob->is_fighting() ||
                                ob->is_busy()) continue;

                        if (! undefinedp(move_way[file]))
                        {
                                set_temp("warquest/move_from", file, ob);
                                GO_CMD->main(ob, move_way[file]);
                        } else
                        if( query_temp("warquest/move_from", ob) )
                                ob->move(query_temp("warquest/move_from", ob));

                        switch(query_temp("warquest/purchase", ob) )
                        {
                        case "weapon" :
                        case "horse"  :
                        case "stone"  :
                        case "arrow"  :
                                message_vision(YEL "$N率領著購置軍備大隊人馬不分晝夜地行進著.....\n", ob);
                                break;
                        case "enlist" :
                                message_vision(YEL "$N率領著招募新兵的大隊人馬不分晝夜地行進著.....\n", ob);
                                break;
                        case "forage" :
                                message_vision(YEL "$N率領著押運糧草大隊人馬不分晝夜地行進著.....\n", ob);
                                break;
                        default :
                                break;
                        }
                        if (! ob->is_busy())
                        ob->start_busy(2 + random(2));
                }
        }
        return;
}

// 處理軍需物資消耗
void auto_cost()
{
        int i, count = 0;
        object *total;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(xh_event_id);
                return;
        }

        total = meng_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                if (meng_info->moneys > 0 || meng_info->forages > 0)
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                meng_info->generals -= ({ total[i] });
                                continue;
                       }

                        count=query_temp("warquest/group", total[i]);
                        if (! count) continue;

                        if (meng_info->moneys > 0)
                                meng_info->moneys -= count * 200;
                        if (meng_info->moneys < 0)
                                meng_info->moneys = 0;
                        if (meng_info->forages > 0)
                                meng_info->forages -= count * 200;
                        if (meng_info->forages < 0)
                                meng_info->forages = 0;
                }
        }

        total = song_info->generals;
        total=filter_array(total,(:objectp($1) && query_temp("warquest/group", $1):));
        if (arrayp(total) && sizeof(total))
        {
                if (song_info->moneys > 0 || song_info->forages > 0)
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }

                        if( query_temp("warquest/group", total[i])<1 )
                                delete("warquest/group", total[i]);

                        count=query_temp("warquest/group", total[i]);
                        if (! count) continue;

                        if (song_info->moneys > 0)
                                song_info->moneys -= count * 200;
                        if (song_info->moneys < 0)
                                song_info->moneys = 0;
                        if (song_info->forages > 0)
                                song_info->forages -= count * 200;
                        if (song_info->forages < 0)
                                song_info->forages = 0;
                }
        }

        if (song_info->moneys < 1 && ! have1)
        {
                message("channel:rumor",
                        MAG "【火線軍情】大宋：餉銀短缺軍隊出現逃兵，士氣下降！！\n" NOR, users());
                have1 = 1;
        }
        if (song_info->forages < 1 && ! have2)
        {
                message("channel:rumor",
                        MAG "【火線軍情】大宋：糧草短缺軍隊出現逃兵，士氣下降！！\n" NOR, users());
                have2 = 1;
        }

        return;
}

void auto_train()
{
        object *total;
        object ob, room;
        string type;
        int i;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(xl_event_id);
                return;
        }

        total = song_info->generals;
        total=filter_array(total,(:objectp($1) && query_temp("warquest/train_begin", $1):));

        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! living(total[i])) continue;

                        ob = total[i];
                        room = environment(ob);

                        type=query_temp("warquest/train", ob);
                        if (! type)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob, "元帥並沒有分派給你訓練隊伍的命令！\n");
                                continue;
                        }

                        if( !room || !query("train", room )
                            || query("train", room) != type )
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob, "請你到指定的兵營裡面訓練新兵！\n");
                                continue;
                        }

                        if (song_info->forages < 12000)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"由于糧草不足，軍隊新兵的訓練被迫終止！\n");

                                tell_object(song_info->marshal,
                                        HIY "由于糧草不足，你的隊伍被迫終止了訓練！\n" NOR);
                                continue;
                        }

                        if (song_info->soilders < 200)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"由于兵源不足，軍隊無新兵可訓練！\n");
                                tell_object(song_info->marshal,
                                        HIY "由于兵源不足，你的隊伍被迫終止了訓練新兵！\n" NOR);
                                continue;
                        }

                        if (song_info->weapons < 400)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"由于兵甲不足，軍隊新兵的訓練被迫終止！\n");
                                tell_object(song_info->marshal,
                                        HIY "由于兵器不足，你的隊伍被迫終止了訓練新兵！\n" NOR);
                                continue;
                        }

                        if ((type == "archer" || type == "cavalry") &&
                            song_info->horses < 200)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"由于戰馬不足，軍隊新兵的訓練被迫終止！\n");
                                tell_object(song_info->marshal,
                                        HIY "由于戰馬不足，你的隊伍被迫終止了訓練新兵！\n" NOR);
                                continue;
                        }

                        if( query_temp("warquest/group", ob)>query("degree_jungong", ob) )
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"你帶兵的能力不足，訓練不了更龐大精銳的隊伍了！\n");

                                tell_object(song_info->marshal,
                                        HIY "你又訓練出一支的精銳部隊了！\n" NOR);
                                continue;
                        }

                        if( random(query("degree_jungong", ob))>1 )
                        {
                                message_vision(HIW "$N將手中令旗一揮，新兵開始集結，" +
                                        "開始排列著不同的陣形，忽又散開，\n合時井然有序，分" +
                                        "時雜而不亂，看來$N真乃深諳用兵之道的良將啊！\n" NOR, ob);

                                addn("eff_qi", 200, ob);
                                song_info->soilders -= 200;
                                song_info->weapons -= 400;
                                if (type == "archer" || type == "cavalry")
                                        song_info->horses -= 200;
                        } else
                                message_vision(HIY "$N將手中令旗一揮，可是新兵好象亂哄哄的，" +
                                        "根本不聽$N的指揮調遣，\n$N直氣得吹胡子瞪眼！！！\n" NOR, ob);
                        // 糧草額外消耗
                        song_info->forages -= 20;
                }
        }
        return;
}

int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        string room;

        tell_object(me, HIR "\n你乘著混亂，逃回元帥大營，又饑有渴，已到半昏迷狀態！\n" NOR);
        if (ob = me->query_last_damage_from())
        {
                msg = MAG + me->name(1) + MAG "的軍隊被" + ob->name(1) + MAG "的軍隊殺的全軍覆沒，一人逃回大營。" NOR;
        } else
                msg = MAG + me->name(1) + MAG "的軍隊全軍覆沒，一人逃回宋軍大營。" NOR;

        message("channel:rumor", MAG "【火線軍情】大宋：" + msg + "\n" NOR, users());

        me->move("/maze/battle3/sying1");
        message("vision", "一個黑影倏的竄了過來，隨即就是“啪”的"
                "一聲，就見" + me->name() +"摔倒了地上，一副半死不"
                "活的樣子。\n", environment(me), ({ me }));
        tell_object(me, "半昏半迷中，你覺得被人拎了起來，又"
                    "重重的摔倒了地上。\n");
        if (! living(me))
                me->revive();
        return 1;
}

// overide function of quit
int check_quit(object me)
{
        message("channel:rumor", MAG "【火線軍情】大宋：" + MAG + me->name(1) +
                            "在戰場上臨陣脫逃。\n", users());
        restore_status(me);

        if (arrayp(song_info->generals) && sizeof(song_info->generals))
                song_info->generals -= ({ me });

        tell_object(me, "你一口氣逃出了戰場，來到揚州中央廣場。\n");

        // continue run quit function
        me->move("/d/city/guangchang");
        message("vision", "只見" + me->name() + "慌裡慌張的跑了過來。\n",
                environment(me), ({ me }));

        ip_numbers -= ({ query_ip_number(me) });
        return 1;
}

int general_die(object me)
{
        delete_temp("warquest", me);
        message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                MAG"，宋軍將領"HIR+query("name", me)+"("+query("id", me)+")"NOR+
                MAG "戰死沙場，以身殉國！！\n" NOR);

        if (arrayp(song_info->generals) && sizeof(song_info->generals))
                song_info->generals -= ({ me });

        ip_numbers -= ({ query_ip_number(me) });
        return 0;
}

void restore_generals()
{
        object *total;
        int i;

        total = song_info->generals;
        total = filter_array(total, (: objectp($1) && userp($1) :));
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                                
                        total[i]->move(query_temp("battle/entrance", total[i]));
                        restore_status(total[i]);
                        
                        message("vision", "只見" + total[i]->name() + "走了過來。\n",
                                environment(total[i]), ({ total[i] }));
                }
        }
        
        total = meng_info->generals;
        total = filter_array(total, (: objectp($1) && userp($1) :));
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                                
                        total[i]->move(query_temp("battle/entrance", total[i]));
                        restore_status(total[i]);
                        
                        message("vision", "只見" + total[i]->name() + "走了過來。\n",
                                environment(total[i]), ({ total[i] }));
                }
        }
}
                
void fail_kingwar()
{
        remove_enemy();
        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                MAG "宋軍被蒙古軍隊擊敗了，大宋派出使者割地求和！！\n" NOR);
        
        /*
        if (objectp(song_info->marshal))
        {
                restore_status(song_info->marshal);
                song_info->marshal->move("/d/city/guangchang");
                message("vision", "只見" + song_info->marshal->name() + "走了過來。\n",
                        environment(song_info->marshal), ({ song_info->marshal }));
                song_info->marshal->apply_condition("junquest_fail", 50);
        }
        */

        restore_generals();
        
        calculate_score(0);
        restore_kingwar();
        return;
}

void win_kingwar()
{
        remove_enemy();
        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                MAG "宋軍英勇的擊敗了蒙古軍隊，迫使蒙古軍隊向大宋求和！\n" NOR);
        
        restore_generals();
        
        calculate_score(1);
        restore_kingwar();
        return;
}

void finish_kingwar()
{       
        /*
        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(wc_event_id);
                return;
        }
        */
        
        remove_enemy();
        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                MAG + "宋軍經過艱苦的抵抗，使得蒙古軍隊久攻不下，終于撤退了！\n" NOR);
        
        restore_generals();
        
        calculate_score(1);
        restore_kingwar();
        return;
}

void remove_enemy()
{
        object *enemys;
        int j;

        if (arrayp(enemys = children("/maze/battle3/meng/kehan")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                        }
                        tell_room(environment(enemys[j]), HIW "只見" + enemys[j]->name() +
                                  "突然哈哈大笑幾聲後，率領軍隊不見了！\n");
                        destruct(enemys[j]);
                }
        }
        if (arrayp(enemys = children("/maze/battle3/meng/mengj")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "只見" + enemys[j]->name() +
                                          "突然哈哈大笑幾聲，迅速攻出幾招，跳出戰圈率領軍隊不見了。\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "只見" + enemys[j]->name() +
                                          "突然臉色大喜，急急忙忙地率領軍隊不見了。\n");
                        }
                        destruct(enemys[j]);
                }
        }
        if (arrayp(enemys = children("/maze/battle3/meng/mengb")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "只見" + enemys[j]->name() +
                                        "突然哈哈大笑幾聲，迅速攻出幾招，跳出戰圈率領軍隊不見了。\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "只見" + enemys[j]->name()
                                                  + "突然臉色大喜，急急忙忙地率領軍隊不見了。\n");
                        }
                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/maze/battle3/song/songb")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "只見" + enemys[j]->name()
                                                  + "突然面色一變，迅速攻出幾招，跳出戰圈率領軍隊不見了。\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "只見" + enemys[j]->name()
                                                  + "掐值一算，突然臉色大變，急急忙忙地率領軍隊不見了。\n");
                        }
                        song_info->generals -= ({ enemys[j] });
                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/maze/battle3/npc/jianjun")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (environment(enemys[j]) && environment(enemys[j])->is_character())
                                continue;

                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/maze/battle3/meng/horse")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (environment(enemys[j]) && environment(enemys[j])->is_character())
                                continue;

                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/maze/battle3/song/horse")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (environment(enemys[j]) && environment(enemys[j])->is_character())
                                continue;

                        destruct(enemys[j]);
                }
        }
        get_object("/maze/battle3/majiu")->reset();
        return;
}

// send message out
void message_ward(string msg)
{
        // CHANNEL_D->do_channel(this_object(), "rumor", msg);
        message("channel:rumor", MAG "【大宋史記】" + msg + NOR, users());
}

// remove overide function
void restore_status(object me)
{
        object bingfu, lingjian, zhanma, kaijia;

        if (objectp(bingfu = present("bing fu", me)))
                destruct(bingfu);

        if (objectp(lingjian = present("ling jian", me)))
                destruct(lingjian);

        if (objectp(zhanma = present("zhan ma", me)))
                destruct(zhanma);

        if (objectp(zhanma = present("shizi ma", me)))
                destruct(zhanma);

        if (objectp(kaijia = present("kai jia", me)))
                destruct(kaijia);

        me->delete_override("quit");
        me->delete_override("die");
        delete_temp("warquest", me);
        delete_temp("title", me);
        delete_temp("battle", me);
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->receive_damage("qi", 0);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("eff_qi",  me), me);
        // me->clear_condition();

        return;
}

void restore_kingwar()
{
        set_heart_beat(0);

        if (mg_event_id)
                SCHEDULE_D->delete_event(mg_event_id);
        if (sc_event_id)
                SCHEDULE_D->delete_event(sc_event_id);
        if (xl_event_id)
                SCHEDULE_D->delete_event(xl_event_id);
        if (yd_event_id)
                SCHEDULE_D->delete_event(yd_event_id);
        if (xh_event_id)
                SCHEDULE_D->delete_event(xh_event_id);
        if (ap_event_id)
                SCHEDULE_D->delete_event(ap_event_id);
        if (wc_event_id)
                SCHEDULE_D->delete_event(wc_event_id);
        if (xt_event_id)
                SCHEDULE_D->delete_event(xt_event_id);

        meng_info->economy = 0;
        meng_info->moneys = 0;
        meng_info->forages = 0;
        meng_info->stones = 0;
        meng_info->arrows = 0;
        meng_info->horses = 0;
        meng_info->weapons = 0;
        meng_info->soilders = 0;
        meng_info->marshal = 0;
        meng_info->generals = 0;
        meng_info->count = 0;
        song_info->economy = 0;
        song_info->moneys = 0;
        song_info->forages = 0;
        song_info->stones = 0;
        song_info->arrows = 0;
        song_info->horses = 0;
        song_info->weapons = 0;
        song_info->soilders = 0;
        song_info->marshal = 0;
        song_info->generals = 0;
        song_info->count = 0;
        have1 = 0;
        have2 = 0;
        start_time = 0;
        valid_check = 0;
        return;
}

// 統計戰果
void calculate_score(int flag)
{
        int reward, rew, pot, exp, mar, jungong, i, j;
        string prompt;
        object me;
        object *total, ob;
        int war_times;

        total = song_info->generals;

        message("channel:rumor", MAG "【大宋京城】" +
                CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                "......\n" NOR,
                users());

        if (arrayp(total) && sizeof(total) > 0)
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        if (total[i] == song_info->marshal)
                                continue;

                        tell_object(total[i], HIR "蒙古軍隊撤兵了，準備班師回朝吧！\n" NOR);

                        //rew = total[i]->query("jungong");
                        reward=query_temp("warquest/reward", total[i]);
                        
                        if (reward < 2)
                        {
                                continue;
                        }
                        reward += 1000;
                        if (reward > 4000) reward = 4000;
                        if (flag) reward += 1000;
                        //if (rew > 200000) rew = 200000;
                        // exp = (reward / 2 + random(reward / 2)) * (total[i]->query("degree_jungong") + 1) * 10;
                        exp = reward*(query("degree_jungong", total[i])+1)*10;
                        if (war_times) exp *= war_times;
                        pot = exp / 2;
                        mar = pot / 2;
                        jungong = exp / 1000;
#ifdef DB_SAVE
                        if (MEMBER_D->is_double_reward(total[i]))
                                jungong *= 2;
#endif

                        addn("jungong", jungong, total[i]);

                        GIFT_D->delay_war_bonus(total[i],
                                ([ "prompt" : prompt, "exp" : exp, "pot" : pot, "mar" : mar, "gold" : 100 ]));

                        if (random(2)) ob = new("/clone/fam/gift/int3");
                        else ob = new("/clone/fam/gift/con3");
                        ob->move(total[i], 1);
                        if (random(2)) ob = new("/clone/fam/gift/str3");
                        else ob = new("/clone/fam/gift/dex3");
                        ob->move(total[i], 1);
                        for (j = 0; j < 3; j++)
                        {
                                if( random(2) )
                                        ob = new("/clone/goods/sun");
                                else
                                        ob = new("/clone/goods/moon");
                                ob->move(total[i], 1);
                        }

                       if( reward >= 2000 && time()-query_temp("warquest/time", total[i]) >= 600 )
                        {
                                ob = new("/clone/gift/puti-zi");
                                ob->set_amount(2);
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/tianxiang");
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/jiuzhuan");
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/xuanhuang");
                                ob->move(total[i], 1);
                                ob = new("/clone/tongren/tongren"+(1+random(2)));
                                ob->move(total[i], 1);
                        }

                        tell_object(total[i], HIW "因抗蒙有功，你獲得了 " + HIR + chinese_number(jungong) +
                                              HIW " 策軍功！！\n" NOR);
                }
        }

        total = meng_info->generals;

        message("channel:rumor", MAG "【蒙古京都】" +
                CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                "......\n" NOR,
                users());

        if (arrayp(total) && sizeof(total) > 0)
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        if (total[i] == meng_info->marshal)
                                continue;

                        tell_object(total[i], HIR "大宋軍隊撤兵了，準備班師回朝吧！\n" NOR);

                        //rew = total[i]->query("guo_shoucheng/reward");
                        reward=query_temp("warquest/reward", total[i]);

                        if (reward < 2)
                        {
                                continue;
                        }
                        reward += 1000;
                        if (reward > 4000) reward = 4000;
                        if (!flag) reward += 1000;
                        //if (rew > 200000) rew = 200000;
                        // exp = (reward / 2 + random(reward / 2)) * (total[i]->query("degree_jungong") + 1) * 10;
                        exp = reward*(query("degree_jungong", total[i])+1)*5;
                        if (war_times) exp *= war_times;
                        pot = exp / 2;
                        mar = pot / 2;
                        jungong = exp / 1000;
#ifdef DB_SAVE
                        if (MEMBER_D->is_double_reward(total[i]))
                                jungong *= 2;
#endif

                        addn("guo_shoucheng/reward", jungong, total[i]);

                        GIFT_D->delay_war_bonus(total[i],
                                ([ "prompt" : prompt, "exp" : exp, "pot" : pot, "mar" : mar, "gold" : 100 ]));

                        if (random(2)) ob = new("/clone/fam/gift/int3");
                        else ob = new("/clone/fam/gift/con3");
                        ob->move(total[i], 1);
                        if (random(2)) ob = new("/clone/fam/gift/str3");
                        else ob = new("/clone/fam/gift/dex3");
                        ob->move(total[i], 1);
                        for (j = 0; j < 3; j++)
                        {
                                if( random(2) )
                                        ob = new("/clone/goods/sun");
                                else
                                        ob = new("/clone/goods/moon");
                                ob->move(total[i], 1);
                        }

                       if( reward >= 2000 && time()-query_temp("warquest/time", total[i]) >= 600 )
                        {
                                ob = new("/clone/gift/puti-zi");
                                ob->set_amount(2);
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/tianxiang");
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/jiuzhuan");
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/xuanhuang");
                                ob->move(total[i], 1);
                                ob = new("/clone/tongren/tongren"+(1+random(2)));
                                ob->move(total[i], 1);
                        }

                        tell_object(total[i], HIW "因抗宋有功，你獲得了 " + HIR + chinese_number(jungong) +
                                              HIW " 策軍功！！\n" NOR);
                }
        }
        battle_open_flag = 0;
        battle_start_flag = 0;
        battle_time_countdown = 0;
        ip_numbers = allocate(0);
        battle_player = allocate_mapping(0);
        return;
}

int continue_kingwar(string arg)
{
        object general;
        object room;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(mg_event_id);
                SCHEDULE_D->delete_event(sc_event_id);
                return 0;
        }

        if (! arg) return 0;
        if (arg == "meng")
        {
                room = get_object("/maze/battle3/mying1");
                if (meng_info->forages > 240000 && meng_info->moneys > 240000 &&
                    meng_info->weapons > 48000 && meng_info->horses > 24000 &&
                    meng_info->soilders > 24000)
                {
                        for (int i = 0; i < 4; i++)
                        {
                                general = new("/maze/battle3/meng/mengb");
                                general->move(room);
                                init_general(general);
                                set_temp("warquest/quest", "攻打宋營，入侵大宋", general);
                        }
                }
        } else
        if (arg == "song")
        {
                room = get_object("/maze/battle3/sying1");
                if (song_info->forages > 100000 && song_info->moneys > 100000 &&
                    song_info->soilders > 24000)
                {
                        general = new("/maze/battle3/song/songb");
                        general->move(room);
                        init_general(general);
                        tell_object(song_info->marshal,
                                HIR "朝廷派遣支援前線的一名宋軍將領到了，趕快派遣他任務吧！！！\n" NOR);
                }
        }

        return 1;
}

string do_assign(object me, string arg)
{
        object *inv;
        object ob;
        object ling, horse;
        string who, what;
        int i, count;

        if (! arg || sscanf(arg, "%s to %s", who, what) != 2)
                return "請用 paiqian sb to do sth. 來發布號令！\n";

        if (who != "all" && ! objectp(ob = present(who, environment(me))))
                return "這裡沒有你可以調度的這名將領！\n";

        if (who == "all" && (what != "battle" || what != "ST-chuzheng"))
                return "請用 paiqian sb to do sth. 來發布號令！\n";

        if( query_temp("warquest/party", ob) != "song" )
                return "對方不是宋軍，如何供你調度？！\n";

        /*
        if( query("degree_jungong", ob)<1 )
                return "對方的統帥才能太低了，難堪大用！\n";
        */

        if (ob == me)
                return "自己命令自己？你不嫌累啊你？！\n";

        if( query("id", ob) == "jianjun" )
                return "你不可以命令大宋監軍去做別的事情！\n";

        if( query("eff_qi", ob) < query("max_qi", ob) )
                return "你還是等對方養好傷再派遣任務吧。\n";

        switch(what)
        {
        case "battle":
        case "chuzheng":
                message_vision(HIR "$N略一沉思，，而後果敢的下令道：本帥決定迎戰蒙古大軍，\n"
                               "各位將軍請即刻調派人馬隨同本帥出征！如有違令，軍法論處！\n" NOR, me);

                inv = all_inventory(environment(me));
                for (i=sizeof(inv)-1; i>=0; i--)
                if( query_temp("warquest/group", inv[i])>0 )
                {
                        if( query_temp("warquest/purchase", inv[i]) ||
                            query_temp("warquest/guard", inv[i]) ||
                            (userp(inv[i]) && inv[i] != me))
                                continue;

                        inv[i]->set_leader(me);
                        set_temp("warquest/battle", 1, inv[i]);
                        set_temp("warquest/quest", "軍隊出征，迎戰蒙軍", inv[i]);
                }
                return "眾將大聲應道：末將遵命！！\n";
                break;
        case "recon": // reconnaissance
        case "zhencha" :
                if (! userp(ob))
                        return "此項任務艱巨,你只能調度玩家去完成！\n";

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "蒙古大軍攻擊將至，\n命你火速前往蒙古軍營偵察敵情以便本帥" +
                               "知己知彼，如有延誤，軍法論處！\n" NOR, me, ob);
                set_temp("title", HIY"大宋偵察營統領"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/recon", 1, ob);
                set_temp("warquest/quest", "深入蒙境，偵察敵情", ob);
                // ob->command("recon");
                break;
        case "enlist":
        case "zhaomu-xinbing" :
                /*
                if (! userp(ob))
                        return "此項任務艱巨,你只能調度玩家去完成！\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "軍中銀兩已經不多，不足以用來支付招募新兵的開支！\n";

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中兵員匱乏，\n命你火速率部，趕去襄陽城內招募新兵" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);
                set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "enlist", ob);
                set_temp("warquest/quest", "招募新兵，補充兵源", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-weapon":
        case "gouzhi-bingjia" :
                /*
                if (! userp(ob))
                        return "此項任務艱巨,你只能調度玩家去完成！\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "軍中銀兩已經不多，不足以用來支付購置兵甲的開支！\n";

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中兵器和盔甲匱乏，\n命你火速率部，趕去襄陽城內採購兵器和盔甲" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);
                set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "weapon", ob);
                set_temp("warquest/quest", "購置兵甲，補充軍備", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-arrow":
        case "gouzhi-yujian" :
                /*
                if (! userp(ob))
                        return "此項任務艱巨,你只能調度玩家去完成！\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "軍中銀兩已經不多，不足以用來支付購置羽箭的開支！\n";

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍營箭樓羽箭匱乏，\n命你火速率部，趕去襄陽城內採購羽箭" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);
                set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "arrow", ob);
                set_temp("warquest/quest", "購置羽箭，補充軍備", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-horse":
        case "gouzhi-zhanma" :
                /*
                if (! userp(ob))
                        return "此項任務艱巨,你只能調度玩家去完成！\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "軍中銀兩已經不多，不足以用來支付購置戰馬的開支！\n";

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中戰馬匱乏，\n命你火速率部，趕去襄陽城內採購戰馬" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);
                set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "horse", ob);
                set_temp("warquest/quest", "購置戰馬，補充軍備", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-stone":
        case "gouzhi-shimu" :
                /*
                if (! userp(ob))
                        return "此項任務艱巨,你只能調度玩家去完成！\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "軍中銀兩已經不多，不足以用來支付購置石木的開支！\n";

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中滾石和檑木匱乏，\n命你火速率部，趕去襄陽城內採購石頭和木材" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);
                set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "stone", ob);
                set_temp("warquest/quest", "購置石木，補充軍備", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "guard-xiangyang":
        case "shouwei-xiangyang" :
                if (! userp(ob))
                        return "此項任務艱巨,你只能調度玩家去完成！\n";
                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來蒙古騎兵常騷擾我大宋襄陽城，\n命你火速率部，趕去襄陽駐守城池" +
                               "，如有延誤，軍法論處！\n" NOR, me, ob);
                set_temp("title", HIY"大宋後防營統領"NOR, ob);
                /*
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                */
                set_temp("warquest/guard", 1, ob);
                set_temp("warquest/quest", "守衛襄陽，穩固後方", ob);
                // ob->command("guard");
                ob->move("/d/wuguan/guofu_dating");
                break;
        case "yayun-liangcao":
        case "escort-forage" :
                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中糧草匱乏，\n命你火速率部，在半月內將京師供應之糧草押解" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);

                set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "forage", ob);
                set_temp("warquest/quest", "押運糧草，補充軍備", ob);
                ob->command("stock");
                break;

        case "xunlian-qibing":
        case "train-cavalry":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "cavalry" )
                        return "對方已經另有他職了，請重新選派將領吧！\n";

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中幾無能戰之師，\n命你加緊訓練一支精銳騎兵，以備不時之需，" +
                               "不得有誤！\n" NOR, me, ob);

                set_temp("title", HIR"大宋車騎營統領"NOR, ob);
                if (! present("zhan ma", ob))
                {
                        UNRIDE_CMD->main(ob);
                        horse = new("/maze/battle3/song/horse");
                        if (horse->move(environment(ob)))
                                RIDE_CMD->do_ride(ob, horse);
                        else destruct(horse);
                }
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/train", "cavalry", ob);
                set_temp("warquest/quest", "訓練騎兵，作戰準備", ob);
                ob->command("drill");
                break;

        case "train-infantry":
        case "xunlian-bubing":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "infantry" )
                        return "對方已經另有他職了，請重新選派將領吧！\n";

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中幾無能戰之師，\n命你加緊訓練一支精銳步兵，以備不時之需，" +
                               "不得有誤！\n" NOR, me, ob);
                set_temp("title", HIW"大宋步兵營統領"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/train", "infantry", ob);
                set_temp("warquest/quest", "訓練步兵，作戰準備", ob);
                ob->command("drill");
                break;

        case "train-archer":
        case "xunlian-gongnu":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "archer" )
                        return "對方已經另有他職了，請重新選派將領吧！\n";

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中幾無能戰之師，\n命你加緊訓練一支精銳弓箭手，以備不時之需，" +
                               "不得有誤！\n" NOR, me, ob);
                set_temp("title", HIB"大宋神弩營統領"NOR, ob);

                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }

                set_temp("warquest/train", "archer", ob);
                set_temp("warquest/quest", "訓練弓兵，作戰準備", ob);
                ob->command("drill");
                break;

        default:
                return "身為一軍之帥，請不要濫用你的軍權！\n";
        }

        return query("name", ob) + "大聲應道：末將遵命！！\n";
}

// rewrited by Lonely@nitan3

#include <ansi.h>
#include <room.h>
#include <command.h>

inherit ITEM;

mapping bingfa = ([
        "fenzhan"    : "奮戰",
        "fendou"     : "奮鬥",
        "fenxun"     : "奮迅",
        "qishe"      : "騎射",
        "benshe"     : "奔射",
        "feishe"     : "飛射",
        "tupo"       : "突破",
        "tujin"      : "突進",
        "tuji"       : "突擊",
/*
        "crossbow" : ([ "qishe"      : "齊射",
                        "lianshe"    : "連射",
                        "liannu"     : "連弩",
                     ]),
                     
        "siegecity": ([ "jinglan"    : "井闌",
                        "chongche"   : "沖車",
                        "fashi"      : "發石",
                        "xiangbing"  : "象兵",
                        "luoshi"     : "落石",
                        "leimu"      : "擂木",
                        "shetai"     : "射台",
                        "jianchui"   : "尖錘",
                     ]),
        "ruse"     : ([ "hunluan"    : "混亂",
                        "xianjing"   : "陷阱",
                        "gongxin"    : "攻心",
                        "huanshu"    : "幻術",
                        "yingzao"    : "營造",
                        "poxian"     : "破陷",
                        "jiaoyu"     : "教諭",
                        "ruma"       : "辱罵",
                     ]),
        "resource" : ([ "guwu"       : "鼓舞",
                        "zhiliao"    : "治療",
                        "yaoshu"     : "妖術",
                     ]),
*/                     
]);

mapping zhenfa = ([
        "putong"   : "普通陣",
        "yulin"    : "魚鱗陣",
        "fengshi"  : "鋒矢陣",
        "heyi"     : "鶴翼陣",
        "yanyue"   : "偃月陣",
        "fangyuan" : "方圓陣",
        "yanxing"  : "雁行陣",
        "changshe" : "長蛇陣",
        "yunlong"  : "雲龍陣",
]);

void create()
{
        set_name(HIW "令箭" NOR, ({"ling jian","ling"}) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long",HIW"一枚大宋將軍調兵遣將的令箭。\n"NOR);
                set("material", "copper");
                set("no_get", 1);
                set("no_steal", 1);
                set("no_put", 1);
                set("no_drop", 1);
                set("no_sell", 1);
                set("no_store", 1);
        }
        set("master", "高□不□寒");
        set("owner", "lonely");
        setup();
}

void init()
{
        object me, ob;

        me = this_player();
        ob = this_object();

        if( query("id", me) == query("owner", ob) )
        {
                add_action("do_stock", ({ "stock", "gouzhi" }));
                add_action("do_move", ({ "move", "yidong" }));
                add_action("do_train", ({ "drill", "xunlian", "train" }));
                add_action("do_attack", ({ "assault", "gongji", "attack", "tuji" }));
                add_action("do_order",  ({ "order", "mingling" }));
                add_action("do_inquiry", ({ "inquiry", "chakan" }));
                // add_action("do_exert", ({ "exert", "yun", "touch" }));
                add_action("do_exert", ({ "touch" }));
                add_action("do_kill",
                        ({ "team kill", "array kill", "touxi", "kill",
                           "hit", "fight", "steal", "beg", "persuade",
                           "perform", "yong", "exert", "yun", "throw",
                           "ansuan", "conjure", "recall" }));        
        }
}

int do_kill(string arg)
{
        string what, who;

        if (! arg) return 0;

        if (this_object()->id(arg))
        {
                write("有沒有搞錯，那是軍隊耶，還不快跑？！\n");
                return 1;
        } else
        if ((sscanf(arg, "%s from %s",what, who) == 2 ||
             sscanf(arg, "%s at %s", what, who) == 2 ||
             sscanf(arg, "%s on %s", what, who) == 2 ||
             sscanf(arg, "%s %s", what, who) == 2) &&
             this_object()->id(who)) {
                write("有沒有搞錯，那是軍隊耶，還不快跑？！\n");
                return 1;
        } else
        if (arg == "roar" || arg == "hou")
        {
                write("有沒有搞錯，那是軍隊耶，還不快跑？！\n");
                return 1;
        }

        return 0;
}

void attack_over(object me)
{
        if (objectp(me))
        {
                message_vision(HIW "$N手中令旗一揮，三軍攻勢一緩，重新"
                        + "開始列陣，準備發起新一輪的攻擊！！\n" NOR, me); 
                delete_temp("warquest/attack", me);
        }
        return;
}      

int do_attack(string arg)
{
        object me, ob, room, env;
        array dirs;
        string dir, who;
        string zhen, craft;
        mapping exits;
        int i;

        me = this_player();
        env = environment(me);

        if (! arg) return notify_fail("你要指揮部隊朝誰發起進攻？\n");

        /*
        // if (me->query("env/auto_contruel"))
        if( query("env/auto_war", me) )
                return notify_fail("你已經設置為由系統自動指揮作戰！如想自己操作，請修改設置。\n");
        */
        if( query_temp("warquest/attack", me) )
                return notify_fail("你的隊伍正在列陣進攻，不要亂發號令了！\n");

        if( !query_temp("warquest/train", me) )
                return notify_fail("你未帶一兵一卒，指揮個什麼呀？\n");

        if( query_temp("warquest/group", me)<1 )
                return notify_fail("你的隊伍已經損失殆盡，無法列陣沖鋒了！\n");

        if (sscanf(arg, "%s with %s & %s on %s", who, zhen, craft, dir) != 4 &&
            sscanf(arg, "%s with %s & %s", who, zhen, craft) != 3)
                return notify_fail("指令格式錯誤，請用 attack <sb.> with <array> & <craft> [on <dir>] 指揮你的隊伍！\n");

        if( !query("array/"+zhen, me) && zhen != "putong" )
                return notify_fail("你目前還沒有通曉「" + zhenfa[zhen] + "」這種陣法！\n");

        if( query_temp("warquest/train", me) == "infantry" )
        {
                if( !query("craft/infantry/"+craft, me) )
                        return notify_fail("你目前還沒有通曉「步兵系兵法」中「" + bingfa[craft] + "」這種兵法！\n");

                if( query("no_fight", env) )
                        return notify_fail("這裡不許戰鬥！！\n");

                if (! objectp(ob = present(who, env)))
                        return notify_fail("無法找到目標，請用 attack <sb.> with <array> & <craft> 指揮你的隊伍！\n");

                if( !query_temp("warquest", ob) || query_temp("warquest/party", ob) != "meng" )
                        return notify_fail("你軍務在身，還是不要輕易招惹是非的好！\n");

                message_vision(HIY "$N將手中寶劍一揮，大喝道：步兵營列陣「" + zhenfa[zhen] +
                        "」，準備向敵軍發起沖鋒──>" + bingfa[craft] + "！！\n" NOR, me, ob);

                set_temp("warquest/attack", 1, me);
                set_temp("warquest/array", zhenfa[zhen], me);
                // me->start_call_out((: call_other, WAR_D, "attack_over", me :), 10);
                call_out("attack_over", 10, me);
                WAR_D->do_attack(me, ob, zhenfa[zhen], bingfa[craft], env);
                return 1;
        } else
        if( query_temp("warquest/train", me) == "cavalry" || 
            query_temp("warquest/train", me) == "archer" )
        {
                if (! dir) return notify_fail("指令格式錯誤，請用 attack <sb.> with <array> & <craft> on <dir>  指揮你的隊伍！\n");

                if( !mapp(exits=query("exits", env)) || undefinedp(exits[dir]) )
                        return notify_fail("無法找到目標，請用 attack <sb.> with <array> & <craft> on <dir>  指揮你的隊伍！\n");

                dirs = keys(exits);
                for (i = 0; i < sizeof(dirs); i++)
                        if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                                dirs[i] = 0;
                dirs -= ({ 0 });

                if (member_array(dir, dirs) == -1)
                        return notify_fail("無法找到目標，請用 attack <sb.> with <array> & <craft> on <dir>  指揮你的隊伍！\n");

                room = get_object(exits[dir]);
                if (! room)  return notify_fail("無法找到目標，請用 attack <sb.> with <array> & <craft> on <dir>  指揮你的隊伍！\n");

                if( query("no_fight", room) )
                        return notify_fail("那裡不允許撕殺！！\n");

                if (! objectp(ob = present(who, room)))
                        return notify_fail("無法找到目標，請用 attack <sb.> with <array> & <craft> on <dir>  指揮你的隊伍！\n");

                if( !query_temp("warquest", ob) || query_temp("warquest/party", ob) != "meng" )
                        return notify_fail("你軍務在身，還是不要輕易招惹是非的好！\n");

                set_temp("warquest/attack", 1, me);
                set_temp("warquest/array", zhenfa[zhen], me);
                if( query_temp("warquest/train", me) == "archer" )
                {
                        if( !query_temp("weapon", me) )
                                if (! WIELD_CMD->main(ob, "bow"))
                                        return notify_fail("你身上沒有弓弩，如何放箭攻擊敵人！\n");
                        message_vision(HIB "$N大聲下令道：神弩營列陣「" + zhenfa[zhen] +
                                "」！一排排利箭在陽光下閃閃發光──>" +
                                bingfa[craft] + "！！\n$N" HIB "一聲令下，萬弩齊發！\n" NOR, me);
                } else
                {
                        me->move(room);
                        message_vision(HIY "$N將手中寶劍一揮，大喝道：車騎營列陣「" + zhenfa[zhen] +
                                "」，準備向敵軍發起沖鋒──>" + bingfa[craft] + "！！\n" NOR,
                                me, ob);
                }

                // me->start_call_out((: call_other, WAR_D, "attack_over", me :), 10);
                call_out("attack_over", 10, me);    
                WAR_D->do_attack(me, ob, zhenfa[zhen], bingfa[craft], env, dir, room);
                return 1;
        }
}

int do_exert(string arg)
{
        tell_object(this_player(),
                "你現在是一軍之統帥了，一舉一動請三思！\n");
        return 1;
}

int do_stock(string arg)
{
        object me;
        
        me = this_player();

        if( !query_temp("warquest/purchase", me) )
                return notify_fail("元帥並未分派你購置軍備的任務，不要擅自行動！\n");
                
        if( query_temp("warquest/move", me) )
                return notify_fail("號令已經發布下去了！\n");

        set_temp("warquest/move", "forward", me);
        set_temp("warquest/move_from", "/d/city2/sying1", me);
                
        switch(query_temp("warquest/purchase", me) )
        {
        case "weapon" :
                message_vision(HIW "$N一揮手中令牌，大喝道：元帥有令，" +
                        "即刻開赴襄陽城購置兵甲，不得有誤！！\n" NOR, me);
                break;
        case "horse"  :
                message_vision(HIW "$N一揮手中令牌，大喝道：元帥有令，" +
                        "即刻開赴襄陽城購買戰馬，不得有誤！！\n" NOR, me);
                break;
        case "stone"  :
                message_vision(HIW "$N一揮手中令牌，大喝道：元帥有令，" +
                        "即刻開赴襄陽城購置石木，不得有誤！！\n" NOR, me);
                break;
        case "arrow"  :
                message_vision(HIW "$N一揮手中令牌，大喝道：元帥有令，" +
                        "即刻開赴襄陽城購置羽箭，不得有誤！！\n" NOR, me);
                break;
        case "enlist" :
                message_vision(HIW "$N一揮手中令牌，大喝道：元帥有令，" +
                        "即刻開赴襄陽城招募新兵，不得有誤！！\n" NOR, me);
                break;
        case "forage" :
                message_vision(HIW "$N一揮手中令牌，大喝道：元帥有令，" +
                        "即刻開赴京師押解糧草，不得有誤！！\n" NOR, me);
                break;
        default :
                break;
        }
        
        return 1;
}

int do_train(string arg)
{
        object me = this_player(), weapon;

        if( !query_temp("warquest/train", me) )
                return notify_fail("元帥並沒有派你訓練隊伍吧？\n");

        if (! environment(me) ||
            base_name(environment(me)) != "/d/city2/sying1")
                return notify_fail("你必須到元帥那裡領命才可以訓練隊伍！\n");

        if( query_temp("warquest/train_begin", me) )
                return notify_fail("你不是正在訓練隊伍嗎？！\n");

        message_vision(HIW "$N接過令箭，大聲道：" +
                "末將遵命，末降即刻前去軍營訓練隊伍！！\n" NOR, me);

        if( query_temp("warquest/train", me) == "cavalry" )
                me->move("/d/city2/sying3");
        else
        if( query_temp("warquest/train", me) == "infantry" )
                me->move("/d/city2/sying2");
        else
        if( query_temp("warquest/train", me) == "archer" )
        {
                weapon=query_temp("weapon", me);
                if (weapon) weapon->unequip();
                WIELD_CMD->main(me, "bow");
                me->move("/d/city2/sying4");
        } else
                return notify_fail("你在做什麼，擅自行動按軍法論處！\n");

        set_temp("warquest/train_begin", 1, me);
        return 1;
}

int do_order(string arg)
{
        object me, env, ob, ling, obb;
        string who, what, dir;
        int i, n, flag;
        mapping jiang;

        me = this_player();
        env = environment(me);
        if (! arg || sscanf(arg, "%s to %s", who, what) != 2)
                return notify_fail("請用 order sb to do sth. 來發布號令！\n");

        if (! objectp(ob = present(who, env)))
                return notify_fail("這裡沒有你可以調度的這名將領！\n");

        if( query_temp("warquest/party", ob) != "song" )
                return notify_fail("對方不是宋軍，如何供你調度？！\n");

        if( !query_temp("warquest/train", ob) || 
            query_temp("warquest/group", ob)<1 )
                return notify_fail("這支隊伍尚未訓練嫻熟，難堪大用！\n");

        if (ob == me)
                return notify_fail("自己命令自己？你不嫌累啊你？！\n");
        
        if (userp(ob)) notify_fail("你不能命令玩家將領！\n");
        
        if( query("degree_jungong", ob)>query("degree_jungong", me) )
                return notify_fail("對方官銜比你高，調動不了人家！\n");

        if( query_temp("warquest/purchase", ob) )
                return notify_fail("對方正在進行軍備工作，最好不要調動他的軍隊！！\n");

        switch(what)
        {
        case "follow":
                message_vision(HIY "$N略一沉思，而後果敢的下令道：“$n，"
                        + "本統領決定迎戰蒙古大軍，\n將軍請即刻調派人馬協助作戰！\n" NOR, me, ob);
                message_vision(HIW "$N大聲應道：末將遵命！願為將軍效犬馬之勞！\n" NOR, ob);
                ob->set_leader(me);
                break;

        case "stop":
                message_vision(HIY "$N仔細查看了四周的地形，而後果敢的下令道：“$n聽令，"
                                + "立即停止隊伍行進！！\n" NOR, me, ob);
                message_vision(HIW "$N大聲應道：末將遵命！！\n" NOR, ob);
                ob->command("move stop");
                break;

        default:
                if (sscanf(what, "guard %s", dir) == 1
                 && query("exits/"+dir, env) )
                {
                        message_vision(HIY "$N仔細查看了四周的地形，而後果敢的下令道：“$n聽令，" +
                                "此處地勢險要，\n易守難攻，還煩請將軍在此處加以扼守！\n" NOR, me, ob);
                        message_vision(HIW "$N大聲應道：末將遵命！但存一兵一卒，決不失陣地！\n" NOR, ob);
                        ob->set_leader(0);
                        ob->command("guard " + dir);
                } else
                if (sscanf(what, "move %s", dir) == 1
                 && query("exits/"+dir, env) )
                {
                        message_vision(HIY "$N仔細查看了四周的地形，而後果敢的下令道：“$n聽令，"
                                + "立即率領部隊\n火速行進，不得有誤！！\n" NOR, me, ob);
                        message_vision(HIW"$N大聲應道：末將遵命！！\n" NOR, ob);
                        ob->set_leader(0);
                        ob->command("move " + dir);
                } else
                if( query("exits/"+what, env) )
                {
                        ob->set_leader(0);
                        GO_CMD->main(ob, what);
                } else
                        return notify_fail("身為一軍之統領，請不要濫用你的軍權！\n");
                break;
        }
        set_temp("warquest/battle", 1, ob);
        set_temp("warquest/quest", "軍隊出征，迎戰蒙軍", ob);
        return 1;
}

int do_inquiry(string arg)
{
        object me = this_player();
        
        return WAR_D->do_inquiry(me, arg);
}

int do_move(string dir)
{
        object me, env;

        me = this_player();
        env = environment(me);

        if (! dir || dir == "stop")
        {
                remove_call_out("on_move");
                write("部隊行進終止！\n");
                return 1;
        }

        if( query("exits/"+dir, env) )
        {
                remove_call_out("on_move");
                call_out("on_move", 2, me, dir);
                write("部隊開始行進！\n");
                return 1;
        }
        else
                write("無法移動，沒有指定方向的出口！\n");

        return 1;
}

void on_move(object me, string dir)
{
        object env;

        if (! me) return;

        env = environment(me);
        if( !query("exits/"+dir, env) )
        {
                write("無法移動，沒有指定方向的出口！\n");
                return;
        }

        if (me->is_fighting() ||
            query_temp("warquest/attack", me) )
        {
                remove_call_out("on_move");
                call_out("on_move", 4, me, dir);
                return;
        } else
        if (GO_CMD->main(me, dir))
        {
                remove_call_out("on_move");
                call_out("on_move", 2, me, dir);
                return;
        } else
        {
                write("無法移動，行進終止！\n");
                return;
        }
}

void owner_is_killed() { destruct(this_object()); }

// Updated by Lonely

#include <ansi.h>
#include <room.h>
inherit ITEM;
inherit F_SSERVER; 

#include "way.h"

void attack_begin(object me, object target, object room, object env, string dir);   
// int do_waring(object me, object ob);

void create()
{
        set_name(HIY "兵符" NOR, ({"bing fu", "fu"}));
        set_weight(10);
        set("no_get", 1);
        set("no_steal", 1);
        set("no_put", 1);
        set("no_drop", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long",HIY"一枚大宋元帥調兵遣將的虎頭兵符。\n"NOR);
                set("material", "copper");
        }
        set("master", "黑客");   
        set("owner", "lonely");
        setup();
}

void init()
{
        object me = this_player(), ob = this_object();
        
        if( query("id", me) == query("owner", ob) )
        {
                add_action("do_escort", "yaliang");  
                add_action("do_train", "xunlian");    
                add_action("do_attack", "tuji");
                add_action("do_order", "order");
                add_action("do_move", "move");   
                add_action("do_inquiry", "inquiry");    
                add_action("do_yun", "yun");
                add_action("do_yun", "exert");
                add_action("do_yun", "touch");
              
/*
                remove_call_out("do_waring");
                call_out("do_waring", 1, me, ob);
*/
        } 
}

/*
int do_waring(object me, object ob)
{
        if (! objectp(me) || ! objectp(ob))
                return 0;
        
        if( query("id", me) == query("owner", ob) )
        {
                add_action("do_escort", "yaliang");  
                add_action("do_move", "move");    
                add_action("do_train", "xunlian");    
                add_action("do_attack", "tuji");
                add_action("do_order", "order");   
                add_action("do_inquiry", "inquiry"); 
                add_action("do_yun", "yun");
                add_action("do_yun", "exert");
                
                remove_call_out("doing");
                call_out("do_waring", 1, me, ob);
          }
}               
*/

int do_kill()
{
        tell_object(this_player(), "你現在是一軍之統帥了，一舉一動請三思！\n");
        return 1;
}    

int do_yun(string arg)
{
        if (arg != "qi" && arg != "recover" && arg != "jing"
        &&  arg != "regenerate" && arg != "heal" && arg != "jingheal")
        {
                tell_object(this_player(), "你現在是一軍之統帥了，一舉一動請三思！\n");
                return 1;
        }
        return 0;
}

int do_escort()
{
        object me = this_player(), ob = this_object();

        if (file_name(environment(me)) != "/quest/quest_jun/sying1")
                return notify_fail("請先回你的帳營調派軍馬，否則將有礙行程！\n"); 

        set_temp("jun_quest/escort", 1, me);

        if( query_temp("jun_quest/move", me) )
                return notify_fail("號令已經發布下去了！\n");   

        ob->start_move(me, ob);
        set("no_get", 1, me);
        set_temp("jun_quest/move", "forward", me);
        set_temp("jun_quest/last_move", "/quest/quest_jun/sying1", me);
        addn_temp("jun_quest/reward", 10, me);

        message_vision(HIW "$N大聲喝道：左右軍馬即刻隨本帥前赴京師押解糧草，不得有誤！！\n" NOR, me); 
        return 1;
}

void start_move(object me, object ob)
{
        call_out("move_me", 2, me, ob);
}

void move_me(object me, object ob)
{
        object owner, room, master;
        mapping move_way;
        string site, temp;
        int liangcao;

        owner = environment(ob);
        if (! owner || ! owner->is_character()
         || query("id", owner) != query("owner", ob) )
        {
                destruct(ob);
                return;
        }

       room = environment(owner);
       site = file_name(room);

       if( query_temp("jun_quest/move", me) == "forward" )
       {
                move_way = forward_way;
                if (site == "/d/bianliang/chengmen")
                {
                        me->start_busy(10 + random(10));   
                        message_vision(HIY "$N率領的解糧大軍終于到達了京師汴樑，" +
                                       "$N將糧草載上馬車，又立刻開始了行軍的奔程....\n" NOR, me);
                        set_temp("jun_quest/move", "backward", me);
                        move_way = backward_way;
                }
       } else 
       if( query_temp("jun_quest/move", me) == "backward" )
       {
                move_way = backward_way;
                if (site == "/quest/quest_jun/sying1")
                {
                        message_vision(HIY "$N率領的解糧大軍終于到達了襄陽軍營，" +
                                       "$N的糧草及時支援了大軍的補給....\n" NOR, me);
                        delete_temp("jun_quest/escort", me);
                        delete_temp("jun_quest/move", me);
                        delete_temp("jun_quest/last_move", me);
                        addn_temp("jun_quest/reward", 20, me);
                        me->start_busy(5+random(5));
                        delete("no_get", me);

                        temp = read_file("/quest/quest_jun/song/liangcao", 1, 1);
                        liangcao = atoi(temp) + 100 + random(100);
                        temp = sprintf("%d", liangcao);
                        write_file("/quest/quest_jun/song/liangcao", temp, 1);

                        remove_call_out("move_me");
                        return;
                }
        }
        if (! living(me) || me->is_fighting() || me->is_busy())
        {
                remove_call_out("move_me");
                call_out("move_me", 4, me, ob);
                return;
        }                    

        if (move_way[site])
        {
                set_temp("jun_quest/last_move", site, me);
                me->command("go " + move_way[site]);
        } else
        if( query_temp("jun_quest/last_move", me) )
                me->move(query_temp("jun_quest/last_move", me));

        message_vision(YEL "$N率領著解糧大隊人馬不分晝夜地行進著.....\n", me);
        me->start_busy(2 + random(2));
        remove_call_out("move_me");
        call_out("move_me", 4, me, ob);
        return;
}

int do_attack(string arg)
{
        object me = this_player(), obb, room, env;
        string dir, who;
        mapping exits;

        env = environment(me);  

        if (! arg) return notify_fail("你要指揮部隊朝誰發起進攻？\n");
        
        if( query_temp("jun_quest/attack", me) )
                return notify_fail("你的隊伍正在列陣進攻，不要亂發號令了！\n"); 

        if( query_temp("jun_quest/group", me)<1 )
                return notify_fail("你的隊伍已經損失殆盡，無法列陣沖鋒了！\n"); 
 
/*
        if( query_temp("jun_quest/train", me) == "infantry" )
        {
                if( query("no_fight", env) )
                        return notify_fail("這裡不許戰鬥！！\n");
*/
                        
                if (objectp(obb = present(arg, env)))
                {
                        if( query("no_fight", env) )
                                return notify_fail("這裡不許戰鬥！！\n");
/*

                        if( query("is_quest", obb) || 
                            query("is_robber", obb) )
                                return notify_fail("你軍務在身，還是不要輕易招惹是非的好！\n");
*/

                        message_vision(HIY "$N將手中寶劍一揮，大喝道：" +
                                       "三軍列陣，準備向敵軍發起沖鋒！！\n" NOR, me);       

                        set_temp("jun_quest/attack", 1, me);
                        call_out("attack_over", 10, me);
                        attack_begin(me, obb, room, env, ""); 
                        return 1;  
                } else
                        return notify_fail("無法找到目標，請用tuji sb 指揮你的隊伍！\n");
/*
        } else
                return notify_fail("你未帶一兵一卒，指揮個什麼呀？\n");
*/
}

void attack_begin(object me, object target, object room, object env, string dir)
{
        object bow;
        int i;
        
        for(i=0;i<query_temp("jun_quest/group", me);i++ )
        {
                if (objectp(target))
/*
                 && (query_temp("jun_quest/train", me) == "cavalry"
                 || query_temp("jun_quest/train", me) == "infantry") )
*/
                {
                        message_vision(HIR "$N指揮的三軍殺聲雷動，" +
                                       "如狂風驟雨般朝$n發起了攻擊！！\n" NOR, me, target);  
                        // COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0); 
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                        addn_temp("jun_quest/reward", 4, me);
                } 
/*
                } else
                if (objectp(target)
                 && query_temp("jun_quest/train", me) == "archer" )
                {
                        bow=query_temp("weapon", me);
                        if( objectp(bow) && query("is_bow", bow) )
                                bow->do_shoot(query("id", target),me,bow,room,dir,1);
                        addn_temp("jun_quest/reward", 4, me);
                } 
*/
                else break;
        }
/*
        if( query_temp("jun_quest/train", me) == "cavalry" )
        {
                message_vision(HIW "一陣沖殺過後，$N率領著宋軍騎兵如風一般消失了！\n" NOR, me);
                me->move(env);
        }
*/

        return;
}


void attack_over(object me)
{
        if (objectp(me))
        {
                message_vision(HIW "$N手中令旗一揮，三軍攻勢一緩，重新開始列陣，準備發起新一輪的攻擊！！\n" NOR, me); 
                delete_temp("jun_quest/attack", me);
        }
        return;
}      

int do_train(object me, string arg)
{
        me = this_player();
        
        if (file_name(environment(me)) != "/quest/quest_jun/sying1")
                return notify_fail("請先回你的帳營才能調派訓練的軍馬！\n"); 

        if( query_temp("jun_quest/train_begin", me) )
                return notify_fail("你不是正在訓練隊伍嗎？！\n");

        message_vision(HIW "$N大聲喝道：左右軍馬，即刻隨本帥前去操練人馬，不得有誤！！\n" NOR, me);   

        set_temp("jun_quest/train", "infantry", me);
        me->move("/quest/quest_jun/sying2");
        set_temp("jun_quest/train_begin", 1, me);
        call_out("train_begin", 2, me);
        call_out("check_me", 2, me);
        return 1;
}

void train_begin(object me)
{
        object room, master, ob;
        string temp;
        int liangcao;
         
        ob = this_object();
        master=find_player(query("master", ob));
        if( !master)master=find_living(query("master", ob));

        if( !query_temp("jun_quest/train", me) )
        {
                remove_call_out("train_begin");
                delete_temp("jun_quest/train_begin", me);
                tell_object(me, "元帥並沒有分派給你訓練隊伍的命令！\n");
                return;
        }

        temp = read_file("/quest/quest_jun/song/liangcao", 1, 1);
        liangcao = atoi(temp);
        if (liangcao <= 10)
        {
                remove_call_out("train_begin");
                delete_temp("jun_quest/train_begin", me);
                tell_object(me,"糧草不足，軍隊訓練被迫終止！\n");

                if (objectp(master) && environment(master)
                &&  master->query_condition("junquest_song"))
                {
                        tell_object(master,
                                HIY "糧草不足，你的隊伍被迫終止了訓練！\n" NOR);
                }                                    
                return;
        }

        if( query_temp("jun_quest/group", me)>query("degree_jungong", me) )
        {
                remove_call_out("train_begin");
                delete_temp("jun_quest/train_begin", me);
                tell_object(me,"你帶兵的能力不足，訓練不了更精銳的隊伍了！\n");

                if (objectp(master) && environment(master)
                &&  master->query_condition("junquest_song"))
                {
                        tell_object(master, HIY "你又訓練出一營的精銳部隊了！\n" NOR);
                }                                    
                return;
        }

        room = environment(me);
        if( !room || !query("train", room )
         || query("train", room) != query_temp("jun_quest/train", me) )
        {
                remove_call_out("train_begin");
                delete_temp("jun_quest/train_begin", me);
                tell_object(me, "請你到指定的兵營裡面訓練隊伍！\n"); 
                return;
        }

        if( random(query("degree_jungong", me))>1 )
        {
                message_vision(HIW "$N將手中令旗一揮，隊伍開始集結，"
                        + "開始排列著不同的陣形，忽又散開，\n合時井然有序，分"
                        + "時雜而不亂，看來$N真乃深諳用兵之道的良將啊！\n" NOR, me);
                addn("eff_qi", 200, me);
        } else
                message_vision(HIY "$N將手中令旗一揮，可是隊伍好象亂哄哄的，"
                        + "根本不聽$N的指揮調遣，\n$N直氣得吹胡子瞪眼！！！\n" NOR, me);

        liangcao -= 2;
        temp = sprintf("%d", liangcao);
        write_file("/quest/quest_jun/song/liangcao", temp, 1);
        remove_call_out("train_begin");
        call_out("train_begin", 10, me);

        return;
}

void check_me(object me)
{
        object *ob, obb, env, room;
        string *dirs, dir;
        mapping exits;
        int group, num, i, g;

        if (! objectp(me)) return;

        group=(query("eff_qi", me)-query("max_qi", me))/2000;
        set("qi",query("eff_qi",  me), me);
        
        num=group-query_temp("jun_quest/group", me);
        
        g=query_temp("jun_quest/group", me);
        g = 0 - g;
    
        if( num>0 && query_temp("jun_quest/train", me) )
        {
                tell_object(me, HIR "你的隊伍精銳度提高了！\n" NOR);
                addn_temp("jun_quest/group", num, me);
        }

        if( num<0 && !query_temp("jun_quest/train_begin", me) )
        {
                if (num < g) num = g;
                tell_object(me, HIW "你損失了" HIR + chinese_number(-num)
                        + HIW"營的士兵！\n"NOR);
                addn_temp("jun_quest/group", num, me);
        }

        if( group <= 1 && !query_temp("jun_quest/train_begin", me) )
        {
                set_temp("jun_quest/group", 0, me);
        }

        env = environment(me);

/*
        if( !query_temp("jun_quest/attack", me )
         && query_temp("jun_quest/train", me) == "cavalry" )
        {
                if( mapp(exits=query("exits", env)) )
                {
                        dirs = keys(exits);
                        for (i = 0; i < sizeof(dirs); i++)
                        if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                                dirs[i] = 0;
                        dirs -= ({ 0 });

                        if (mapp(exits))
                        {
                                dir = dirs[random(sizeof(dirs))];
                                if (! room = find_object(exits[dir]))
                                        room = load_object(exits[dir]);
                                if (room)  
                                {
                                        ob = all_inventory(room);
                                        if (sizeof(ob) > 0)
                                        {
                                                for (i = 0; i < sizeof(ob); i++)
                                                {
                                                        obb = ob[i]; 
                                                        if( query_temp("jun_quest/party", obb) == "meng" )
                                                        {
                                                                set_temp("jun_quest/attack", 1, me);
                                                                call_out("attack_over", 10, me);    
                                                                me->move(room);
                                                                message_vision(
                                                                        HIR "$N率領著一支宋軍騎兵朝$n沖殺過來！\n" NOR,
                                                                        me, obb);
                                                                attack_begin(me, obb, room, env, "");
                                                                break;
                                                        }
                                                }
                                        }
                                }
                        }
                } 
        } else
*/
        if( !query_temp("jun_quest/attack", me )
         && query_temp("jun_quest/train", me) == "infantry" )
        {
                ob = all_inventory(env);   
                if (sizeof(ob) > 0)
                {
                        for (i = 0; i < sizeof(ob); i++)
                        {
                                obb = ob[i]; 
                                if( query_temp("jun_quest/party", obb) == "meng" )
                                {
                                        message_vision(HIW "$N大聲下令道：步兵營列陣！隊伍開始排出整齊"
                                                + "的方陣，在一片閃爍的刀光\n中，$N指揮隊伍發起了可怕的沖鋒！\n" NOR, me);
                                        set_temp("jun_quest/attack", 1, me);
                                        call_out("attack_over", 10, me);
                                        attack_begin(me, obb, room, env, "");   
                                        break;
                                }
                        }
                }
        } 
/*
        } else
        if( !query_temp("jun_quest/attack", me )
         && query_temp("jun_quest/train", me) == "archer"
         && query("qi", me)>query_temp("jun_quest/group", me)*200
         && query("jing", me)>query_temp("jun_quest/group", me)*100 )
        {
                if( mapp(exits=query("exits", env)) )
                {
                        dirs = keys(exits);
                        for (i = 0; i < sizeof(dirs); i++)
                        if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                                dirs[i] = 0;
                        dirs -= ({ 0 });

                        if (mapp(exits))
                        {
                                dir = dirs[random(sizeof(dirs))];
                                if (! room = find_object(exits[dir]))
                                        room = load_object(exits[dir]);
                                if (room)  
                                {
                                        ob = all_inventory(room);
                                        if (sizeof(ob) > 0)
                                        {
                                                for(i = 0; i < sizeof(ob); i++)
                                                {
                                                        obb = ob[i]; 
                                                        if( query_temp("jun_quest/party", obb) == "meng" )
                                                        {
                                                                if( !query_temp("weapon", me) )
                                                                        me->command("wield bow");
                                                                message_vision(HIB "$N大聲下令道：神弩營準備！一排排利箭在陽"
                                                                        + "光下閃閃發光──射擊！！\n$N一聲令下，萬弩齊發！\n" NOR,
                                                                        me);  
                                                                set_temp("jun_quest/attack", 1, me);
                                                                call_out("attack_over", 10, me);    
                                                                attack_begin(me, obb, room, env, dir);
                                                                break;
                                                        }
                                                }
                                        }
                                }
                        }
                } 
        }
*/

        if (file_name(env) == "/quest/quest_jun/myuanmen1" && ! me->is_busy()
         && query_temp("jun_quest/party", me) == "song" )
                me->command("break");
        remove_call_out("check_me");
        call_out("check_me", 1, me);
        return;
}

int do_order(string arg)
{
        object me = this_player(), ob, ling, obb;
        string who, what, dir;
        int i, n, flag;
        mapping jiang;

        if (! arg || sscanf(arg, "%s to %s", who, what) != 2)
                return notify_fail("請用 order sb to do sth. 來發布號令！\n"); 

        if (! objectp(ob = present(who, environment(me))))
                return notify_fail("這裡沒有你可以調度的這名將領！\n");

        if( query_temp("jun_quest/party", ob) != "song" )
                return notify_fail("對方不是宋軍，如何供你調度？！\n");

        if( !query_temp("jun_quest/train", ob) )
                return notify_fail("這支隊伍尚未訓練嫻熟，難堪大用！\n"); 

        if (ob == me)
                return notify_fail("自己命令自己？你不嫌累啊你？！\n"); 
       
        switch(what)
        {         
        case "follow":
                message_vision(HIY "$N略一沉思，而後果敢的下令道：“$n，" +
                        "本帥決定迎戰蒙古大軍，\n將軍請即刻調派人馬隨同本帥出征！\n" NOR, me, ob);
                message_vision(HIW "$N大聲應道：末將遵命！願為將軍效犬馬之勞！\n" NOR, ob);
                ob->set_leader(me);
                break;

        case "guard":
                message_vision(HIY "$N仔細查看了四周的地形，而後果敢的下令道：“$n聽令，" +
                        "此處地勢險要，\n易守難攻，還煩請將軍在此處加以扼守！\n" NOR, me, ob);
                message_vision(HIW "$N大聲應道：末將遵命！但存一兵一卒，決不失陣地！\n" NOR, ob);
                ob->set_leader(0);
                break;

        case "stop":
                if( query_temp("jun_quest/escort", ob) )
                        return notify_fail("對方已經另有軍務了，無法調動軍隊！！\n");
                message_vision(HIY "$N仔細查看了四周的地形，而後果敢的下令道：“$n聽令，" +
                        "立即停止隊伍行進！！\n" NOR, me, ob);
                message_vision(HIW "$N大聲應道：末將遵命！！\n" NOR, ob);
                ob->command("move stop");
                break;

        default:
                if (sscanf(what, "move %s", dir) == 1
                 && query("exits/"+dir, environment(me)) )
                {
                        if( query_temp("jun_quest/escort", ob) )
                                return notify_fail("對方已經另有軍務了，無法調動軍隊！！\n");

                        message_vision(HIY "$N仔細查看了四周的地形，而後果敢的下令道：“$n聽令，" +
                                "立即率領部隊\n火速行進，不得有誤！！\n" NOR, me, ob);     
                        message_vision(HIW "$N大聲應道：末將遵命！！\n" NOR, ob);
                        ob->set_leader(0);
                        ob->command("move " + dir);
                } else                   
                if( query("exits/"+what, environment(me)) )
                {
                        ob->set_leader(0); 
                        ob->command("go " + what);
                } else
                        return notify_fail("身為一軍之帥，請不要濫用你的軍權！\n");
                break; 
        } 
        return 1;
}

int do_inquiry()
{
        object obb, me = this_player();
        string str, temp;
        int i, n, liangcao;
        mapping jiang;

        if( !(jiang=query_temp("jun_quest/jiang", me)) )
                return notify_fail("你現在沒有任命過任何將領！\n");

        str = HIR "您帳下效力的將領共計" + chinese_number(sizeof(jiang)) + "員\n" NOR;
        str += HIY "目前尚可調度的將領名冊如下：\n" NOR;
        str += me->short(1) + HIW "\n        統軍： " +
               chinese_number(query_temp("jun_quest/group", me))+"營"NOR;
//        str += HIC "                戰鬥指數： " + sprintf("%d\n" NOR,
        str += HIC "                戰鬥指數： " + sprintf("%s\n" NOR,
               query("combat_exp", me));
        n = 0;
        for (i = 0; i < sizeof(jiang); i++)
        {
                obb=query_temp("jun_quest/jiang/jiang"+(i+1, me));
                if (objectp(obb))
                {
                        str += obb->short(1) + HIW "\n        統軍： " +
                               chinese_number(query_temp("jun_quest/group", obb))+"營"NOR;
//                        str += HIC "                戰鬥指數： " + sprintf("%d\n" NOR,
                        str += HIC "                戰鬥指數： " + sprintf("%s\n" NOR,
                               query("combat_exp", obb));
                        n++;
                }
        }

        if (n == 0)  str += MAG "你目前已經沒有可用之將了！\n" NOR;
        str += HIB "已陣亡將領" + chinese_number(sizeof(jiang)-n) + "名\n" NOR;

        temp = read_file("/quest/quest_jun/song/liangcao", 1, 1);
        liangcao = atoi(temp);
        str += HIM "目前軍中還有糧草" + chinese_number(liangcao) + "擔\n" NOR;

        write(str);
        return 1;
} 

int do_move(string dir)
{
        object me = this_player();

        if (! dir || dir == "stop")
        {
                remove_call_out("move_on");
                write("部隊行進終止！\n");
                return 1;
        }

        if( query("exits/"+dir, environment(me)) )
        {
                call_out("move_on", 2, me, dir);
                write("部隊開始行進！\n");
                return 1;
        } else
                write("無法移動，沒有指定方向的出口！\n");
        return 1;
}

void move_on(object me, string dir)
{
        if( !query("exits/"+dir, environment(me)) )
        {
                remove_call_out("move_on");
                write("無法移動，沒有指定方向的出口！\n");
                return;
        }

        if( me->is_fighting() || query_temp("jun_quest/attack", me) )
        {
                remove_call_out("move_on");
                call_out("move_on", 4, me, dir);
                return;
        } else
        if (me->command("go " + dir))
        {
                remove_call_out("move_on");
                call_out("move_on", 2, me, dir);
                return;
        } else
        {
                remove_call_out("move_on");
                write("無法移動，行進終止！\n");
                return;
        }
}

void owner_is_killed()
{
        string master_name, master_id;

        master_name = query("master");
        master_id = query("owner");

        message("channel:rumor", MAG "\n【宋史記載】：" +
                CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                MAG "，蒙古騎兵大敗宋軍于襄陽！！\n" +
                "              宋軍主帥 " HIR + master_name + " ( " + master_id + " ) " NOR +
                MAG "戰死沙場，以身殉國！！\n" NOR, users()); 
        message("channel:rumor", HIR "\n【王朝戰爭】靖康恥猶未雪，臣子恨何時滅啊！\n" NOR, users());
        
        WAR_D->fail_war();
        destruct(this_object()); 
        return;
}   

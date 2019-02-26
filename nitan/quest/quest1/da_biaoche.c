// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ITEM;

mapping default_dirs = ([
        "north"     : "北面",
        "south"     : "南面",
        "east"      : "東面",
        "west"      : "西面",
        "northup"   : "北邊",
        "southup"   : "南邊",
        "eastup"    : "東邊",
        "westup"    : "西邊",
        "northdown" : "北邊",
        "southdown" : "南邊",
        "eastdown"  : "東邊",
        "westdown"  : "西邊",
        "northeast" : "東北",
        "northwest" : "西北",
        "southeast" : "東南",
        "southwest" : "西南",
        "up"        : "上面",
        "down"      : "下面",
        "enter"     : "裏面",
        "out"       : "外面",
]);

void create()
{       
        seteuid(getuid());
        set_name(HIM "福威大鏢車" NOR, ({ "da biaoche", "biaoche", "che" }));
        set_weight(500000);
        set("no_get", 1);
        set("unit", "輛");
        set("value", 0);
        set("long", 
                HIM "一輛福威鏢局的大鏢車，上面結結實實蓋着蓬布，一羣鏢頭趕(drive)着車，牢牢地護在一邊。" NOR); 
        set("no_clean_up", 1);
        setup();
        call_out("destroy1", 2, this_object());
}

void init()
{
        if( query("id", this_player()) == query("owner", this_object() )
         || query("id", this_player()) == query("parter", this_object()) )
        {
                add_action("do_gan", "gan"); 
                add_action("do_gan", "drive");
        }
}

void start_escape_me()
{
        call_out("destroy2", (int)query("time"), this_object());
}

int destroy2(object ob)
{
        object me, parter;
        
        if (objectp(ob))
        {
                /*
                message("channel:rumor", MAG "【鏢局傳聞】由於" + query("owner_name") +
                        "率領的鏢隊未能如期抵達，福威鏢局已派人前去接管鏢隊！\n" NOR, users());
                */
                
                tell_object(all_inventory(environment(ob)),
                            HIW "忽然，遠遠走來一羣人，原來是總鏢頭派人前來了，為首的鏢師\n" +
                            "邊走嘴裏還邊罵道：“他奶奶的！等了這麼久也還沒到，總鏢頭\n" +
                            "還以為讓人給劫了，害老子白跑一趟！”説完，一干人等拉起鏢\n" +
                            "車，揚長而去！\n" NOR);

                remove_call_out("destroy1");
                remove_call_out("destroy2");

                me=present(query("owner", ob),environment(ob));
                if( !me)me=find_living(query("owner", ob));
                if (objectp(me))
                {
                        delete_temp("apply/short", me);
                        delete_temp("quest_yunbiao/have_task", me);
                        set_temp("quest_yunbiao/finished_time", time(), me);
                        delete_temp("quest_yunbiao/bandit_killed", me);
                }
                parter=present(query("parter", ob),environment(ob));
                if( !parter)parter=find_living(query("parter", ob));
                if (objectp(parter))
                {
                        delete_temp("apply/short", parter);
                        delete_temp("quest_yunbiao/have_task", parter);
                        set_temp("quest_yunbiao/finished_time", time(), parter);
                        delete_temp("quest_yunbiao/bandit_killed", parter);
                }
                destruct(ob);
        }
        return 1;
}


int do_gan(string arg)
{        
        object me, parter, ob, env, obj, robber, *killer;
        string item, dir, dest, target;
        int reward_exp1, reward_pot1, reward_score1, flag, i, num, reward_exp2, reward_pot2, reward_score2;
        int lvl;

        mapping exit;
        
        ob = this_object();
        me=present(query("owner", ob),environment(ob));
        parter=present(query("parter", ob),environment(ob));

        if (! arg) return notify_fail("你要趕什麼？\n");

        if (! objectp(me) || ! objectp(parter)) 
                return notify_fail("護鏢要兩個人齊心協力，你的同伴不在，不要輕舉妄動！\n"); 

        if (sscanf(arg, "%s to %s", item, dir) != 2 
        ||  item != "biaoche" && item != "che" && item != "da biaoche")
                return notify_fail("指令：gan 鏢車 to 方向 \n");        
                        
        if (me->is_busy())
                return notify_fail("你現在正忙着哩。\n");

        flag = 0;
        killer = all_inventory(environment(me));
        for (i = 0; i < sizeof(killer); i++)
        {
                if (objectp(killer[i]) 
                 && (query("want_kill1", killer[i]) == query("id", me )
                 || query("want_kill2", killer[i]) == query("id", me)) )
                flag = 1;
        }

        if (flag)   
                return notify_fail(CYN"你還是先把眼前的敵人解決了再説吧！\n"NOR);
        
        env = environment(me);
        if (! env) return notify_fail("你要去那裏？\n");

        if( !mapp(exit=query("exits", env)) || undefinedp(exit[dir]) )
                return notify_fail("這個方向過不去。\n");
        
        dest = exit[dir];

        if (! (obj = find_object(dest)))
                call_other(dest, "???");
        if (! (obj = find_object(dest)))
                return notify_fail("那裏好像過不去。\n");

        if (! undefinedp(default_dirs[dir]))
                target = default_dirs[dir];
        else
                target=query("short", obj);

        message_vision(HIG "$N趕着鏢車往" + target + "駛去。\n" NOR, me);  
        
        if( file_name(obj) != query("file", ob) )
        {
                if (ob->move(obj) && me->move(obj) && parter->move(obj)) 
                {
                        all_inventory(env)->follow_me(me, dir);
                        message_vision(HIG "$N趕着鏢車駛了過來。\n" NOR, me);
                        lvl = me->query_skill("driving"); 
                        if (random(lvl + 100) < 50) {
                        me->start_busy(random(2) + 1);
                           if (! parter->is_busy())
                        parter->start_busy(random(2) + 1);
                        } else
                        {
                        me->start_busy(1);
                           if (! parter->is_busy())
                        parter->start_busy(1);
                        }
                        if (me->can_improve_skill("driving")) 
                                me->improve_skill("driving", 1); 
                        if (parter->can_improve_skill("driving")) 
                                parter->improve_skill("driving", 1); 
                }

                if( random(10)<2 && !query("no_fight", environment(ob)) )
                {
                        num = random(2) + 1;
                        for (i = 0; i < num; i++)
                        {
                                robber = new(__DIR__"bandit");
                                set("want_kill1",query("id",  me), robber);
                                set("want_kill2",query("id",  parter), robber);
                                robber->move(environment(ob));  
                                robber->kill_ob(me);
                                robber->kill_ob(parter);
                                robber->check_me();  
                                robber->start_busy(1);
                        }
                        me->start_busy(1);
                        parter->start_busy(1);   
                }
        } else
        {
                reward_exp1=query("combat_exp", me)/30000;
                reward_exp1=reward_exp1+query_temp("quest_yunbiao/bonus", me)*25;
                reward_exp1=reward_exp1+query_temp("quest_yunbiao/bandit_killed", me)*200;
                reward_exp1 = reward_exp1 / 2 + random(reward_exp1 / 2);
                if (reward_exp1 > 800) reward_exp1 = 800;
#ifdef DB_SAVE
                if (MEMBER_D->is_double_reward(me)) 
                        reward_exp1 *= 2;
#endif
                reward_pot1 = reward_exp1;
                reward_score1 = reward_exp1 / 40;
                
                reward_exp2=query("combat_exp", parter)/30000;
                reward_exp2=reward_exp2+query_temp("quest_yunbiao/bonus", parter)*20;
                reward_exp2=reward_exp2+query_temp("quest_yunbiao/bandit_killed", parter)*200;
                reward_exp2 = reward_exp2 / 2 + random(reward_exp2 / 2);
                if(reward_exp2 > 800) reward_exp2 = 800;
#ifdef DB_SAVE
                if (MEMBER_D->is_double_reward(parter)) 
                        reward_exp2 *= 2;
#endif
                reward_pot2 = reward_exp1;
                reward_score2 = reward_exp1 / 40;
                /*
                message("channel:rumor",HIM"【鏢局傳聞】"+query("name", me)+
                        "率領的鏢隊歷經千辛萬苦，終於順利抵達！\n" NOR,
                        users());
                */
                tell_object(me, HIW "在此次運鏢中你獲得了" +
                            CHINESE_D->chinese_number(reward_exp1) + "點實戰經驗、" +
                            CHINESE_D->chinese_number(reward_pot1) + "點潛能\n及" +
                            CHINESE_D->chinese_number(reward_score1) + "點綜合評價獎勵！\n" NOR);

                tell_object(parter, HIW "在此次運鏢中你獲得了" +
                            CHINESE_D->chinese_number(reward_exp2) + "點實戰經驗、" +
                            CHINESE_D->chinese_number(reward_pot2) + "點潛能\n及" +
                            CHINESE_D->chinese_number(reward_score2) + "點綜合評價獎勵！\n" NOR);

                addn("quest_yunbiao/reward_exp", reward_exp1, me);
                addn("quest_yunbiao/reward_potential", reward_pot1, me);
                addn("combat_exp", reward_exp1, me);
                addn("potential", reward_pot1, me);
                addn("score", reward_score1, me);
       
                addn("quest_yunbiao/reward_exp", reward_exp2, parter);
                addn("quest_yunbiao/reward_potential", reward_pot2, parter);
                addn("combat_exp", reward_exp2, parter);
                addn("potential", reward_pot2, parter);
                addn("score", reward_score2, parter);

                delete_temp("quest_yunbiao/have_task", me);
                set_temp("quest_yunbiao/finished_time", time(), me);
                delete_temp("quest_yunbiao/have_task", parter);
                set_temp("quest_yunbiao/finished_time", time(), parter);
                delete_temp("quest_yunbiao/bandit_killed", me);
                delete_temp("apply/short", me);
                delete_temp("quest_yunbiao/bandit_killed", parter);
                delete_temp("apply/short", parter);
              
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        }   
        return 1;
}

int destroy1(object ob)
{
        object me, parter;

        if (! objectp(ob) || !environment(ob))
                return 1;

        if (objectp(ob) && ! present(query("owner", ob), environment(ob)) 
        &&  ! present(query("parter"), environment(ob)))
        {
                me=find_player(query("owner", ob));
                if( !me)me=find_living(query("owner", ob));
                
                parter=find_player(query("parter", ob));
                if( !parter)parter=find_living(query("parter", ob));
                
                if (objectp(me))
                {
                        delete_temp("quest_yunbiao", me);
                        delete_temp("apply/short", me);
                }
                if (objectp(parter))
                {
                        delete_temp("quest_yunbiao", parter);
                        delete_temp("apply/short", parter);
                }

                message("channel:rumor", HIB "【鏢局傳聞】" + query("owner_name") +
                        "率領的鏢隊在半路讓人給劫了！\n" NOR, 
                        users());
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        } else
        {
                remove_call_out("destroy1");
                call_out("destroy1",2,ob);
                return 1;
        }
}

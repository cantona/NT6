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
        set_name(HIW "鏢車" NOR, ({ "biao che", "cart", "che" }));
        set_weight(300000);
        set("no_get", 1);
        set("unit", "輛");
        set("value", 0);
        set("long", 
                HIW "一輛福威鏢局的鏢車，一干鏢頭正準備趕車(drive)起程呢。" NOR); 
        set("no_clean_up",1);
        setup();
        call_out("destroy1", 2, this_object());
}

void init()
{
        if( query("id", this_player()) == query("owner", this_object()) )
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
        object me;
        if (objectp(ob))
        {
                /*
                message("channel:rumor", MAG "【鏢局傳聞】由於" + query("owner_name") +
                        "護送的鏢車未能如期抵達，福威鏢局已派人前去接管鏢車！\n" NOR, users());
                */
                tell_object(all_inventory(environment(ob)),
                            HIW "忽然，遠遠走來一羣人，原來是總鏢頭派人前來了，為首的鏢師\n" +
                            "邊走嘴裏還邊罵道：“他奶奶的！等了這麼久也還沒到，總鏢頭\n" +
                            "還以為讓人給劫了，害老子白跑一趟！”説完，一干人等拉起鏢\n" +
                            "車，揚長而去！\n" NOR);

                remove_call_out("destroy1");
                remove_call_out("destroy2");

                me=present(query("owner", ob),environment(ob));
                if (objectp(me))
                {
                        delete_temp("apply/short", me);
                        delete_temp("quest_yunbiao/have_task", me);
                        set_temp("quest_yunbiao/finished_time", time(), me);
                }
                destruct(ob);
        }
        return 1;
}


int do_gan(string arg)
{        
        object me, ob, env, obj, robber, *killer;
        string item, dir, dest, target;
        int reward_exp, reward_pot, reward_score, flag, i;
        int lvl;

        mapping exit;
        me = this_player();
        ob = this_object();

        if (! arg) return notify_fail("你要趕什麼？\n");

        if( query("id", me) != query("owner", ob) )
                return notify_fail("你趕的不是自己的鏢車吧？\n"); 

        if (sscanf(arg, "%s to %s", item, dir) != 2 
        ||  item != "biao che" && item != "che")
                return notify_fail("指令：gan 鏢車 to 方向 \n");        
                        
        if (me->is_busy())
                return notify_fail("你現在正忙着哩。\n");

        flag = 0;
        killer = all_inventory(environment(me));
        for (i = 0; i < sizeof(killer); i++)
        {
                if (objectp(killer[i]) 
                 && query("want_kill", killer[i]) == query("id", me) )
                flag = 1;
        }

        if (flag)   
                return notify_fail(CYN "你還是先把眼前的敵人解決了再説吧！\n" NOR);
        
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
                if (ob->move(obj) && me->move(obj)) 
                {
                        all_inventory(env)->follow_me(me, dir);
                        message_vision(HIG "$N趕着鏢車駛了過來。\n" NOR, me);
                        lvl = me->query_skill("driving"); 
                        if (random(lvl + 100) < 50) 
                        me->start_busy(random(2) + 2);
                        else me->start_busy(1);
                        if (me->can_improve_skill("driving")) 
                                me->improve_skill("driving", 1); 
                }

                if( random(12)<2 && !query("no_fight", environment(ob)) )
                {
                        robber = new(__DIR__"robber");
                        set("want_kill",query("id",  me), robber);
                        robber->move(environment(ob));  
                        robber->kill_ob(me);
                        robber->check_me();  
                        me->start_busy(1);
                        robber->start_busy(1);
                }
        } else
        {
                reward_exp=query("combat_exp", me)/30000;
                reward_exp=reward_exp+query_temp("quest_yunbiao/bonus", me)*20;
                reward_exp = reward_exp / 2 + random(reward_exp);
                if (reward_exp > 500) reward_exp = 500;
#ifdef DB_SAVE
                if (MEMBER_D->is_double_reward(me)) 
                        reward_exp *= 2;
#endif
                reward_pot = reward_exp;
                reward_score = reward_exp / 40;
                /*
                message("channel:rumor",HIM"【鏢局傳聞】"+query("name", me)+
                        "運送的鏢車歷經千辛萬苦，終於順利抵達！\n" NOR,
                        users());
                */
                tell_object(me, HIW "在此次運鏢中你獲得了" +
                            CHINESE_D->chinese_number(reward_exp) + "點實戰經驗、" +
                            CHINESE_D->chinese_number(reward_pot) + "點潛能及\n" +
                            CHINESE_D->chinese_number(reward_score) + "點綜合評價獎勵！\n" NOR);

                addn("quest_yunbiao/reward_exp", reward_exp, me);
                addn("quest_yunbiao/reward_potential", reward_pot, me);
                addn("combat_exp", reward_exp, me);
                addn("potential", reward_pot, me);
                addn("score", reward_score, me);

                delete_temp("quest_yunbiao/have_task", me);
                set_temp("quest_yunbiao/finished_time", time(), me);
                delete_temp("apply/short", me);
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        }   
        return 1;
}

int destroy1(object ob)
{
        object me;

        if (! objectp(ob) || ! environment(ob))
                return 1;

        if (objectp(ob) && ! present(query("owner", ob), environment(ob)))
        {
                me=find_player(query("owner", ob));
                if( !me)me=find_living(query("owner", ob));
                if (objectp(me))
                {
                        delete_temp("quest_yunbiao", me);
                        delete_temp("apply/short", me);
                }

                message("channel:rumor", HIB "【鏢局傳聞】" + query("owner_name") +
                        "護送的鏢車在半路讓人給劫了！\n" NOR, users());
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        } else
        {
                remove_call_out("destroy1");
                call_out("destroy1", 2, ob);
                return 1;
        }
}

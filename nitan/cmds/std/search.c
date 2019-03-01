// search.c

// 在一個ROOM中尋找物品
// 由于SCORE的不同，尋找的對象和幾率也不同。
// ROOM可以設置環境變量：search_objects，這樣可以指定在在這
// 個房間中的某些物品的搜索幾率。也可以設置no_search 指明如
// 果江湖閱歷小于某一個值就不能找到（如果該值為零，那麼將不
// 查閱該人的江湖閱歷，這個物品將絕對不可能找到）。這兩個變
// 量可以是設置房屋的正式變量也可以是臨時變量，正是變量表示
// 房屋的環境，臨時變量表示是房屋臨時的搜尋信息。

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object env;

        seteuid(getuid());

        env = environment(me);

        if (me->is_busy())
                return notify_fail("等你忙玩了手頭的事情再找吧！\n");

        if (me->is_fighting())
                return notify_fail("一邊打架一邊找東西？只有你才想得出來！\n");

        if( query("no_search", env) == "all" )
                return notify_fail("這地方看來找不出什麼東西...\n");

        set_temp("pending/searching", 1, me);
        me->set_short_desc("正在東張西望。");
        message("vision", me->name() + "東瞅瞅、西望望，幹什麼呢？\n",
                environment(me), ({ me }));
        tell_object(me, "你開始在這裡摸索，看有沒有什麼值錢的東西。\n");
        me->start_busy(bind((:call_other, __FILE__, "searching" :), me),
                       bind((:call_other, __FILE__, "halt_searching" :), me));
        return 1;
}

mapping query_default_objects(object me)
{
        int score=query("score", me);

        if( !query("outdoors", environment(me)) )
                return ([ ]);

        if (score < 100)
                return ([
                  "/clone/money/coin"       : 100000,
                  "/clone/money/silver"     : 20000,
                  "/clone/misc/jinchuang"   : 20000,
                  "/clone/weapon/dagger"    : 20000,
                  "/d/city/npc/obj/jiudai"  : 10000,
                  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
        if (score < 400)
                return ([
                  "/clone/money/coin"       : 10000,
                  "/clone/money/silver"     : 15000,
                  "/clone/misc/jinchuang"   : 15000,
                  "/clone/weapon/dagger"    : 8000,
                  "/d/city/npc/obj/jiudai"  : 8000,
                  "/clone/weapon/duanjian"  : 3000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
        if (score < 2000)
                return ([
                  "/clone/money/coin"       : 5000,
                  "/clone/money/silver"     : 10000,
                  "/clone/misc/jinchuang"   : 25000,
                  "/clone/weapon/dagger"    : 20000,
                  "/d/city/npc/obj/jiudai"  : 10000,
                  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
        if (score < 10000)
                return ([
                  "/clone/money/silver"     : 10000,
                  "/clone/misc/jinchuang"   : 20000,
                  "/clone/weapon/dagger"    : 10000,
                  "/d/city/npc/obj/jiudai"  : 5000,
                  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
                return ([
                  "/clone/weapon/changjian" : 8000,
                  "/clone/weapon/blade"     : 8000,
                  "/clone/weapon/gangzhang" : 8000,
                  "/clone/cloth/tiejia"     : 2500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
}

//object found(object me, object env)
mixed found(object me, object env)
{
        mixed  *st;
        mapping cs, ns;
        mapping os;
        object  ob, task_ob;
        mixed   sob;
        int sum;
        int i;

        os = query_default_objects(me);
        if( mapp(cs=query_temp("search_objects", env)) )
                os += cs;

        if( mapp(cs=query("search_objects", env)) )
                os += cs;

        sum=query("score", me)>>7;
        if( mapp(ns=query_temp("no_search", env)) )
        {
                st = keys(ns);
                for (i = 0; i < sizeof(st); i++)
                {
                        if (! ns[st[i]] || sum < ns[st[i]])
                                // can not search this object or
                                // need score
                                map_delete(os, st[i]);
                }
        }

        if( mapp(ns=query("no_search", env)) )
        {
                st = keys(ns);
                for (i = 0; i < sizeof(st); i++)
                {
                        if (! ns[st[i]] || sum < ns[st[i]])
                                // can not search this object or
                                // need score
                                map_delete(os, st[i]);
                }
        }

        if (sum > 30) sum = 30;
        if( query_temp("been/searched", env)>0 )
                sum-=query_temp("been/searched", env);
        if (random(sum + 100) < 93)
                return 0;

        st = keys(os);
        sum = 0;
        for (i = 0; i < sizeof(st); i++)
        {
                if (! intp(os[st[i]]))
                        os[st[i]] = 0;
                sum += os[st[i]];
        }

        if (! sum) return 0;
        sum = random(sum);
        for (i = 0; i < sizeof(st); i++)
        {
                if (sum < os[st[i]])
                {
                        if (stringp(st[i]))
                        {
                                if (objectp(task_ob = get_object(st[i])) &&
                                    sscanf(st[i], "/task/obj/%*s"))
                                {
                                        object boss;

                                        if( !random(5) )
                                                ob = task_ob;
                                        else {
                                                FUBEN_D->enter_fuben(me, "ultra");
                                                boss = new("/maze/ultra/npc/yaowang");
                                                boss->move(get_object("/f/ultra/"+query("id", me)+"/maze/exit"));
                                                task_ob->move(boss);
                                                get_object("/f/ultra/"+query("id", me)+"/maze")->set_display_map(1);
                                                get_object("/f/ultra/"+query("id", me)+"/maze")->set_maze_boss(boss);
                                                tell_object(me, "咦，這裡好象有個隱蔽的迷宮，你撕下封條進入迷宮大門。\n");
                                                delete_temp("search_objects", env); 
                                                return 1;
                                        }
                                        delete_temp("search_objects", env);
                                }
                                else
                                        ob = new(st[i]);
                        }
                        else
                        if (objectp(st[i]))
                                ob = st[i];
                        else
                        if (functionp(st[i]))
                                ob = evaluate(st[i], me, env);

                        if (! objectp(ob))
                                return 0;

                        addn_temp("been/searched", 15, env);
                        return ob;
                }
                sum -= os[st[i]];
        }

        return 0;
}

int searching(object me)
{
        object env;
        mixed ob;

        env = environment(me);
        if( me->add_temp("pending/searching",1)>6 )
        {
                tell_object(me, "找了半天，你還是一無所獲，只好先放棄了。\n");
                message("vision", me->name() + "嘆了口氣，發了發呆。\n", env, ({ me }));
                me->set_short_desc(0);
                return 0;
        }

        if( query("qi", me)<30 || 
            query("jing", me)<30 )
        {
                tell_object(me, "你實在太疲倦了，只好放棄了尋找。\n");
                message("vision", me->name() + "嘆了口氣，一臉倦容。\n",
                        env, ({ me }));
                me->set_short_desc(0);
                return 0;
        }

        me->receive_damage("qi", 30);
        me->receive_damage("jing", 30);

        ob = found(me, env);
        if (intp(ob) && ob > 0)
        {
                me->set_short_desc(0);
                return 0;
        }
        if (objectp(ob))
        {
                if( query("base_unit", ob) )
                        ob->set_amount(random(5) + 1);
                tell_object(me,HIC"你突然發現了一"+query("unit", ob)+
                                ob->name() + HIC "！\n");
                message("visoin", me->name() + "突然彎下腰，不知道從地"
                        "上撿起了什麼東西，眉開眼笑的。\n", env, ({ me }));
                if (! ob->move(me, 1))
                {
                        tell_object(me, "可惜" + ob->name() + "對你來"
                                    "說太重了，你只好先放在地上。\n");
                }
                delete_temp("pending/searching", me);
                addn("score", 1, me);
                me->set_short_desc(0);
                return 0;
        } else
        {
                message_vision(random(2) ? "$N繼續東張西望的到處瞅。\n"
                                         : "$N時而彎下腰在地上撥拉什麼東西。\n",
                               me);
                return 1;
        }
}

int halt_searching(object me)
{
        object env;

        env = environment(me);
        delete_temp("pending/searching", me);
        tell_object(me, "你放棄了尋找。\n");
        message("vision", me->name() + "舒展了一下腰，嘆了口氣。\n", env, ({ me }));
        me->set_short_desc(0);
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: search

在地上尋找東西。能找到什麼呢？只有天才知道，某些地方能夠找到
好東西。不過大部分地方只能找到一些普通的東西。如果你找到了東
西，你的江湖閱歷將會因此而增長一點。

HELP );
        return 1;
}

// Yanwu.c 煙霧彈

#include <command.h>
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "麝香粉" NOR, ({ "shexiang fen" }) );
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一包散發出異香的藥粉。它可以用(apply)來散發香味，借機逃走。\n");
                set("unit", "包");
                set("value", 100000);
                set("no_sell", 1);
                set("can_apply_for_wimpy", 1);
        }
        setup();
}

void init()
{
        add_action("do_apply","apply");
}

int apply_for_wimpy(object me)
{
        object *obs;
        int i;
        int sc;

        if (me->is_busy())
                return notify_fail("你現在正在忙著呢。\n");

        me->clean_up_enemy();
        if (me->is_fighting())
        {
                obs = me->query_enemy();
                for (i = 0; i < sizeof(obs); i++)
                {
                        if (! living(obs[i]))
                                continue;
                        sc=query("score", obs[i])-
                             query("score", me);
                        if (sc < 0) continue;
                        if (sc > 500000) sc = 500000;
                        if (sc / 4 + random(sc) > 200000)
                        {
                                message_vision("\n$N掏出麝香粉就往空中一洒，然而$n"
                                               "大喝一聲道：“也不看看" +
                                               RANK_D->query_self(obs[i]) +
                                               "行走江湖有多少年，你居然還敢玩這種把戲？”\n"
                                               "說罷只見$n伸手一揮，將$N的香粉全部震開。\n",
                                               me, obs[i]);
                                destruct(this_object());
                                return 1;
                        }
                }
        }

        set_temp("no_follow", 1, me);
        tell_room(environment(me), HIM "\n忽然一陣異香傳來，真是"
                                   "沁人心肺，舒泰無比，眾人一時間只想睡覺。\n" NOR);

        set_temp("success_flee", "你借著眾人迷亂成功的逃走了。\n", me);
        GO_CMD->do_flee(me);
        destruct(this_object());
        return 1;
}

int do_apply(string arg)
{
        if (! arg || ! id(arg))
                return notify_fail("你要用什麼？\n");

        return apply_for_wimpy(this_player());
}
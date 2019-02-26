// trick.c 鬼話連篇
// Created by Doing Lu 10/7/2K

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

string name() { return HIM "鬼話連篇" NOR; }

int perform(object me, string skill)
{
        int heal;
        int ap, dp;
        object target;

        if( query("jing", me)<50 )
                return notify_fail("你的精神不濟，難以構思謊言。\n");

        me->clean_up_enemy();
        target = me->select_opponent();

        if (! me->is_fighting())
                return notify_fail("你又不是在打架，沒事説謊幹什麼？\n");

        if( !query("can_speak", target) || query("not_living", target) )
                return notify_fail("可惜啊！看來" + target->name() +
                                   "是聽不懂你的話了。\n");

        message_vision(HIM "$N" HIM "情急生智，對着$n" HIM
                       "就來了一套長篇大論，當真是天花亂墜。\n",
                       me, target);
        ap = me->query_int();
        dp = target->query_int();
        if( query("character", me) == "狡黠多變" )
                ap += ap / 4;
        if( query("character", me) == "陰險奸詐" )
                ap += ap / 6;

        me->receive_damage("jing", 30 + random(20));

        if (ap / 3 + random(ap) > random(dp + 10))
        {
                // 施展鬼話連篇成功
                message_vision(HIM "$n" HIM "聽得暈暈乎乎，不知所以，"
                               "手只是緩了一緩，$N" HIM "趁機溜走。\n" NOR,
                               me, target);
                set_temp("success_flee", HIG"你成功的逃走了！\n"NOR, me);
                GO_CMD->do_flee(me);
        } else
        {
                message_vision(CYN "$n" CYN "冷冷的等$N" CYN
                               "説完，才道：“你還是認命了吧"
                               "！”説罷就是一招！\n" NOR,
                               me, target);
                me->start_busy(1 + random(4));
        }

        return 1;
}
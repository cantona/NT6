// lighting.c 連鎖閃電
// Created by Vin 8/5/2002

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIW "□□□□" NOR; }

#define LIGHTING "「" HIW "□□□□" NOR "」"

int perform(object me, object target)
{
        string msg;
        int damage;

        if (! wizardp(me) && me->query("id") != "vin")
                return notify_fail(LIGHTING "只能由巫師施展。\n");

        if (! me->is_fighting())
                return notify_fail(LIGHTING "只能對戰鬥中的對手使用。\n");

        target = me->select_opponent();

        if (! target || ! target->is_character()
           || target->query("not_living"))
                return notify_fail("你打算對誰施展" LIGHTING  "？\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "施展法□「" HIW "□□□□" NOR +
              WHT "」，高□念□道：比迪姆﹒□特蒙﹒泰裡阿普﹒埃控。\n" NOR;

        me->start_busy(1);

        if (wiz_level(target) <= wiz_level(me)
           && target->query("id") != "vin")
        {
                damage = 8000 + random(8000);
                target->receive_wound("qi", damage, me);
                target->receive_wound("jing", damage / 2, me);

                msg += HIW "霎□只□□道□□□天而降，□□劈在$n"
                       HIW "身上，直劈得$n" HIW "七□生□、血肉四□。\n" NOR;
        } else
        {
                msg += HIW "霎□只□□道□□□天而降，□□劈在$n"
                       HIW "身上，青□散□，$n" HIW "□是一□事情也□有。\n" NOR;
        }
        message_combatd(msg, me, target);
        me->want_kill(target);

        if (! target->is_killing(me))
                target->kill_ob(me);
        return 1;
}

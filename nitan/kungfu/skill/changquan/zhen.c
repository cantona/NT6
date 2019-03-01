// gladiator

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "八震字決" NOR; }

int perform(object me, object target)
{
        string msg;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name()+"只能空手施展。\n");

        if ((int)me->query_skill("changquan", 1) < 80)
                return notify_fail("你太祖長拳不夠嫻熟，難以施展"+name()+"。\n");

        if (me->query_skill_mapped("cuff") != "changquan")
                return notify_fail("你沒有激發太祖長拳，難以施展"+name()+"。\n");

        if (me->query_skill_prepared("changquan") != "changquan")
                return notify_fail("你沒有準備太祖長拳，難以施展"+name()+"。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不足，難以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "霎時間只見$N" HIY "跨立馬步，穩定下盤，雙拳有章有法的依次擊向$n"
              HIY "全身各處。\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -50, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1 + random(3));
        return 1;
}
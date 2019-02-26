#include <ansi.h>

inherit F_SSERVER;

string name() { return HIG "千蛇出洞" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int lvl;
        int i;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("你必須手持一把杖才能施展" + name() + "！\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，無法施展" + name() + "！\n");

        if ((lvl = (int)me->query_skill("lingshe-zhangfa", 1)) < 120)
                return notify_fail("你的靈蛇杖法還不到家，無法使用" + name() + "！\n");

        if (me->query_skill_mapped("staff") != "lingshe-zhangfa")
                return notify_fail("你沒有激發靈蛇杖法，無法使用" + name() + "！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "大喝一聲，撲身上前，手中的" + weapon->name() +
              HIW "化作萬道光芒，一齊射向$n" HIW "！\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "$n" HIY "見$N" HIY "把" + weapon->name() +
                       HIY "使得活靈活現，猶如真物一般，實在是難以抵擋，只有後退。\n" NOR;
                count = lvl / 20;
                addn_temp("apply/attack", count, me);
        } else
                count = 0;

        message_combatd(msg, me, target);
        addn("neili", -100, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}

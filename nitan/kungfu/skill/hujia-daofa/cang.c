#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "八方藏刀勢" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 180)
                return notify_fail("你的胡家刀法還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("你沒有激發胡家刀法，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "輕舒猿臂，施出「戰八方藏刀式」，手中的" + weapon->name() +
              HIW "吞吞吐吐，變化莫測，籠罩了$n" HIW "周身要害！\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "$n" HIY "見來招實在是變幻莫測，不由得心"
                       "生懼意，招式登時出了破綻！\n" NOR;
                count = me->query_skill("hujia-daofa", 1);
        } else
        {
                msg += HIC "$n" HIC "心底微微一驚，打起精神小心接招。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -220, me);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(1 + random(4));
        return 1;
}

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "推天獻印勢" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

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

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 120)
                return notify_fail("你的胡家刀法還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("你沒有激發胡家刀法，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "橫過手中" + weapon->name() +  HIY "，施出「推天獻"
              "印勢」，雙手握刀，將整個刀鋒向$n" HIY "緩緩推進！\n"NOR;

        ap = attack_power(me, "blade") + me->query_skill("force", 1);
        dp = defense_power(target, "force") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "何曾見過如此高明的刀法，"
                                           "一聲慘叫，刀鋒已入體三分，鮮血四處噴濺！\n" NOR);
                me->start_busy(2);
                if (ap / 3 + random(ap / 2) > dp && ! target->is_busy())
                        target->start_busy(ap / 100 + 3);
        } else
        {
                msg += CYN "$p" CYN "大吃一驚，也不招架，當即向後"
                       "橫移數尺，避開了$P" CYN "這一招。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

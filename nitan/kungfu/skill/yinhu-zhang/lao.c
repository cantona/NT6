#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "大海撈針" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me))
           || (string)query("skill_type", weapon) != "staff")
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 140)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)query("neili", me) < 200)
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("yinhu-zhang", 1) < 100)
                return notify_fail("你銀瑚杖法火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "yinhu-zhang")
                return notify_fail("你沒有激發銀瑚杖法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIM "\n$N" HIM "一聲暴喝，猛然間騰空而起，施出絕招「" HIW "大海撈"
              "針" HIM "」，手中" + weapon->name() + HIM "從天而降，氣勢驚人地"
              "襲向$n" HIM "。\n" NOR;

        message_sort(msg, me, target);

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           HIR "$n" HIR "完全無法看清招中虛實，只"
                                           "聽「□」地一聲，已被$N" HIR "擊中肩膀。\n" NOR);
                me->start_busy(3);
                addn("neili", -180, me);
        } else
        {
                msg = CYN "可是$n" CYN "奮力招架，左閃右避，好不容"
                       "易抵擋住了$N" CYN "的攻擊。\n" NOR;
                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
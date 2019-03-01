#include <ansi.h>
#include <combat.h>

string name() { return HIY "奇門五轉" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("luoying-shenzhang", 1) < 120)
                return notify_fail("你的落英神劍掌不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("qimen-wuxing", 1) < 120)
                return notify_fail("你對奇門五行的研究不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "luoying-shenzhang")
                return notify_fail("你沒有激發落英神劍掌，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "luoying-shenzhang")
                return notify_fail("你沒有準備落英神劍掌，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的內力不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "掌勢陡然一變，施出落英神劍掌「奇門五轉」絕技，虛虛"
              "實實的攻向$n" HIY "。\n" NOR;

        ap = attack_power(me, "strike") +
             (int)me->query_skill("qimen-wuxing", 1) +
             me->query_int()*10;

        dp = defense_power(target, "parry") +
             (int)target->query_skill("qimen-wuxing", 1) +
             target->query_int()*10;

        addn("neili", -150, me);
        if (ap / 2 + random(ap) > dp)
        {
                target->start_busy(2 + random(3));
                me->start_busy(2);
                damage = damage_power(me, "strike");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "大吃一驚，登時接連中掌，"
                                           "狂噴出一口鮮血，身子急轉個不停。\n" NOR);
        } else
        {
                me->start_busy(3);
                msg += HIC "可是$p" HIC "看破了$P" HIC "的企圖，連消帶打，避開了$P"
                       HIC "這一擊。\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

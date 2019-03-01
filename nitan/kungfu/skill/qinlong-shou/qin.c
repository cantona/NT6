//edit by gladiator 擒龍打

#include <ansi.h>
#include <combat.h>

#define QIN "「" HIR "擒龍打" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string wn, msg;

        if (! target) target = offensive_target(me);

        if( userp(me) && me->query_skill("qinlong-shou",1)<120 && !query("can_perform/qinlong-shou/qin", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIN "只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你使用的武器不對，難以施展" QIN "。\n");

        if (me->query_skill("force") < 100)
                return notify_fail("你的內功的修為不夠，難以施展" QIN "。\n");

        if (me->query_skill("qinlong-shou", 1) < 100)
                return notify_fail("你的擒龍手修為不夠，難以施展" QIN "。\n");

        if (me->query_skill_mapped("hand") != "qinlong-shou")
                return notify_fail("你沒有激發擒龍手，難以施展" QIN "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你現在真氣不夠，難以施展" QIN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wn = weapon->name();

        msg = HIC "$N" HIC "施出「" HIR QIN HIC "」絕技，" +
              HIC "微作龍吟，雙手曲成爪抓向$n" HIC "。\n" NOR;

        ap = me->query_skill("hand");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap * 2 / 3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -150, me);
        } else
        {
                msg += CYN "可是$p" CYN "並不慌亂，收斂心神，輕輕格擋開了$P"
                       CYN "的劍招。\n"NOR;
                me->start_busy(3);
                addn("neili", -60, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        addn("neili", -damage, target);

        if( query("neili", target)<0 )
                set("neili", 0, target);

        return  HIR "結果$n" HIR "不慎被$N" HIR "手指射出的"
                "指氣爪中勞宮穴，全身真氣不禁狂泄而出！\n" NOR;
}
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "萬毒噬體" NOR; }

string final(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功不夠火候，難以施展" + name() + "。\n");

        if ((int)me->query_skill("wudu-shenzhang", 1) < 150)
                return notify_fail("你的五毒神掌不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "wudu-shenzhang")
                return notify_fail("你現在沒有準備五毒神掌，難以施展" + name() + "。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "將體內真氣運于雙掌之間，只見雙掌微微泛出紫光，猛"
              "地拍向$n。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {

                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                          (: final, me, target, damage :));

                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "眼明手快，側身一跳$P"
                       CYN "已躲過$N這招。\n" NOR;
                me->start_busy(3);
                target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int ap, dp;

        ap = me->query_skill("strike");
        dp = target->query_skill("force");

        target->affect_by("wudu_shenzhang",
                (["level":query("jiali", me)+random(query("jiali", me)),
                   "id":query("id", me),
                   "duration" : ap / 70 + random(ap / 30) ]));

        target->receive_wound("jing", damage / 5, me);

        return  HIR "只見$n" HIR "被$N" HIR "一掌拍中"
                "，倒退幾步，卻見臉色已微微泛黑。\n" NOR;

}
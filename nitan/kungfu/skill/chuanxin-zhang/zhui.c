#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "穿心錐" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("chuanxin-zhang", 1) < 100)
                return notify_fail("你的穿心掌不夠嫻熟，不會使用" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，無法使用" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "chuanxin-zhang")
                return notify_fail("你沒有激發穿心掌，無法使用" + name() + "！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "\n$N" HIY "一聲冷笑，雙掌一錯，陡然施出一招"
              "「" HIW "穿心錐" HIY "」，幻出千百之手掌一齊"
              "插向$n" HIY "！" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "strike");
                addn("neili", -150, me);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                          HIR "結果$p" HIR "沒能避開$P" HIR
                                          "變幻莫測的掌法，掌勁頓時透胸而過，"
                                          "口噴鮮血，幾乎摔倒！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -50, me);
                msg = CYN "可是$p" CYN "識破了$P"
                      CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
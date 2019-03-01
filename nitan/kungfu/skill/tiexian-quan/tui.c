#include <ansi.h>
#include <combat.h>

string name() { return HIW "破甲推山" NOR; }

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

        if ((int)me->query_skill("tiexian-quan", 1) < 60)
                return notify_fail("你鐵線拳法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "tiexian-quan")
                return notify_fail("你沒有激發鐵線拳法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "tiexian-quan")
                return notify_fail("你沒有準備鐵線拳法，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 80)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "parry");

        msg = HIC "\n$N" HIC "長嘯一聲，施出絕招「" HIW "開山破" HIC "」，一\n"
              "拳揮出，破空而響，直擊$n" HIC "面門和胸口。\n" NOR;

        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");

                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                          HIR "$N" HIR "出手既快，方位又奇，$n"
                                          HIR "閃避不及，悶哼一聲，已然中拳。\n" NOR);

                addn("neili", -100, me);
                me->start_busy(2);
        } else
        {
                msg = CYN "$n" CYN "不慌不忙，以快打快，將$N"
                      CYN "這招化去。\n" NOR;

                addn("neili", -30, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
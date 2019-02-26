#include <ansi.h>
#include <combat.h>

string name() { return HIW "五雷連閃" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg, wn;
        int ap, dp;
        int i, attack_time;
        int count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() +"只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("tianlei-dao", 1) < 150)
                return notify_fail("你天雷絕刀不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "tianlei-dao")
                return notify_fail("你沒有激發天雷絕刀，難以施展" + name() + "。\n");

        if (me->query_skill("dodge") < 180)
                return notify_fail("你的輕功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");


        wn = weapon->name();

        msg = HIY "\n$N" HIY "將手中" + wn + HIY "立於胸前，施出絕招「" HIW "五"
              "雷連閃" HIY "」，$N身法陡然加快，\n手中" + wn + HIY "連續砍出五刀，"
              "刀法之精妙，令人匪夷所思。\n" NOR;

        message_combatd(msg, me, target);

        attack_time = 5;

        ap = attack_power(me,"blade");
        dp = defense_power(target, "dodge");

        addn("neili", -180, me);

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 15;
                msg = HIG "$n" HIG "見$P" HIG "這招來勢洶湧，勢不可"
                     "擋，被$N" HIG "攻得連連後退。\n" NOR;
        } else
        {
                count = 0;
                msg = HIC "$n" HIC "見$N" HIC "這幾刀來勢迅猛無比，毫"
                      "無破綻，只得小心應付。\n" NOR;
        }

        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 15);
        }
        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}

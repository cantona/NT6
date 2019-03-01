#include <ansi.h>
#include <combat.h>

#define LIAN "「" HIW "天刀落雲式" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg, wn;
        int ap, dp;
        int i, attack_time;

        if( userp(me) && !query("can_perform/luoyun-dao/tian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不對，難以施展" LIAN "。\n");

        if ((int)me->query_skill("luoyun-dao", 1) < 100)
                return notify_fail("你的落雲刀法不夠嫻熟，難以施展" LIAN "。\n");

        if (me->query_skill_mapped("blade") != "luoyun-dao")
                return notify_fail("你沒有激發落雲刀法，難以施展" LIAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你目前的真氣不夠，難以施展" LIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wn = weapon->name();

        msg = HIY "\n$N" HIY "將手中" + wn + HIY "立于胸前，施出絕招「" HIW "天"
              "刀落雲式" HIY "」，$N身法陡然加快，手中" + wn + HIY "連連揮出，猶"
              "如萬馬奔騰般襲向$n" HIY "。" NOR;

        message_sort(msg, me, target);

        attack_time = 4;

        ap = me->query_skill("blade");
        dp = target->query_skill("dodge");

        attack_time += random(ap / 40);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIG "$n" HIG "見$P" HIG "這招來勢洶湧，勢不可"
                     "擋，被$N" HIG "攻得連連後退。\n" NOR;
        } else
        {
                msg = HIC "$n" HIC "見$N" HIC "這幾刀來勢迅猛無比，毫"
                      "無破綻，只得小心應付。\n" NOR;
        }

        message_combatd(msg, me, target);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(attack_time));

        return 1;
}
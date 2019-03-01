// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "誰與爭鋒" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" + name() + "。\n");

        if ((lvl = (int)me->query_skill("yitian-zhang", 1)) < 120)
                return notify_fail("你的倚天屠龍掌不夠嫻熟，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在真氣太弱，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "yitian-zhang")
                return notify_fail("你沒有激發倚天屠龍掌，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "yitian-zhang")
                return notify_fail("你沒有準備使用倚天屠龍掌，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "神氣貫通，將倚天屠龍掌二十四字一氣呵成，雙掌"
              "攜帶著排山倒海之勁貫向$n" HIY "。\n\n" NOR;
        addn("neili", -150, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "頓時覺得呼吸不暢，全然被這"
                       "股力道所制，只得拼命運動抵擋。\n" NOR;
                count = ap / 15;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "深吸一口氣，凝神抵擋，猶如輕舟立"
                       "于驚濤駭浪之中，左右顛簸，卻是不倒。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 10; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(2);
        return 1;
}

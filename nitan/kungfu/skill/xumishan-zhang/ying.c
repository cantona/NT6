// This program is a part of NITAN MudLIB
// ying.c 須彌山掌「羣山疊影」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "羣山疊影"; }

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「羣山疊影」只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用「羣山疊影」！\n");

        if ((lvl = (int)me->query_skill("xumishan-zhang", 1)) < 150)
                return notify_fail("你的須彌山掌掌不夠嫻熟，不會使用「羣山疊影」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在真氣太弱，不能使用「羣山疊影」。\n");

        if (me->query_skill_prepared("strike") != "xumishan-zhang")
                return notify_fail("你現在沒有準備使用須彌山掌，不能使用「羣山疊影」。\n");

        msg = HIY "$N" HIY "穩穩使出須彌山掌掌的絕招「羣山疊影」，雙掌"
              "平平向$n" HIY "推去，$n" HIY "頓時覺得一股排山倒海的"
              "內力向自己湧來。\n" NOR;
        addn("neili", -150, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "頓時覺得呼吸不暢，全然被這"
                       "股力道所制，只得拼命運動抵擋。\n" NOR;
                count = ap / 20;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "深吸一口氣，凝神抵擋，猶如輕舟立"
                       "於驚濤駭浪之中，左右顛簸，卻是不倒。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(2);
        return 1;
}

#include <ansi.h>
#include <combat.h>

#define HUO "「" HIR "流星火雨" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;

        if( userp(me) && !query("can_perform/honglian-dao/huo", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUO "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" HUO "。\n");

        if ((int)me->query_skill("force") < 120 )
                return notify_fail("你的內功火候不夠，難以施展" HUO "。\n");

        if ((int)me->query_skill("honglian-dao", 1) < 80)
                return notify_fail("你紅蓮刀法不夠嫻熟，難以施展" HUO "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不夠，難以施展" HUO "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，難以施展" HUO "。\n");

        if (me->query_skill_mapped("blade") != "honglian-dao")
                return notify_fail("你沒有激發紅蓮刀法，難以施展" HUO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "施出紅蓮刀法絕技，手中" + weapon->name() +
              HIR "運轉如飛，激起層層熱浪席卷$n" HIR "周身！\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -80, me);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(4));
        return 1;
}
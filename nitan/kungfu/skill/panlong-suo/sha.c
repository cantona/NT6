#include <ansi.h>

#define SHA "「" HIR "絕命七殺" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i;

        if( userp(me) && !query("can_perform/panlong-suo/sha", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHA "只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對，難以施展" SHA "。\n");

        if ((int)me->query_skill("force") < 220)
                return notify_fail("你的內功火候不夠，難以施展" SHA "。\n");

        if ((int)me->query_skill("panlong-suo", 1) < 180)
                return notify_fail("你的霹靂盤龍索還不到家，難以施展" SHA "。\n");

        if (me->query_skill_mapped("whip") != "panlong-suo")
                return notify_fail("你沒有激發霹靂盤龍索，難以施展" SHA "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" SHA "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "突然間$N" HIR "猛的猱身撲上，手中" + weapon->name() +
              HIR "急轉，便似不要命般地向$n" HIR "猛攻過去。\n" NOR;

        if (random(me->query_skill("whip")) > target->query_skill("parry") / 2)
        {
                msg += HIR "$n" HIR "卒不及防，登時手忙腳亂，招架疏"
                       "散，慌忙中難以抵擋。\n" NOR;
                count = me->query_skill("whip") / 20;
        } else
        {
                msg += HIC "$n" HIC "心底一驚，連忙全神應對，不敢有"
                       "絲毫大意。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -180, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(6));
        return 1;
}
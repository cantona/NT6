#include <ansi.h>
#include <combat.h>

#define XUAN "「" HIW "玄功無極勁" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, ap, dp, damage;
        string msg;

        if( userp(me) && !query("can_perform/xuangong-quan/xuan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(XUAN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(XUAN "只能空手施展。\n");

        skill = me->query_skill("xuangong-quan", 1);

        if (skill < 120)
                return notify_fail("你的無極玄功拳等級不夠，難以施展" XUAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" XUAN "。\n");
 
        if (me->query_skill_mapped("unarmed") != "xuangong-quan")
                return notify_fail("你沒有激發無極玄功拳，難以施展" XUAN "。\n");

        if (me->query_skill_prepared("unarmed") != "xuangong-quan")
                return notify_fail("你現在沒有準備使用無極玄功拳，無法使用" XUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "只見$N" HIW "雙手回圈，慢慢的引動氣流，正當$n"
              HIW "吃驚間，$P" HIW "雙拳已陡然破空貫出。\n" NOR;
        addn("neili", -100, me);

        if (random(me->query_skill("force")) > target->query_skill("force") / 2)
        {
                me->start_busy(3);
                target->start_busy(random(3));
                
                damage = (int)me->query_skill("xuangong-quan", 1);
                damage = damage + random(damage);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "急忙抽身躲避，可已然不及，被$N"
                                           HIR "雙拳捶個正中。\n:內傷@?");
        } else 
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，並沒有上當。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
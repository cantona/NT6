#include <ansi.h>

#define CHAN "「" HIM "跗骨纏魂" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;

        if( userp(me) && !query("can_perform/panlong-suo/chan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(CHAN "只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對，難以施展" CHAN "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不夠，難以施展" CHAN "。\n");

        if ((int)me->query_skill("panlong-suo", 1) < 120)
                return notify_fail("你的霹靂盤龍索還不到家，難以施展" CHAN "。\n");

        if (me->query_skill_mapped("whip") != "panlong-suo")
                return notify_fail("你沒有激發霹靂盤龍索，難以施展" CHAN "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，難以施展" CHAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIM "$N" HIM "一聲長嘯，手中" + weapon->name() + HIM "一抖，登時"
              "幻化作萬道紫芒向$n" HIM "身上猛套過去。\n" NOR;

        if (random(me->query_skill("whip")) > target->query_skill("parry") / 2)
        {
                msg += HIR "霎時$n" HIR "只覺" + weapon->name() + HIR
                       "壓力不斷增加，便如跗骨之蛆，揮之不去。\n" NOR;
                target->start_busy((int)me->query_skill("panlong-suo") / 20 + 1);
                addn("neili", -80, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$n" CYN "小心應對，絲毫不受迷惑，縱身"
                       "躍出了$N" CYN "的籠罩。\n" NOR;
                addn("neili", -30, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
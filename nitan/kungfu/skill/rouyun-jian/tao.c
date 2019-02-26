#include <ansi.h>

#define TAO "「" HIC "三環套月" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/rouyun-jian/tao", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(TAO "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("rouyun-jian", 1) < 140)
                return notify_fail("你的柔雲劍法修為不夠，難以施展" TAO "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的內功修為不夠，難以施展" TAO "。\n");

        if (me->query_skill("dodge") < 180)
                return notify_fail("你的輕功修為不夠，難以施展" TAO "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" TAO "。\n");

        if (me->query_skill_mapped("sword") != "rouyun-jian")
                return notify_fail("你沒有激發柔雲劍法，難以施展" TAO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "使出柔雲劍法「三環套月」，一招之中另藴三招，鋪天"
              "蓋地罩向$n" HIC "！\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -150, me);

        addn_temp("apply/attack", 40, me);
              COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", 60, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", 80, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", -180, me);
        me->start_busy(1 + random(3));
        return 1;
}
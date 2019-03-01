#include <ansi.h>

#define FU "「" HIW "縛字訣" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;

        if( userp(me) && !query("can_perform/jiandun-zhusuo/fu", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FU "只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你的武器不對，難以施展" FU "。\n");

        if (me->query_skill("jiandun-zhusuo", 1) < 50)
                return notify_fail("你的劍盾珠索級別不夠，難以施展" FU "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你現在真氣不夠，難以施展" FU "。\n");

        if (me->query_skill_mapped("whip") != "jiandun-zhusuo")
                return notify_fail("你沒有激發劍盾珠索，難以施展" FU "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "右手一揚，手中" + weapon->name() +
              HIW "頓時回旋飛舞而至，迂回盤繞向$n" HIW "！\n";

        me->start_busy(1);

        if (random((int)me->query_skill("jiandun-zhusuo", 1)) > (int)target->query_skill("parry", 1) / 2)
        {
                msg += HIR "$n" HIR "只覺全身一緊，已被" + weapon->name() +
                       HIR "牢牢縛住，動彈不得！\n" NOR;
                target->start_busy((int)me->query_skill("jiandun-zhusuo") / 20 + 1);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，斜跳躲閃開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
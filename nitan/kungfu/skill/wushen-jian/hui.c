#include <ansi.h>
#include <combat.h>

#define HUI "「" HIG "回峯蜿蜒勢" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int level;

        if( userp(me) && !query("can_perform/wushen-jian/hui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" HUI "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        level = me->query_skill("wushen-jian", 1);

        if (level < 180)
                return notify_fail("你衡山五神劍不夠嫻熟，難以施展" HUI "。\n");

        if (me->query_skill_mapped("sword") != "wushen-jian")
                return notify_fail("你沒有激發衡山五神劍，難以施展" HUI "。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候不足，難以施展" HUI "。\n");

        if( query("neili", me)<160 )
                return notify_fail("你現在的真氣不夠，難以施展" HUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIG "\n$N" HIG "使出衡山五神劍「" HIC "回峯蜿蜒勢" HIG "」，"
              "手中" + weapon->name() + HIG "猛然反轉，劍勢迂迴詭異，連"
              "連襲向$n" HIG "。" NOR;

        message_sort(msg, me, target);

        addn("neili", -100, me);
        if (level + random(level) > target->query_skill("dodge", 1))
        {
                msg = HIR "劍勢迂迴間$N" HIR "招式陡然變快，$n已被$N"
                      HIR "攻的目不暇接，手忙腳亂！\n" NOR;
                target->start_busy(level / 18 + 2);
                me->start_busy(1);
        } else
        {
                msg = CYN "可是$n" CYN "看破了$N"
                      CYN "的企圖，鎮定解招，一絲不亂。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
#include <ansi.h>
#include <combat.h>

#define HUI "「" HIG "蛇困愁城" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int level, ap, dp;
        /*
        if( userp(me) && !query("can_perform/jinshe-jian/kun", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
        */
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" HUI "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        level = me->query_skill("jinshe-jian", 1);

        if (level < 140)
                return notify_fail("你金蛇劍法不夠嫻熟，難以施展" HUI "。\n");

        if (me->query_skill_mapped("sword") != "jinshe-jian")
                return notify_fail("你沒有激發金蛇劍法，難以施展" HUI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" HUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "\n$N" HIG "輕嘆一聲，手中" + weapon->name() + HIG "猶如"
              "金蛇般的纏向$n" HIG "。\n" NOR;

        message_sort(msg, me, target);

        addn("neili", -140, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "一道金光閃過，$n已被$N" HIY "攻的目不暇接，手忙腳亂！\n" NOR;
                target->start_busy(1 + random(ap / 80));
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
// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "纏字訣" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int level;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        level = me->query_skill("dagou-bang", 1);

        if (level < 60)
                return notify_fail("你打狗棒法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("你沒有激發打狗棒法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "$N" HIG "使出打狗棒法「" HIC "纏" HIG "」字訣，棒頭在"
              "地下連點，連綿不絕地挑向$n" HIG "的小腿和腳踝。\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "棒影竄動間$n" HIR "招式陡然一緊，已被$N"
                       HIR "攻的蹦跳不停，手忙腳亂！\n" NOR;
                target->start_busy(4 + random(level/60));
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N"
                       CYN "的企圖，鎮定解招，一絲不亂。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

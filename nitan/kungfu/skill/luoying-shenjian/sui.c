#include <ansi.h>
#include <combat.h>

string name() { return HIG "隨波逐流" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("luoying-shenjian", 1) < 80)
                return notify_fail("你落英神劍不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "luoying-shenjian")
                return notify_fail("你沒有激發落英神劍，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "$N" HIG "手中" + weapon->name() + HIG "疾轉，劍幕繚繞，引得周"
              "圍氣流波動不已，籠罩$n" HIG "四方。\n" NOR;

        addn("neili", -80, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "$n" HIR "勘不透$N" HIR "招中奧妙，不敢擅自出招，頓時"
                       "便失了先機。\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "不慌不忙，看破了此招"
                       "虛實，並沒有受到半點影響。\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
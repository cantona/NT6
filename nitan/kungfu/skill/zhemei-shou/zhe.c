// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "折梅式" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int skill, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        skill = me->query_skill("zhemei-shou", 1);

        if (skill < 80)
                return notify_fail("你的折梅手等級不夠，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 120)
                return notify_fail("你內功火候不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "合逍遙折梅手諸多變化為一式，隨手輕輕揮出，虛虛"
              "實實籠罩$n" HIC "全身諸處要穴。\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");

        addn("neili", -80, me);
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -50, me);
                msg += HIR "$n" HIR "心頭一顫，想不出破解之法，急忙後"
                      "退數步，一時間無法反擊。\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN "的企圖，絲"
                      "毫不為所動，讓$P" CYN "的虛招沒有起得任何作用。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}
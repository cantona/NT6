// chan.c 天魔纏身

#include <ansi.h>

inherit F_SSERVER;

string name() { return "天魔纏身"; }

int perform(object me, object target)
{
        object weapon;
        int level, b;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「天魔纏身」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if (!living(target))
                return notify_fail("對方已經不能戰鬥了！\n");

        if ((level = me->query_skill("tianmo-jian", 1)) < 160)
                return notify_fail("你的天魔劍法不夠嫻熟，不會使用「天魔纏身」。\n");

        if( query("neili", me)<80 )
                return notify_fail("你現在真氣不夠，無法使用「天魔纏身」。\n");

        msg = HIM "$N" HIM "使出天魔劍法「天魔纏身」，默運口訣，將手中"
              + weapon->name() + HIM "一抖，立時發出一陣攝人心魂的聲音。\n" NOR;

        addn("neili", -60, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(2) > dp)
        {
                msg += HIR "結果$p" HIR "頓覺神智不定，心燥意亂，"
                       "全然不知身在何處，呆立當場！\n" NOR;
                b = level / 20;
                if (b > 8)   b = 8;
                target->start_busy(b);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，連忙"
                       "運功將心神護住。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}

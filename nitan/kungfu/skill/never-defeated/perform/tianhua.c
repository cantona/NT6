// tianhua.c 天花亂墜

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("天花亂墜只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必須手持兵刃才能施展天花亂墜！\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if ((int)me->query_skill("never-defeated", 1) < 100)
                return notify_fail("你的不敗神功不夠深厚，不會使用天花亂墜。\n");

        if (me->query_skill_mapped("sword") != "never-defeated") 
                return notify_fail("你現在沒有激發不敗神功為劍法，難以施展天花亂墜。\n"); 
                
       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "手中的" + weapon->name() + HIC
              "一勾一劃，簡單明瞭的壓向$n" HIC "！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "被$P" HIR "逼得施展不開半點招式！\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的招數，"
                       "鎮定自若，應對自如。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
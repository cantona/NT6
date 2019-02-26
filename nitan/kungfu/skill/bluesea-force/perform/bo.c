// bo.c 碧海清波

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("碧海清波只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");
                
        if ((int)me->query_skill("bluesea-force", 1) < 100)
                return notify_fail("你的南海玄功不夠深厚，不會使用碧海清波。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "掌力忽左忽右，形成一個個氣旋，如波浪一般接連向$n"
              HIC "逼去！\n" NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "被$P" HIR "逼得施展不開半點招式！\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的掌勢來路，"
                       "鎮定自若，應對自如。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
// gui.c 鬼魅身法

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("鬼魅身法只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");
                
        if ((int)me->query_skill("kuihua-mogong", 1) < 100)
                return notify_fail("你的葵花魔功不夠深厚，不會使用鬼魅身法。\n");
                
        if (me->query_skill_mapped("dodge") != "kuihua-mogong")
                return notify_fail("你沒有激發葵花魔功為特殊輕功，難以施展鬼魅身法。\n");
                
        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "身子忽進忽退，身形詭祕異常，在$n"
              HIR "身邊飄忽不定。\n" NOR;

        ap = attack_power(me, "dodge") + me->query_int();
        dp = defense_power(target, "parry") + target->query_int();

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "只能緊守門户，不敢妄自出擊！\n" NOR;
                target->start_busy(ap / 100 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的身法，並沒"
                       "有受到任何影響。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
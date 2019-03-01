// muyeyingyang.c 牧野鷹揚

#include <ansi.h>

inherit F_SSERVER;

string name() { return "牧野鷹揚"; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("牧野鷹揚只能對戰鬥中的對手使用。\n");

        if ( query_temp("weapon", me) )
                return notify_fail("搜骨鷹爪功必須空手方可施展。\n");

        if ((int)me->query_str() < 30)
                return notify_fail("你臂力不夠,不能使用牧野鷹揚！\n");

        if ((int)me->query_skill("sougu-yingzhua",1) < 150)
                return notify_fail("你的搜骨鷹爪功修為不夠,目前還不能使用牧野鷹揚！\n");

        if ((int)query("neili", me) < 800)
                return notify_fail("你內力現在不夠, 不能使用牧野鷹揚！\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if ( !living(target))
                return notify_fail("對方已經這樣了，放膽攻擊吧！\n");

        msg = HIY "$N" HIY "使出搜骨鷹爪功絕技「牧野鷹揚」，雙爪驀地抓向$n"
              HIY "的全身要穴。\n" NOR;

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "被$P" HIR "點中要穴，立時動彈不得！\n" NOR;
                target->start_busy( (int)me->query_skill("sougu-yingzhua",1) / 120 + 1);
                addn("neili", -150, me);
        } else
        {
                msg += HIG "可是$p" HIG "看破了$P" HIG "的企圖，並沒有上當。\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
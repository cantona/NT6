#include <ansi.h>
#include <combat.h>

string name() { return HIC "定崑崙" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int fmsk;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 120)
                return notify_fail("你的彈指神通不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你沒有激發彈指神通，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你沒有準備彈指神通，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "合指輕彈，頓時只聽“颼”的一聲，一縷若有若無的"
              "罡氣已朝$n" HIC "電射而去。\n" NOR;

        ap = attack_power(me,"finger");
        dp = defense_power(target,"parry");
        fmsk = me->query_skill("qimen-xuanshu", 1); 

        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                msg +=  HIR "$n" HIR "只覺脅下一麻，已被$P"
                        HIR "指氣射中，全身痠軟無力，呆立當場。\n" NOR;
                target->start_busy(ap / 80  + fmsk / 25); 
                me->start_busy(1);
                addn("neili", -100, me);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN
                       "的企圖，輕輕一躍，跳了開去。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

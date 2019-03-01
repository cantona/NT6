// shangfei.c 傷肺訣

#include <ansi.h>

inherit F_SSERVER;

string name() { return "傷肺訣"; }

private void remove_effect(object me, int amount);

int perform(object me)
{
        string msg;
        object target;
        int skill, dodge_decrease;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「傷肺訣」只能在戰鬥中使用。\n");

        if( (int)query("neili", me) < 600 )
                return notify_fail("你的內力還不夠高！\n");

        if( (int)me->query_skill("cuff") < 60 )
                return notify_fail("你的拳法還不到家，無法體現七傷拳的各種總訣！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 60)
                return notify_fail("你七傷拳的修為不夠，不能夠體會傷肺訣! \n");

        if( (int)me->query_skill("force", 1) < 60)
                  return notify_fail(HIM "你的基本內功修為不足，不能隨便使用傷肺訣! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你沒有激發七傷拳，無法運用傷肺訣！\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("你沒有準備使用七傷拳，無法施展「傷肺訣」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用此招！\n");


        msg = HIY "$N凝神定氣，使出七傷拳總訣中的「" HIR "傷肺訣" HIY "」，雙拳勢如雷霆，向$n擊去。\n"NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if( ap /2 + random(ap) > dp || !living(target))
        {
                addn("neili", -100, me);

                msg = HIG "$N的拳風隱含風雷，“澎”的一聲打在$n身上！\n$n只覺得呼吸不順，頓時腳步慢了許多！\n"NOR;
                dodge_decrease = query("apply/dodge", target) / 10;
                addn_temp("apply/dodge", -dodge_decrease, target);
                target->start_busy(2);
                me->start_busy(2 + random(2));
                call_out("remove_effect", skill/60, target, dodge_decrease);
        }
        else
        {
                msg = HIG "只見$n不慌不忙，輕輕一閃，躲過了$N的必殺一擊！\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

private void remove_effect(object me, int amount)
{
        if (!me)
                return;
        addn_temp("apply/dodge", amount, me);
        tell_object(me, "你感覺呼吸變得順暢，所中的七傷拳傷肺勁氣逐漸消解了。\n");
}
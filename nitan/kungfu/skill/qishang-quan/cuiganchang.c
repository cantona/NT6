// cuiganchang.c 摧肝腸訣

#include <ansi.h>

inherit F_SSERVER;

string name() { return "摧肝腸訣"; }

int perform(object me)
{
        string msg,str;
        object target;
        int skill, qi_wound;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「摧肝腸訣」只能在戰鬥中使用。\n");

        if( (int)query("neili", me) < 700 )
                return notify_fail("你的內力還不夠高！\n");

        if( (int)me->query_skill("cuff") < 220 )
                return notify_fail("你的拳法還不到家，無法體現七傷拳的各種總訣！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 220)
                return notify_fail("你七傷拳的修為不夠，不能夠體會摧肝腸訣! \n");

         if( (int)me->query_skill("force", 1) < 220)
                return notify_fail(HIM "你的基本內功修為不足，不能隨便使用摧肝腸訣! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你沒有激發七傷拳，無法運用摧肝腸訣！\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("你沒有準備使用七傷拳，無法施展「摧肝腸訣」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用此招！\n");


        msg = HIY "$N凝神定氣，使出七傷拳總訣中的「" HIR "摧肝腸訣" HIY "」，雙拳勢如雷霆，向$n擊去。\n"NOR;
        message_vision(msg, me, target);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if( ap /2 + random(ap) > dp || !living(target))
        {
                addn("neili", -200, me);

                msg = HIG "$n前胸中了$N全力一擊，只覺一陣劇痛，“哇”的一聲噴出一口鮮血！\n"NOR;
                qi_wound = damage_power(me, "cuff");
                qi_wound += query("jiali", me);
                if(qi_wound > query("qi", target))
                        qi_wound = query("qi", target);

                target->receive_wound("qi", qi_wound,me);
                if( !target->is_busy() )
                        target->start_busy(2);
                me->start_busy(2);
                str = COMBAT_D->status_msg((int)query("qi", target) * 100 /(int)query("max_qi", target));
                msg += "($n"+str+")\n";
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
// yihuanghu.c 意恍惚訣

#include <ansi.h>

inherit F_SSERVER;

string name() { return "意恍惚訣"; }

int perform(object me)
{
        string msg;
        object target;
        int skill;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「意恍惚訣」只能在戰鬥中使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if( (int)query("neili", me) < 1000 )
                return notify_fail("你的內力還不夠高！\n");

        if( (int)me->query_skill("cuff") < 150 )
                return notify_fail("你的拳法還不到家，無法體現七傷拳的各種總訣！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 150)
                return notify_fail("你七傷拳的修為不夠，不能夠體會意恍惚訣! \n");

          if( (int)me->query_skill("force", 1) < 150)
                  return notify_fail(HIM "你的基本內功修為不足，不能隨便使用意恍惚訣! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你沒有激發七傷拳，無法運用意恍惚訣！\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("你沒有準備使用七傷拳，無法施展「意恍惚決」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用此招！\n");


        msg = HIY "$N凝神定氣，使出七傷拳總訣中的「" HIR "意恍惚訣" HIY "」，雙拳勢如雷霆，向$n擊去。\n"NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if( ap /2 + random(ap) > dp || !living(target))
        {
                addn("neili", -300, me);

                msg = HIC "結果$N雙拳擊中時，卻是若有若無。\n$n正在奇怪間，已被$N的真氣制住，神情恍恍忽忽的！\n"NOR;
                target->start_busy(ap/80+2);
                me->start_busy(1);
        }
        else
        {
                msg = HIG "只見$n不慌不忙，輕輕一閃，躲過了$N的必殺一擊！\n"NOR;

                addn("neili", -100, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
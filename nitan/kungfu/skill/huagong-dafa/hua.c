// hua.c

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp;
        int my_max, tg_max;
        int suck;

        if (target == me) target = offensive_target(me);

        if (! environment(me)) return 0;
        if( query("no_fight", environment(me)) )
                return notify_fail("在這裡不能攻擊他人。\n");

        if (! objectp(target))
                return notify_fail("你要化誰的內力？\n");

        if( query("race", target) != "人類" )
                return notify_fail("搞錯了！只有人才能有內力！\n");

        if (me->is_busy())
                return notify_fail("你現在正忙，無法化他人內力。\n");

        my_max=query("max_neili", me);
        tg_max=query("max_neili", target);

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能施用化功大法！\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 90)
                return notify_fail("你的化功大法功力不夠，不能施展！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠，不能施展化功大法。\n");

        if( query("max_neili", me) >= me->query_neili_limit() )
                return notify_fail("你的內力修為似乎已經達到了瓶頸，再吸取也是徒勞。\n"); 


        if( query("neili", target)<10 || 
            query("max_neili", target)<10 )
                return notify_fail(target->name() +
                                   "已然內力渙散，不必再化了。\n");

        if( query("max_neili", target)>query("max_neili", me)*4/3 )
                return notify_fail( target->name() +
                        "的內功修為遠勝于你，你無法從化他的內力！\n");

        message_combatd(HIR "$N" HIR "全身骨節爆響，雙臂暴長數尺，手掌"
                        "刷的一抖，粘向$n！\n" NOR,
                        me, target);

        me->want_kill(target);
        if (living(target))
                if (! target->is_killing(me)) target->kill_ob(me);

        sp = me->query_skill("force") + me->query_skill("dodge");
        dp = target->query_skill("force") + target->query_skill("dodge");

        if ((sp / 2 + random(sp) > random(dp)) || ! living(target))
        {
                tell_object(target, HIR "你只覺天頂骨裂，全身功力"
                            "貫腦而出，如融雪般消失得無影無蹤！\n" NOR);
                suck = 1 + (me->query_skill("huagong-dafa", 1) - 90) / 8;
                addn("max_neili", -suck, target);
                addn("max_neili", suck, me);
                if( query("max_neili", target)<1 )
                        set("max_neili", 0, target);

                me->start_busy(4 + random(4));
                target->start_busy(4 + random(4));
        } else
        {       
                message_combatd(HIY "可是$p" HIY "看破了$P"
                                HIY "的企圖，內力猛地一震，借勢溜"
                                "了開去。\n" NOR, me, target);
                me->start_busy(4 + random(4));
        }

        return 1;
}

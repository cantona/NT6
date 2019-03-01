//zhou.c

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int exert(object me)
{
        string msg;
        object target;
        int skill, ap, dp, attack_decrease,dodge_decrease;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("busi-shenlong",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「咒法」只能在戰鬥中使用。\n");
        if( me->is_busy() )
                return notify_fail("你正忙著呢。\n");
        if( (int)me->query_skill("busi-shenlong", 1) < 200)
                return notify_fail(HIM "你的不死神龍心法修為不足，還無法用內力念出真言! \n" NOR);
        if( query("neili", me)<1000 || query("max_neili", me)<2000 )
                return notify_fail("你的內力不夠，無法念出真言。\n");

        message_vision(HIR "\n$N突然向後一躍，雙臂向上伸展，口中喃喃有詞......\n
                       萬年不老!永享仙福!壽與天齊!文武仁聖！\n
                       萬年不老!永享仙福!壽與天齊!文武仁聖！\n
                       萬年不老!永享仙福!壽與天齊!文武仁聖！\n\n" NOR, me);

        ap=query("combat_exp", me)/1000+skill*5;
        if(living(target))
                dp=query("combat_exp", target)/4000;
        else    dp = 0;

        if( random(ap) > dp * 2 )
        {
                if(userp(me))
                        addn("neili", -500, me);
                msg = HIM "$n聽到$N口中的咒語，突感神經錯亂，全身失去知覺一般！\n"NOR;
                attack_decrease=query("apply/attack", target)/6;
                dodge_decrease=query("apply/defense", target)/6;
                addn_temp("apply/attack", -attack_decrease, target);
                addn_temp("apply/defense", -dodge_decrease, target);
                if (! target->is_busy())
                        target->start_busy(2);
                me->start_busy(random(3));
        }
        else
        if( random(ap) > dp )
        {
                if(userp(me))
                        addn("neili", -500, me);
                msg = HIR "$n聽到$N口中的咒語，突感精神恍惚，手腳頓時不聽使喚！\n"NOR;
                attack_decrease=query("apply/attack", target)/9;
                dodge_decrease=query("apply/defense", target)/9;
                addn_temp("apply/attack", -attack_decrease, target);
                addn_temp("apply/defense", -dodge_decrease, target);
                if (! target->is_busy())
                target->start_busy(2);
                me->start_busy(random(3));
        }
        else
        {
                msg = CYN "$n眼觀鼻，鼻觀心，抱元守一，終于脫離了邪咒控制！\n"NOR;
                if(userp(me))
                        addn("neili", -400, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
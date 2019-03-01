// yijin.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
        int skill, n;

        if (target != me)
                notify_fail("你只能對自己用["+WHT+"易經轉脈"+NOR+"]來提升自已的戰鬥和防御力。\n"NOR,);

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠!");
        if( userp(me) && !query("can_perform/jiuyin-hamagong/yijin", me) )
                      return notify_fail("你所使用的外功中沒有這種功能。\n"); 

        if( query_temp("yijin", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        n = skill / 5;

        addn("neili", -400, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "深深吸了一口氣。突然雙掌撐地，雙腳朝上，只"
                        "見全身衣物逐漸膨漲起來，口中不停蛙嗚，臉色忽紅忽紫！\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        addn_temp("apply/dodge", skill/3, me);
        addn_temp("apply/parry", skill/3, me);
        addn_temp("apply/armor", skill/3, me);
                addn_temp("apply/damage", skill/2, me);
        addn_temp("apply/dispel_poison", skill/3, me);
        addn_temp("apply/reduce_poison", 15, me);//提高15%的抗毒

        set_temp("yijin", skill, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill :), n);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int skill)
{
        skill=query_temp("yijin", me);
        
        if( query_temp("yijin", me) )
        {
                addn_temp("apply/attack", -(skill/3), me);
                addn_temp("apply/defense", -(skill/3), me);
                addn_temp("apply/dodge", -(skill/3), me);
                addn_temp("apply/parry", -(skill/3), me);
                addn_temp("apply/armor", -(skill/3), me);
                addn_temp("apply/damage", -(skill/2), me);
                addn_temp("apply/dispel_poison", -(skill/3), me);
                addn_temp("apply/reduce_poison", -15, me);
                delete_temp("yijin", me);
                tell_object(me, "你的["+HIR+"易經轉脈"+NOR+"]運行完畢，將內力收回丹田。\n");
        }
}


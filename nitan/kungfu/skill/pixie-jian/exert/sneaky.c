// This program is a part of NITAN MudLIB
// sneaky.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        
        if( userp(me) && !query("reborn/times", me) )
                return notify_fail("你所使用的內功中沒有這種功能。\n");
                
        if (target != me)
                return notify_fail("辟邪劍法只能對自己使用。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠！\n");

        if (me->query_skill("pixie-jian", 1) < 120)
                return notify_fail("你的辟邪劍法修行不夠，難以運功。\n");

        if( query_temp("apply/shade_vision", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);
        
        message_combatd( HIW "$N" HIW "微一凝神，運起功力，整個人如同被煙霧籠罩一般，漂忽不定，鬼魅至極。\n" NOR, me);

        set_temp("apply/shade_vision", 1, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int level)
{
        if( query_temp("apply/shade_vision", me) )
        {
                delete_temp("apply/shade_vision", me);
                message_vision(HIW "$N" HIW "運功完畢，全身忽的一頓，現出整個身形。\n" NOR, me);
        }
}

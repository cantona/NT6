// buddhism-force (protect)
// by Lonely

#include <ansi.h>

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        if( target != me ) 
                return notify_fail("金剛不壞神功護體真氣只能對自己使用。\n");
    
        if( query("neili", me)<1000 )
                return notify_fail("你的內力不夠。\n");
        if( query_temp("protect", me) )
                return notify_fail("你已經在運功中了。\n");
    
        skill = me->query_skill("buddhism-force", 1);
        if (skill<90) return notify_fail("你的金剛不壞神功還不夠嫻熟。\n");
        me->receive_damage("qi", 0);
        
        message_combatd( HIW "$N微一凝神，運起金剛不壞護體神功，全身衣衫一震。\n" NOR, me);
        addn_temp("apply/armor_vs_force", skill, me);
        set_temp("protect", 1, me);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill/2);
        if( me->is_fighting() ) me->start_busy(1);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (! me)    return;
        addn_temp("apply/armor_vs_force", -amount, me);
        delete_temp("protect", me);
        tell_object(me, BOLD"你的金剛不壞護體神功運行完畢，將內力收回丹田。\n"NOR);
}
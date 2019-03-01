#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill;
        object weapon;
        
        if( query("neili", me)<600 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("badao", 1) < 500)
                return notify_fail("你的霸刀修為不夠。\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("你還沒有激發霸刀呢。\n");
                
        if( query_temp("badao-dasha", me) )
                return notify_fail("你已經施展起刀煞了。\n");
                
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對！\n");
                
        skill = me->query_skill("badao", 1);
        addn("neili", -500, me);

        message_combatd(HIY "$N揮動起手中" + weapon->name() + HIY "，一股強勁的氣流自全身湧向" + weapon->name() + 
                        HIY "，頓時，刀氣四溢，殺氣騰騰。\n" NOR, me);

        addn_temp("apply/damage", skill/2, me);
        set_temp("badao-dasha", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("badao-dasha", me) )
        {
                addn_temp("apply/damage", -(amount/2), me);
                delete_temp("badao-dasha", me);
                tell_object(me, "你的霸刀運行完畢，將內力收回丹田。\n");
        }
}
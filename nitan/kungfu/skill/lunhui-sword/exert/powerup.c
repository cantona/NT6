#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用六道輪迴劍來提升自己的戰鬥力。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        message_combatd(HIG "\n$N" HIG "長歎一聲，手挽寶劍，談笑風聲間，六道真氣自體內而出，湧向天際，化作一朵金蘭，消失了。\n" NOR, me);

        // 打通BREAKUP後的效果增加20%
        if( query("breakup", me))skill=skill+skill*2/10;

        addn_temp("apply/attack", skill, me);
        addn_temp("apply/damage", skill, me);

        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill / 2);
      
        return 1;
}

void remove_effect(object me, int amount)
{
        if (! objectp(me))return;
                                
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/damage", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, HIY "你的六道輪迴劍「劍氣通天」運行完畢，將內力收回丹田。\n" NOR);
        }


}
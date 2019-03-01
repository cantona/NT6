// powerup.c
// Last Modified by ahda on Aug.30 2001

#include <ansi.h>
inherit F_CLEAN_UP;
void remove_effect(object me, int amount);
int exert(object me, object target)
{
        int skill;
  if ( userp(me) && !wizardp(me) && 
  !query("perform/powerup", me) && 
  !query("can_perform/huiyan-xinfa/powerup", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("你所使用的內功中沒有這種功能。");

        if( target != me )
                return notify_fail("你只能用回雁心法提升自己的戰鬥力。\n");
        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

//        me->addn("bellicosity", 100 + skill/2 );
        addn("neili", -100, me);
        me->receive_damage("qi",0);

        message_combatd(RED"$N大吼一聲，運起回雁心法，臉色由紅轉白，緊接著，又由白轉紅！一時間，體內真氣遊走全身，似要迸發。\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/dodge", skill/3, me);
        set_temp("powerup", 1, me);
        me->start_call_out((:call_other,__FILE__,"remove_effect",me,skill/3:),skill);
        if( me->is_fighting() ) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/dodge", -amount, me);
        delete_temp("powerup", me);
        tell_object(me, "你的回雁心法運行完畢，將內力收回丹田。\n");
}

int help(object me)
{
        write(WHT"\n回雁心法之加力："NOR"\n");
        write(@HELP

        使用功效：
                提升自己的攻擊防御能力

        出手要求：
                內力100
HELP
        );
        return 1;
}

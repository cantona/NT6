// powerup.c 化蛇大法
// Last Modified by winder on Mar. 10 2000
//modified by sega 12/28/1999
//改了增加功力與降低不等和不耗內力的bug

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

/*
  if ( userp(me) && !wizardp(me) && 
  !query("perform/powerup", me) && 
  !query("can_perform/wudu-shengong/powerup", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("你所使用的內功中沒有這種功能。");
*/

        if( target != me )
                return notify_fail("你只能用五毒神功提升自己的戰鬥力。\n");
        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        message_combatd(BLU"$N運起五毒神功，頭頂黑氣蒸騰，全身肌膚墳起黑色的鱗甲，雙目兇光四射！\n" NOR, me);

        addn_temp("apply/armor", skill, me);
        addn_temp("apply/hand", skill/3, me);
        addn_temp("apply/attack", skill/3, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill:), skill);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/hand", -amount/3, me);
                addn_temp("apply/attack", -amount/3, me);
                addn_temp("apply/armor", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的五毒神功運行完畢，身體逐漸恢復正常。\n");
        }
}
int help(object me)
{
        write(WHT"\n五毒神功之化蛇大法："NOR"\n");
        write(@HELP

        使用功效：
                提升自己的攻擊防禦能力

        出手要求：
                內力100
HELP
        );
        return 1;
}

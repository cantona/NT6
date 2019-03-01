// Written by Lonely@nitan.org
// 所向無滯 轉世技能
// wuzhi.c

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
        int skill;

        /*
        if( query("family/family_name", me) != "古墓派" )
                return notify_fail("你不是古墓弟子，無法使用所向無滯。\n");
        */

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用所向無滯！\n");

        if( (skill = me->query_skill("yunv-xinfa", 1)) < 1000 )
                return notify_fail("你的玉女心法還不夠精熟，無法使用所向無滯！\n");

        if( query_temp("wuzhi", me) )
                return notify_fail("你已經在運起所向無滯了。\n");

        if( query("jingli", me)<2000 )
                return notify_fail("你的真氣不夠。\n");

        if( query("neili", me)<5000 )
                return notify_fail("你的內力不夠。\n");

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        skill += me->query_skill("martial-cognize", 1);
        skill /= 100;

        message_combatd(HIY "只見$N" HIY "心靜如水，內息再無停滯，心中武學如流水般揮洒開來。\n" NOR, me);

        addn_temp("apply/ap_power", skill, me);
        addn_temp("apply/add_weak", skill, me);
        addn_temp("apply/add_busy", skill/6, me);
        addn_temp("apply/double_damage", skill, me);
        set_temp("wuzhi", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill*50);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int skill)
{
        if( query_temp("wuzhi", me)){
                addn_temp("apply/ap_power", -skill, me);
                addn_temp("apply/add_weak", -skill, me);
                addn_temp("apply/add_busy", -skill/6, me);
                addn_temp("apply/double_damage", -skill, me);
                delete_temp("wuzhi", me);
                tell_object(me, "你的玉女心法運行完畢，將內力收回丹田。\n");
        }
}

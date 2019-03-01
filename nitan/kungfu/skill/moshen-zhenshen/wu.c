#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return "無法無天"; }

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill;

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("moshen-zhenshen", 1) < 100)
                return notify_fail("你的魔神真身修為不夠。\n");

        if( query_temp("moshenzhenshen", me) )
                return notify_fail("你已經運起魔神真身絕招無法無天了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "默運魔功，內勁在身體內快速的運轉，霎時在體外形成一層罡氣！\n" NOR, me);

        addn_temp("apply/armor", skill/2, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("moshenzhenshen", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("moshenzhenshen", me) )
        {
                addn_temp("apply/armor", -(amount/2), me);
                addn_temp("apply/defense", -(amount/3), me);
                delete_temp("moshenzhenshen", me);
                tell_object(me, "你的魔神真身絕招無法無天運行完畢，將內力收回丹田。\n");
        }
}
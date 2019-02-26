// ironskin.c 銅皮鐵骨
// Created by Vin 1/9/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "銅皮鐵骨" NOR; }

int perform(object me, string skill)
{
        int count;

        if (me->query("qi") < 40)
                return notify_fail("你的體力不支，無法迅猛提升自己的防禦力。\n");

        message_vision(YEL "$N" YEL "微一凝神，氣沉丹田，雙目陡然"
                       "精光四射。\n" NOR, me);
        count = me->query_str() * 3 / 2;

        if (me->query_temp("special_skill/ironskin", 1))
                return notify_fail("你已經盡力提升自己的防禦力了。\n");

        me->receive_damage("qi", 20 + random(20));
        me->set_temp("special_skill/ironskin", 1);
        me->add_temp("apply/armor", count);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              count :), 60 + random(30));

        return 1;
}

void remove_effect(object me, int count)
{
        me->delete_temp("special_skill/ironskin", 1);
        me->add_temp("apply/armor", -count);
        tell_object(me, "你施展完銅皮鐵骨，放鬆了全身的勁道。\n");
}

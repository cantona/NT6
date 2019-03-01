// power.c 天神降世
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "天神降世" NOR; }

int perform(object me, string skill)
{
        int count;

        if( query("qi", me)<80 )
                return notify_fail("你的體力不支，無法迅猛提升自己的戰鬥力。\n");

        message_vision(HIY "$N" HIY "雙臂一伸一縮，膝部微彎，"
                       "作勢欲撲。\n" NOR, me);
        count = me->query_str();

        if( query_temp("special_skill/power", me) )
                return notify_fail("你已經盡力提升自己的戰鬥力了。\n");

        me->receive_damage("qi", 40 + random(40));
        set_temp("special_skill/power", 1, me);
        addn_temp("apply/attack", count, me);
           me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              count :), 60 + random(30));

        return 1;
}

void remove_effect(object me, int count)
{
        delete_temp("special_skill/power", me);
        addn_temp("apply/attack", -count, me);
        tell_object(me, "你施展完天神降世，鬆了一口氣。\n");
}

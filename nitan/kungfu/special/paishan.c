
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "排山倒海" NOR; }

int perform(object me, string skill, string arg)
{
        int add_dam;     

        if (me->query_temp("special/paishan"))
                return notify_fail("排山倒海技能已經在施展中了。\n");

        if (me->is_busy())return notify_fail("等你忙完再説吧！\n");

        message_vision(HIW "$N" HIW "雙拳緊握，殺氣懾人，衣裳無風自起，一股氣流猶如排山倒海般地湧出 ……\n" NOR, me);
 
        me->start_busy(1);

        if (me->query_temp("weapon"))
                add_dam = 1 + me->query_temp("apply/damage") / 20;
        else
                add_dam = 1 + (me->query_temp("apply/damage") + me->query_temp("apply/unarmed_damage")) / 20;

        me->set_temp("special/paishan", 1);
        me->add_temp("apply/damage", add_dam);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, add_dam :), 180);
        return 1;
}

void remove_effect(object me, int add_dam)
{
        if ((int)me->query_temp("special/paishan"))
        {
                me->add_temp("apply/damage", -1 * add_dam);
                me->delete_temp("special/paishan");
                tell_object(me, "你排山倒海特技施展完畢。\n");
        }
}


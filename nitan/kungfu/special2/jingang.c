
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "金剛護體" NOR; }

int perform(object me, string skill, string arg)
{
        int add_dam;      	

        if (me->query_temp("special/jingang"))
                return notify_fail("金剛護體技能已經在施展中了。\n");

        if (me->is_busy())return notify_fail("等你忙完再說吧！\n");

        message_vision(HIY "$N" HIY "雙拳揮出，大喝一聲，猛然間全身金光籠罩，皮膚猶如渡上一層金子一般 ……\n" NOR, me);
 
        me->start_busy(1);

        me->set_temp("special/jingang", 1);
	me->add_temp("apply/armor", 500);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, 500 :), 180);
        return 1;
}

void remove_effect(object me, int add_dam)
{
        if ((int)me->query_temp("special/jingang"))
        {
		me->add_temp("apply/armor", -500);
	        me->delete_temp("special/jingang");
	        tell_object(me, "你金剛護體特技施展完畢。\n");
        }
}


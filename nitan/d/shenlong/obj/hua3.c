// hua3.c

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIR "斷腸花" NOR, ({"duanchang hua", "duanchang"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
        	set("unit", "朵");
		set("long", "這是一朵斷腸花，通體通紅，鮮嫩欲滴，美麗異常。\n");
        	set("no_get", "你根本不敢近前。\n");
		set("only_do_effect", 1);
	}
        setup();
}

int do_effect(object me)
{
        message_vision("$N把" + name() + "扔進嘴裡，幾下就吞了下去。\n", me);
        set_temp("die_reason", "服下斷腸花，中毒身亡了", me);
	me->die();
	destruct(this_object());
	return 1;
}
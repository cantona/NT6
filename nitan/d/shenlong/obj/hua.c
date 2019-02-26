//hua.c 百香花

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIG"百香花"NOR, ({"baixiang hua", "baixiang"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "朵");
		set("long", "這是一朵鮮豔的花，花香濃郁異常。\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
        message_vision("$N把" + name() + "扔進嘴裏，幾下就吞了下去。\n", me);
	destruct(this_object());
	return 1;
}

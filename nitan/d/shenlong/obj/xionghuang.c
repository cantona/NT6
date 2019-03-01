#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("雄黃", ({"xionghuang" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "包");
		set("long", "這是一包雄黃，據說可驅百毒。\n");
		set("value", 1000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	write("想死啊？雄黃不能吃。\n");
        return 1;
}
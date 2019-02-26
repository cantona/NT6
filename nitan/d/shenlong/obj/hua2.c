// hua2.c 無名花
inherit ITEM;

void create()
{
	set_name("無名花", ({ "wuming hua", "wuming", "hua" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "朵");
		set("long", "這是一朵無名小花，花蕊雖小，卻十分美麗。\n");
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

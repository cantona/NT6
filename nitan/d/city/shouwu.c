// shouwu.c 何首烏

inherit ITEM;

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name("何首烏", ({"heshou wu", "wu"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "棵");
		set("long", "這是一棵初具人形的何首烏。\n");
		set("value", 10000);
	}
	setup();
}

int do_eat(string arg)
{
	if (!id(arg))
	return notify_fail("你要吃什麼？\n");

	this_player()->receive_curing("qi", 100);
	message_vision("$N吃下一棵何首烏，頓時間覺得全身充滿了活力 !\n", this_player());
	destruct(this_object());
	return 1;
}

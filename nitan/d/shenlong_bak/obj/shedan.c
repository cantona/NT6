inherit ITEM;


void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("腹蛇膽", ({"fushe dan","dan"}));
        set("unit", "枚");
        set("long", "這是一枚火紅的腹蛇膽。\n");
        set("value", 500);
        setup();
}

int do_eat(string arg)
{
if (!id(arg))  return notify_fail("你要吃什麼？\n");
this_player()->unconcious();
destruct(this_object());
return 1;
}
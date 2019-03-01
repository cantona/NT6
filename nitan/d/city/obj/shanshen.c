// shanshen.c 老山參

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("老山參", ({"laoshan shen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", "這是一株沾滿山泥的長白老山參。\n");
                set("value", 10000);
                set_weight(100);
        }
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
        return notify_fail("你要吃什麼？\n");

        addn("eff_qi", 20, this_player());

        message_vision("$N吃下一株老山參，只覺得渾身一股熱氣兜底冒了上來 !\n", this_player());
        destruct(this_object());
        return 1;
}

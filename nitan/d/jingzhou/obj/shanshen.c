// shanshen.c 老山叁

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("老山叁", ({"laoshan shen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", "這是一株沾滿山泥的長白老山叁。\n");
                set("value", 10000);
        }
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
        return notify_fail("你要吃什麼？\n");

        addn("eff_qi", 200, this_player());
//        this_player()->addn("max_qi", 100);

        message_vision("$N吃下一株老山叁，只覺得渾身一股熱氣兜底冒了上來 !\n", this_player());
        destruct(this_object());
        return 1;
}


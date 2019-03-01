// yangxin.c 養心丸

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("養心丸", ({"yangxin wan", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆暗紅發亮的養心丸。\n");
                set("value", 10000);
        }
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
        return notify_fail("你要吃什麼？\n");

        addn("qi", 200, this_player());
        message_vision("$N吃下一顆養心丸，只覺得體內真力源源滋生，不絕如縷。\n", this_player());
        destruct(this_object());
        return 1;
}

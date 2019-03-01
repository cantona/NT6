// xiongdan1.c

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("熊膽幹", ({"xiongdan gan", "xiongdan", "gan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "副");
                set("long", "這是一副熊膽幹。\n");
                set("value", 1000);
        }
        setup();
}

int do_eat(string arg)
{
        object me = this_player();
        if (!id(arg))
        return notify_fail("你要吃什麼？\n");
        if (me->is_fighting()) return notify_fail("戰鬥中不能吃東西！\n");
        if (me->is_busy()) return notify_fail("你正忙著呢！\n");

        set("eff_qi",query("max_qi",  this_player()), this_player());
        message_vision("$N吃下一副熊膽幹，覺得精神好多了。\n", this_player());
        destruct(this_object());
        return 1;
}


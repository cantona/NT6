// shedan.c

inherit ITEM;

void create()
{
        set_name("腹蛇膽", ({"fushe dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", "這是一枚火紅的腹蛇膽。\n");
                set("value", 500);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N一口就把$n吞了下去。\n",
                       me, this_object());
        destruct(this_object());
        me->unconcious();
        return 1;
}

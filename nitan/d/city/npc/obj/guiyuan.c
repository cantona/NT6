// guiyuan.c 歸元丹

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("歸元丹", ({"guiyuan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆瑩白溜圓的歸元丹。\n");
                set("value", 10000);
        }
        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        addn("neili", 200, this_player());
        message_vision("$N吃下一顆歸元丹，只覺得四肢百骸真氣充盈無比！\n", this_player());
        destruct(this_object());
        return 1;
}


// niuhuang.c 牛黃

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIY"牛黃"NOR, ({"niuhuang"}));
        set_weight(500);
        set("vegetable", 8);
        set("value", 1000);
        set("nostrum", 16);
        set("unit", "塊");
        set("long", "這是一塊牛膽裏取出來的牛黃，看來可以入藥。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        if (!id(arg)) return notify_fail("你要吃什麼？\n");

        if (!present(this_object(), this_player()))
                return notify_fail("你要吃什麼？\n");

        if(arg=="niuhuang")
        {
                write("牛黃不能這麼吃。\n");
        }
        return 1;
}
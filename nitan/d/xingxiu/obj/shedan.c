//  poison: shedan.c
// Jay 3/18/96

// more work needed to use this object to make poison

inherit ITEM;


void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("毒蛇膽", ({"shedan", "dan"}));
        set("unit", "只");
        set("long", "這是一隻綠瑩瑩的毒蛇膽，是製備毒藥的原料。\n");
        set("value", 800);
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什麼？\n");
        return notify_fail("你找死啊。\n");
}
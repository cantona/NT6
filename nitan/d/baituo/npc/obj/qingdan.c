// more work needed to use this object to make poison
inherit ITEM;


void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("青蛇膽", ({"qing", "qing dan"}));
        set("unit", "只");
        set("long", "這是一隻綠瑩瑩的青蛇膽，是製備『蛇膽膏』的原料。\n");
        set("value", 100);
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什麼？\n");
        return notify_fail("你找死啊。\n");
}
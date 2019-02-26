//  poison: shachongke.c
// Jay 3/17/96

// more work needed to use this object to make poison

inherit ITEM;

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("沙蟲殼", ({"shachong ke", "ke"}));
        set("unit", "只");
        set("long", "這是一隻沙蟲的幹殼，是製備毒藥的原料。\n");
        set("value", 300);
//        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什麼？\n");
        return notify_fail("你找死啊。\n");
}

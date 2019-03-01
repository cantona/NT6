// Obj: /d/guiyun/obj/shedan.c
// Last Modified by winder on Jul. 9 2001

inherit ITEM;

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("毒蛇膽", ({"shedan", "dan"}));
        set("unit", "只");
        set("long", "這是一只綠瑩瑩的毒蛇膽，是制備毒藥的原料。\n");
        set("value", 800);
        setup();
}

int do_eat(string arg)
{
        if (!id(arg)) return notify_fail("你要吃什麼？\n");
        return notify_fail("你找死啊！\n");
}

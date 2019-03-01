// yaofen.c 藥粉

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("藥粉", ({ "yao fen" , "yao", "fen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包專治內傷的藥粉。\n");
                set("value", 1000);
        }
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什麼藥？\n");
        return notify_fail("只有專練可對付‘化骨綿掌’的武功的人才需要服這種藥。\n");

}
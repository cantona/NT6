inherit ITEM;
#include <ansi.h>
void create()
{
        set_name(RED"膏藥"NOR, ({ "gaoyao" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "看上去很奇怪的一副膏藥，半邊紅半邊黑。\n");
                set("unit", "副");
                set("value", 500);
        }
    setup();
}

void init()
{
        add_action("do_use","use");
        add_action("do_use","yong");
}


int do_use(string arg)
{
        if (!id(arg))
                return notify_fail("\n你要用什麼藥？\n");
        return notify_fail("\n你撕開藥封來，只見一張紙上有個明目，曰:\n"
        +"“去清復明膏藥”。此外什麼也沒有。\n");
}
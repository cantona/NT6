#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + MAG "紫蛟須" NOR, ({ "dragon beard", "beard" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "一根南海惡蛟的龍鬚，呈紫黑色。\n" NOR);
                set("unit", "根");
                set("value", 200000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "□須" NOR, ({ "dragon beard", "beard" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一根□王的胡須。\n" NOR);
                set("unit", "根");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + HIW "八仙石" NOR, ({"baxian shi", "baxian", "shi"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "這是一塊晶瑩剔透的玉石，光華亮澤，觸手冰涼。\n" NOR);
                set("unit", "塊");
                set("value", 10000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + HIW "八仙石" NOR);
                set("can_make", ({ "指套" }));
                set("power_point", 70);
        }
}

int query_autoload()
{
        return 1;
}

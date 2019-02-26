#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + RED "碧血石" NOR, ({"bixue shi", "bixue", "shi"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "堅硬似鐵的碧血石，石面隱隱印着血色花紋。\n" NOR);
                set("unit", "塊");
                set("value", 8000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + RED "碧血石" NOR);
                set("can_make", ({ "鐵掌" }));
                set("power_point", 50);
        }
}

int query_autoload()
{
        return 1;
}

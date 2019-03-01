#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + CYN "邯鄲石" NOR, ({"handan shi", "handan", "shi"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN "這是一塊通體烏黑的石頭，觸手處清涼光滑。\n" NOR);
                set("unit", "塊");
                set("value", 8000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + CYN "邯鄲石" NOR);
                set("can_make", ({ "指套" }));
                set("power_point", 50);
        }
}

int query_autoload()
{
        return 1;
}

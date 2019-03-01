#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(CYN "玄武甲殼" NOR, ({ "xuanwu jiake", "jiake"}));
        set_weight(25000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN "一塊神獸玄武的甲殼，相當的堅韌。\n" NOR);
                set("unit", "塊");
                set("value", 120000);
              set("item_origin", 1);
              set("material_attrib", "silk");
              set("material_name", CYN "玄武甲殼" NOR);
              set("can_make", ({ "甲" }));
              set("power_point", 100);
        }
}

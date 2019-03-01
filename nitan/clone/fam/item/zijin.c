#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + MAG "紫金礦" NOR, ({"zijin kuang", "zijin", "kuang"}));
        set_weight(1800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "這是一塊極為罕見的紫金礦石，堅如玄鐵，價值連城。\n" NOR);
                set("unit", "塊");
                set("value", 8000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + MAG "紫金礦" NOR);
                set("can_make", ({ "護甲", "頭盔", "護腕" }));
                set("power_point", 50);
        }
}

int query_autoload()
{
        return 1;
}

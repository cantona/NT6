#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + HIR "雷火寒晶" NOR, ({"leihuo hanjing", "leihuo", "hanjing", "jing"}));
        set_weight(4500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "集天地之靈氣而聚成的晶體，可鑄一切神兵利器。\n" NOR);
                set("unit", "塊");
                set("value", 10000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + HIR "雷火寒晶" NOR);
                set("can_make", ({ "劍", "刀", "錘", "短兵", "簫", "棍", "杖" }));
                set("power_point", 70);
        }
}

int query_autoload()
{
        return 1;
}

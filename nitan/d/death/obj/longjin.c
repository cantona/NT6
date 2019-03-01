#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "龍筋" NOR, ({ "long jin", "jin"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一根從神獸青龍身上取出的筋，相當的堅韌。晶瑩剔透，隱然泛出白光。\n" NOR);
                set("unit", "根");
                set("value", 200000);
              set("item_origin", 1);
              set("material_attrib", "silk");
              set("material_name", HIW "龍筋" NOR);
              set("can_make", ({ "鞭" }));
              set("power_point", 120);
        }
}

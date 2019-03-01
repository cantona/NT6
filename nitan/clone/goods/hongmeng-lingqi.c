#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "鴻蒙靈氣" NOR, ({ "hongmeng lingqi", "hongmen lingqi", "lingqi" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "混沌初開產生的鴻蒙靈氣，據說擁有著奇幻的力量，是用來提升套裝等級的必備材料。\n" NOR); 
                set("unit", "塊");
                set("value", 500000);
                set("no_sell", 1);
                set("auto_load", 1);
        }
        setup();
}

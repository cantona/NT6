// fu

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIR"同心結" NOR, ({ "tongxin jie", "jie" }));
               set("long", "一個鮮紅色的中國結，象徵着有情人永結同心。\n");
        set("weight", 100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("value", 5000);
                set("material", "絲");
                set("armor_prop/armor", 2);
                }
        setup();
}        
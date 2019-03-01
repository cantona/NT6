#include <ansi.h>
#include <armor.h>
inherit ARMOR;
void create()
{
        set_name( WHT "盤古鎧" NOR,  ({ "pangu kai", "kai", "armor" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "見");
                set("long", "一見黑黝黝的鐵甲，上面雕有盤古的頭像。\n");
                set("value", 100000);
                set("material", "cloth");
                set("armor_prop/armor", 200);
        }
        setup();
}


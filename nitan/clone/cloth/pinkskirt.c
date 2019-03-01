// pinkshirt.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(HIR"五色梅淺紅裙"NOR, ({"qianhong qun","pink skirt","skirt"}));
        set_weight(2700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一襲長裙，上面繡了幾道水波。\n");
                set("unit", "襲");
                set("value", 3000);
                set("material", "cloth");
                set("armor_prop/armor", 5);
                set("armor_prop/dodge", 10);
        }
        setup();
}

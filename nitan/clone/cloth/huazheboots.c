// huazheboots.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit BOOTS;

void create()
{
        set_name("花褶靴", ({ "huazhe xue", "flower boots", "boots" }) );
        set_weight(1700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long",
"一雙皮靴，上等牛皮製成。做功考究，裁剪精緻，看上去氣派不凡。\n");
                set("value", 800);
                set("material", "cloth");
                set("armor_prop/armor", 2);
                set("armor_prop/per", 1);
        }
        setup();
}

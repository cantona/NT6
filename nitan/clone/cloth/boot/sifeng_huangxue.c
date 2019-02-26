// sifeng_huangxue.c 四縫幹黃靴

#include <armor.h>
inherit BOOTS;

void create()
{
        set_name("四縫幹黃靴", ({"sifeng huangxue", "xie", "shoes"}));
        set_weight(1000);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一雙精心縫製的皮靴，輕便舒適。\n");
                set("unit", "雙");
                set("value", 500);
                set("material", "pi");
                set("armor_prop/armor", 4);
                set("armor_prop/dodge", 10);
        }
        setup();
}



// shoutao.c  手套

#include <armor.h>

inherit HANDS;

void create()
{
        set_name( "鹿皮手套", ({ "lupi shoutao", "shoutao" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long", "這是一雙鹿皮手套，上面有硬物刻勒的痕跡，可以避毒。\n");
                set("value", 10000);
                set("material", "leather");
                set("armor_prop/armor", 10);
        }
        setup();
}
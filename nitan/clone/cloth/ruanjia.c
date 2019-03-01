// ruanwei jia
#include <armor.h>
#include <ansi.h>
inherit ARMOR;
void create()
{
    set_name(WHT "軟甲" NOR,({ "ruan jia","jia", }) );
    set_weight(1000);
    if( clonep() )
        set_default_object(__FILE__);
    else
    {
        set("unit", "件");
            set("long", "一件輕飄飄的、生滿尖銳倒刺的護甲。\n");
            set("material", "copper");
            set("value",2000);
            set("armor_prop/armor", 75);
            set("armor_prop/dodge", -5);
    }
    setup();
}


// ruanwei jia

#include <armor.h>

inherit ARMOR;

void create()
{
    set_name( "軟□甲",({ "ruanwei jia","jia", }) );
    set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "件");
                set("long", "一件輕飄飄的、生滿尖銳倒刺的護甲。\n");
                set("material", "copper");
                set("value",20000);
                set("no_drop", "這樣東西不能離開你。\n");
                set("armor_prop/armor", 100);
                set("armor_prop/dodge", -5);
        }
        setup();
}
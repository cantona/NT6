#include <armor.h>
                
inherit CLOTH;
 
void create()
{
        set_name("夜行衣", ({ "black cloth", "cloth" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一件夜行人用來掩藏行蹤的黑色緊身衣。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/dodge", 1);
                set("armor_prop/per", -1);
        }
        setup();
}

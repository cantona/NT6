// weapon: 法鈴

#include <weapon.h>
 
inherit HAMMER;
 
void create()
{
        set_name("法鈴", ({ "fa ling","fa","ling" }) );           
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "副");                                
                set("value", 10);
                set("material", "iron");                             
                set("long", "這是一副法鈴，搖起來叮叮鐺鐺亂響。\n");
                set("wield_msg", "$N從腰間抽出一副$n，握在手裡。\n");
                set("unequip_msg", "$N將$n收起來，掛回腰間。\n");
        }
        init_hammer(1);
        setup();
}

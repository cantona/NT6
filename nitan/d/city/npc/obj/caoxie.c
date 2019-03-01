// caoxie.c 草鞋
 
#include <armor.h>
 
inherit BOOTS;
 
void create()
{
        set_name("草鞋", ({ "sandals", "cao xie", "xie" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "wood");
                set("unit", "雙");
                set("long", "這是一雙草編的草鞋，用以保護足部。\n");
                set("value", 100);
                set("armor_prop/dodge", 2);
        }
        setup();
}
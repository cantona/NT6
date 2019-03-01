// toukui.c 頭盔
 
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIM "戰神頭盔" NOR, ({ "zhanshen toukui3", "zhanshen", "toukui3" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "頂");
                set("long", HIM "這是一頂鐵制的頭盔，用以保護頭部。\n" NOR);
                set("value", 1500000);
                set("armor_prop/armor", 300);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
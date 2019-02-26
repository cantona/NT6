// cloth.c example cloth

#include <ansi.h>

inherit EQUIP;

void create()
{
        set_name( HIC "淺藍色馬褂" NOR, ({ "lan magua", "cloth" }) );
        set_weight(700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("value", 100);
                set("material", "cloth");
                set("armor_type", "cloth");
                set("armor_prop/per", 1);
                set("armor_prop/armor", 2);
                set("wear_msg","$N穿上一件$n。\n");
                set("remove_msg","$將$n脱了下來。\n");
        }
}

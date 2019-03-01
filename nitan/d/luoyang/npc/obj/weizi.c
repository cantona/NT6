// weizi.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(MAG"魏紫"NOR, ({"weizi"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"一朵含苞待放的"MAG"魏紫。\n"NOR);
                set("value", 6000);
                set("flower", 1);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}
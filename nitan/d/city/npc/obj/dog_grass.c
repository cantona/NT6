// dog_grass.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIG"狗尾巴草"NOR, ({"dog grass", "grass"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "束");
                set("long", 
"一束碧綠如玉的"HIG"狗尾巴康草乃馨。\n"NOR);
                set("value", 5000);
                set("flower", 1);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一束$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}
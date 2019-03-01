// yujinxiang.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(YEL"鬱金香"NOR, ({"yujinxiang"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"一朵富麗華貴的"YEL"鬱金香。\n"NOR);
                set("value", 1000);
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
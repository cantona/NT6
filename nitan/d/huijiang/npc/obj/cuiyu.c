// cuiyu.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIG"翠羽"NOR, ({"cui yu", "yu"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", 
"一支翠綠的羽毛。\n");
                set("value", 800);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 10);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}
// hua2.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIR"莎欏花"NOR, ({"flower", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", "這是一朵美麗的小野花，香氣清新。\n");
                set("value", 0);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}
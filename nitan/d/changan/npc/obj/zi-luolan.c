//ziluolan.c

#include <armor.h>
#include <ansi.h>

inherit HEAD;

void create()
{
        set_name(HIM "紫羅蘭" NOR, ({ "zi luolan", "luolan" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long", "高貴典雅的紫羅蘭，聞起來還有一股淡淡的香味兒。\n");
                set("unit", "朵");
                set("value", 6);
                set("material", "plant");
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unwield_msg", "$N輕輕地把$n從頭上除了下來。\n");
                set("female_only", 1);

        }

        setup();
}
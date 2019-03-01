//lan-tiane

#include <armor.h>
#include <ansi.h>

inherit HEAD;

void create()
{
        set_name(HIB "藍天鵝" NOR, ({ "lan tiane", "tiane" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long", "莊重樸實的藍天鵝。\n");
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
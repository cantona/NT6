//yupei.c

#include <armor.h>

inherit NECK;

void create()
{
        set_name("龍鳳玉佩", ({"yu pei"}));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("unit", "個");
                set("value", 2000);
                set("long", "一枚玉佩，上面雕刻着龍鳳圖案．\n");
                set("no_sell", 1);
                set("material", "steel");
                set("armor_prop/dodge", 10);
                set("armor_prop/armor", 2);
        }

        setup();
}
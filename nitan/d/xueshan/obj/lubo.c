inherit F_LIQUID;
#include <weapon.h>
#include <ansi.h>

inherit HAMMER;
void create()
{
        set_name( BLU "顱砵" NOR, ({"lubo"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用顱骨制成的砵。\n");
                set("unit", "個");
                set("value", 100);
                set("max_liquid", 10);
                set("regidity", 1000);
                set("wield_msg", "$N從腰間抽出一個$n，端在手裡。\n");
                set("unequip_msg", "$N將$n收起來，掛回腰間。\n");
        }

        // because a container can contain different liquid
        // we set it to contain water at the beginning
        set("liquid", ([
                "type": "water",
                "name": "清水",
                "remaining": 10,
                "drunk_supply": 10,
        ]));
        init_hammer(30);
}


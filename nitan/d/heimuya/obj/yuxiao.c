// yuxiao.c

#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("玉簫", ({"yuxiao"}));
        set_weight(500);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", "一支白玉做成的長簫，看上去晶瑩溫潤。武林中人經常以簫代劍。\n");
                set("value", 10000);
                set("material", "bamboo");
                set("wield_msg", "$N大袖一揮，手中已多了一支晶瑩溫潤的玉簫。\n");
                set("unwield_msg", "$N手中玉簫一轉，眨眼間玉簫已然不見影蹤。\n");
        }
        init_sword(50);
        setup();
}        
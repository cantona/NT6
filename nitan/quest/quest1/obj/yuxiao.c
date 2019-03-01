#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
    set_name("玉蕭", ({"yuxiao"}));
    set_weight(500);

        if (clonep())
                set_default_object(__FILE__);
        else {
        set("unit", "支");
        set("long", "一支白玉做成的長蕭，看上去晶瑩溫潤。武林中人經常以蕭代劍。\n");
                set("value", 10000);
                set("material", "bamboo");
        set("wield_msg", "$N大袖一揮，手中已多了一支晶瑩溫潤的玉蕭。\n");
        set("unwield_msg", "$N手中玉蕭一轉，眨眼間玉蕭已然不見影蹤。\n");
        }
    init_sword(100,2);
        setup();
}       

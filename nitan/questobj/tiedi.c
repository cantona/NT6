// tiedi.c

#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIB"鐵笛"NOR, ({"tie di"}));
        set_weight(500);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", "一支黑鐵做成的長笛，看上去堅忍異常。\n");
                set("value", 0);
                set("material", "bamboo");
                set("wield_msg","$N大袖一揮，手中已多了一支烏黑油光的鐵笛。\n");
                set("unwield_msg","$N手中鐵笛一轉，眨眼間鐵笛已然不見影蹤。\n");
        }
        setup();
}
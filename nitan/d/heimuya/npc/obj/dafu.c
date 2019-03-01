// dafu.c

#include <ansi.h>
#include <weapon.h>

inherit AXE;

void create()
{
        set_name("大斧", ({"da fu", "axe"}));
        set_weight(5000);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "一柄十分鋒利的大斧。\n");
                set("value", 100);
                set("material", "bamboo");
                set("wield_msg", "$N回手從身後抽出一柄大斧。\n");
                set("unwield_msg", "$N手往後一別，把大斧插在後腰上。\n");
        }
        init_axe(35);
        setup();
}
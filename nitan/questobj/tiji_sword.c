// tiji_sword.c

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(HIB"星"HIM"雨"NOR, ({ "xingyu sword", "lqy", "sword" }));
        set_weight(6000);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N往腰中一帶，抽出了一口$n握在手中。\n");
                set("unwield_msg", "$N手中$n迎風一抖，眨眼間已然不見影蹤。\n");
        }
        setup();
}


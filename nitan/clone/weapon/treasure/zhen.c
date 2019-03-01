// zhen.c 繡花針
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>;
#include <weapon.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name("繡花針", ({"xiuhua zhen", "zhen", "sword"}));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long","一枚精鋼打制的繡花針，看上去雪亮雪亮的。武林中人很少以它為兵器。\n");
                set("value", 10000);
                set("material", "steel");
                set("wield_msg", "$N手腕一抖，手中已多了一枚雪亮的繡花針。\n");
                set("unwield_msg", "$N手腕一轉，眨眼間繡花針已然不見影蹤。\n");
        }
        init_sword(100);
        setup();
}
// sanmending.c 喪門釘

#include <weapon.h>
inherit THROWING;
// inherit COMBINED_ITEM;

void create()
{
        set_name("喪門釘", ({ "sangmen ding", "ding" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一玫喪門釘，似乎喂的是“青陀羅花”的毒汁。\n");
                set("value", 1);
                set("material", "steel");
                set("wield_msg", "$N抓出一把喪門釘扣在手心。\n");
                set("unwield_msg", "$N將手中的喪門釘放回裝暗器的皮囊裡。\n");
                set("base_unit", "枚");
                set("base_weight", 2);
                set("poisoned", "qtlh_poi");
                set("poison_number", 6);
        }
        set_amount(random(5) + 10);
        init_throwing(10);
        setup();
}
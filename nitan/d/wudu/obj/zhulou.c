#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name("竹簍", ({"zhu lou", "zhu", "lou"}));
        set_weight(300);
        set_max_encumbrance(15000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是一個小口大肚的竹簍，常用來存放草藥。\n");
                set("wear_msg", "$N將竹簍背在背上。\n");
                set("remove_msg", "$N將竹簍從背上放了下來。\n");
                set("value", 50);
                set("material", "bamboo");
                set("armor_prop/armor", 3);
        }
        setup();
}

int is_container() { return 1; }
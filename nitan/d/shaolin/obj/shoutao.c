// shoutao.c

#include <ansi.h>
#include <armor.h>

inherit HANDS;

void create()
{
        set_name("皮手套", ({ "pi shoutao", "shoutao" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "雙");
                set("long", "這是一雙皮手套，上面有硬物刻勒的痕跡。\n");
                set("value", 3000);
                set("armor_prop/armor", 1);
                set("armor_prop/hand", 1);
                set("armor_prop/strike", 1);
                set("armor_prop/unarmed_damage", 3);
                set("shaolin",1);
        }
        setup();
}
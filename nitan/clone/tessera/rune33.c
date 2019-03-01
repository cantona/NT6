//rune33.c

// Zod灺肅

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }

void create()
{
        set_name(HIW "睫恅" NOR, ({"rune33", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "睫恅ㄩ怮湮喪睫ㄛ褫眕溫側羞昜﹝\n");
                set("unit", "跺");
                set("enchase/SN", 33);
                set("enchase/type", "all");
                set("enchase/consistence", 100);
                set("enchase/weapon_prop", ([
                        "add_skill" : 30,
                        "add_busy"  : 3,
                        "add_damage" : 6,
                ]));
                set("enchase/armor_prop", ([
                        "add_skill" : 5,
                        "research_effect": 20,   
                        "practice_effect" : 20,   
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

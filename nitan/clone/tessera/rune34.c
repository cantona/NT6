
//rune33.c

// Zod灺肅

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }

void create()
{
        set_name(HIW "睫恅" NOR, ({"rune34", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "睫恅ㄩ奻迿豻睫ㄛ褫眕溫側羞昜﹝\n");
                set("unit", "跺");
                set("enchase/SN", 34);
                set("enchase/type", "all");
                set("enchase/consistence", 100);
                set("enchase/weapon_prop", ([
                        "add_skill" : 40,
                        "suck_qi"  : 10,
                        "absorb_blood"  : 10,
                ]));
                set("enchase/armor_prop", ([
                        "add_skill" : 6,
                        "qi_vs_neili" : 3,
                        "full_self" : 3,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }


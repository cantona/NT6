//rune33.c

// Zod灺肅

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }

void create()
{
        set_name(HIW "睫恅" NOR, ({"rune35", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "睫恅ㄩ迶峚睫ㄛ褫眕溫側羞昜﹝\n");
                set("unit", "跺");
                set("enchase/SN", 35);
                set("enchase/type", "all");
                set("enchase/consistence", 100);
                set("enchase/weapon_prop", ([
                        "add_skill" : 50,
                        "add_freeze" : 10,
                        "add_dizziness" : 10,
                ]));
                set("enchase/armor_prop", ([
                        "add_skill" : 7,
                        "avoid_freeze" : 3,
                        "avoid_dizziness" : 3,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }


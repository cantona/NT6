//rune18.c

// Ko 科

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({"rune18", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：太安皇崖符，可以放入凹槽物品。\n");
                set("unit", "個");
                set("enchase/SN", 18);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "int"   : 15,               
                ]));
                set("enchase/armor_prop", ([
                        "int"   : 10,     
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
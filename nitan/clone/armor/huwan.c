// huwan.c
// Last Modified by winder on May. 29 2001

#include <ansi.h>
#include <armor.h>
inherit WRISTS;

void create()
{
        set_name( "護腕", ({ "hu wan", "huwan" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long", "這是一件皮質的護腕，上面滿布鐵釘，用以保護腕部。\n");
                set("value", 6000);
                set("material", "wrists");
                set("armor_prop/armor", 5);
                set("shaolin",1);
        }
        setup();
}
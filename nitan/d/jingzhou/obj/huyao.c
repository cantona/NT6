// huyao.c

#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name( "護腰", ({ "waist", "hu yao", "huyao" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "條");
                set("long", "這是一條皮質的護腰，用以保護腰部。\n");
                set("value", 1600);
                set("material", "leather");
                set("armor_prop/armor", 5);
        }
        setup();
}
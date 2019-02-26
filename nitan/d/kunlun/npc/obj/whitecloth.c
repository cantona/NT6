// Room: /d/kunlun/npc/obj/whitecloth.c
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(HIW"啞説藽"NOR, ({ "baihu cloth","cloth" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "璃");
                set("value", 5000);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 3);
                set("female_only", 1);
        }
        setup();
}

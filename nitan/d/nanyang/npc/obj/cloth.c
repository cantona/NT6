// Room: /d/nanyang/npc/cloth.c
// Last Modified by winder on Nov. 20 2001

#include <armor.h>
inherit CLOTH;
void create()
{
        set_name("藍緞長衫", ({ "cloth" }) );
        set("long","一件紫藍色的綢面長衫，穿起來很氣派。\n");
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                set("value",1000);
                set("no_get",1);
                set("armor_prop/per",1);
                set("armor_prop/armor", 1);
        }
        setup();
}
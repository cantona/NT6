// Code of ShenZhou
// branch2.c
// Jay 7/4/96
#include <ansi.h>
#include <weapon.h>
inherit CLUB;

void create()
{
    set_name(YEL"大樹枝"NOR, ({"shuzhi", "zhi", "branch"}));
    set_weight(500+random(500)); 
    if( clonep() )
      set_default_object(__FILE__);
    else {
      set("long", "這是一根大樹枝。\n");
        set("unit","根");
        set("wield_msg","$N拔出一根大樹枝握在手中。\n");
        set("material", "wood");
    }
    init_club(random(2));

    setup();
}
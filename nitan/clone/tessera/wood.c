// wood.c 木靈

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG "木靈" NOR, ({ "mu ling", "wood" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIG "這是一片木靈，來自東海扶桑之樹，上古神人所棲，每千年而有木靈生，色青，觸之若無物。\n" NOR);
                set("value", 2000);
                set("unit", "片");
                set("magic/element", "wood");
        }
        setup();
}

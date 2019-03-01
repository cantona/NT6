// fire.c 炎晶

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(RED "炎晶" NOR, ({ "yan jing", "fire" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", RED "這是一塊炎晶，地肺熔巖受南明離火所化，色赤紅，溫度極高。\n" NOR);
                set("value", 2000);
                set("unit", "塊");
                set("magic/element", "fire");
        }
        setup();
}

// water.c 玄冰

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC "玄冰" NOR, ({ "xuan bing", "water" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIC "這是一塊玄冰，極北萬年冰山所孕，色玄黑，寒氣逼人。\n" NOR);
                set("value", 2000);
                set("unit", "塊");
                set("magic/element", "water");
        }
        setup();
}

inherit ITEM;
inherit F_FOOD;

#include <ansi.h>

void create()
{
        set_name(HIW "饅頭" NOR, ({ "man tou", "man","tou" }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一個饅頭。\n");
                set("unit", "個");
                set("value", 40);
                set("food_remaining", 4);
                set("food_supply", 15);
                set("material", "rice");
        }
        setup();
}
// hualu3.c
#include <ansi.h>;
inherit ITEM;

void create()
{
        set_name(HIY"寒梅花露"NOR, ({ "hua lu" }));
        set_weight(1500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一瓶寒梅花露，看來是花了不少心血泡製成的。\n");
                set("unit", "瓶");
                set("value", 50);
        }
}

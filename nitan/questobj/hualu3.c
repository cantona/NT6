// hualu3.c
#include <ansi.h>;
inherit ITEM;

void create()
{
        set_name(HIB"寒梅花露"NOR, ({ "hanmei hualu", "hualu" }));
        set_weight(1500);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一瓶寒梅花露，看來是花了不少心血泡製成的。\n");
                set("unit", "瓶");
                set("value", 0);
        }
}

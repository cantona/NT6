// yaolu.c

#include <ansi.h>;
inherit ITEM;

void create()
{
        set_name(HIY"銅藥爐"NOR, ({"yaolu", "lu"}));
        set_weight(100000000000000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一座黃銅做的丹爐，燙得有點讓人無法接近。\n");
                set("unit", "座");
                     set("no_get","你是大力士吧？這個也想拿起來？");
                set("value", 2000);
        }
}

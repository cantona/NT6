// yaoshi.c
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"紅玉鑰匙"NOR, ({"tong yaoshi", "yaoshi"}));
        set("long",
                "這是一把看起來很古怪的鑰匙。\n");
        set("unit", "把");
        set_weight(10);
}

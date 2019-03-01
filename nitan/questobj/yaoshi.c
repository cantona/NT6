// yaoshi.c
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"紅玉鑰匙"NOR, ({"hongyu yaoshi", "yaoshi"}));
        set("long", "這是一把看起來很古怪的鑰匙。\n");
        set("taskobj", 1);
        set("unit", "把");
        set("value", 100);
        set("weight", 10);
}

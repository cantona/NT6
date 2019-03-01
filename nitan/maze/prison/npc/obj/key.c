#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "天牢鑰匙" NOR, ({ "tianlao key", "key" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "一把開啟天牢的鑰匙。\n");
                set("value", 200);
                set("maze_item", 1);
        }
        setup();
}


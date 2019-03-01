// yuhulu.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("玉葫蘆", ({ "yu hulu", "hulu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "這是一個美玉雕刻的葫蘆，玲瓏精緻。\n");
                set("value", 8000);
                set("material", "jade");
        }
        setup();
}
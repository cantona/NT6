// dayuanbao.c 大金元寶

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "大金元寶" NOR, ({ "da yuanbao", "da", "yuanbao" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一隻黃澄澄的金元寶。\n");
                set("value", 2000000);
                set("unit", "只");
        }
}

int query_autoload() { return 1; }
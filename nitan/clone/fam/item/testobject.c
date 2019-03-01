#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + MAG "測試物品" NOR, ({"test object"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "這是一件測試物品，還沒有被巫師創造成形，卻發出淡淡紫光。\n" NOR);
                set("unit", "個");
                set("value", 1);
                                set("no_drop", 1);
                                set("no_sell", 1);
                                set("no_give", 1);
                                set("no_get", 1);
        }
}

int query_autoload()
{
        return 1;
}


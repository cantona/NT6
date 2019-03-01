#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "懦惘坒鄴" NOR, ({ "lan baoshikuang", "lan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "輸");
                set("unit", "輸");
                set("base_value", 10000);
                set("base_weight", 600);
        }
        setup();
}
int query_autoload()
{
        return 1;
}
inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "鎮魂之精" NOR, ({"zhenhun zhijing", "zhenhun", "zhijing" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 500000);
                set("enchase/name", "鎮魂之精");
                set("enchase/point", 1);
                set("enchase/type", "head");
                set("limit", 10); // 至少有10個孔的時候方可鑲嵌
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["add_yanjiu" : 10]) );  // 每個提高研究效率10%
        }
        setup();
}

int query_autoload()
{
        return 1;
}


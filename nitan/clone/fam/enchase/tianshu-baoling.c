inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "天書寶靈" NOR, ({"tianshu baoling", "tianshu" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 500000);
                set("enchase/name", "天書寶靈");
                set("enchase/point", 1);
                set("enchase/type", "head");
                set("limit", 12); // 至少有12個孔的時候方可鑲嵌
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["add_jiqu" : 15]) );  // 每個提高研究效率15%
        }
        setup();
}

int query_autoload()
{
        return 1;
}


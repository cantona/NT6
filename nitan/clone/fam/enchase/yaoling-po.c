inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "妖靈·魄" NOR, ({"yaoling po1", "po1" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("value", 500000);
                set("enchase/name", "妖靈·魄");
                set("enchase/point", 1);
                set("enchase/type", "neck");
                                set("enchase/cur_firm", 90);
                                //set("nine_object", 1); // 九孔鑲嵌物品標記
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}


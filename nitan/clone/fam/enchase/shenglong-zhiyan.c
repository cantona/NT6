inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "聖龍之眼" NOR, ({"shenglong zhiyan1", "zhiyan1" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 500000);
                set("enchase/name", "聖龍之眼");
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


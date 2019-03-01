inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "神龍夢幻" NOR, ({"shenlong menghuan2", "menghuan2" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 500000);
                set("enchase/name", "神龍夢幻");
                set("enchase/point", 1);
                set("enchase/type", "neck");
                                set("enchase/cur_firm", 100);
                                //set("nine_object", 1); // 九孔鑲嵌物品標記
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}


inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "紅寶石" NOR, ({"hong baoshi2", "baoshi2" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "一顆紅色閃亮的寶石，乃人間真品。\n" NOR);
                set("unit", "顆");
                set("value", 500000);
                set("enchase/name", "紅寶石");
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


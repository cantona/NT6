inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "紅眼惡魔" NOR, ({"hongyan emo", "hongyan", "emo" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "一顆通紅的寶石，猶如惡魔的眼珠。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "紅眼惡魔");
                set("enchase/point", 1);
                set("enchase/type", "all");
                                set("enchase/cur_firm", 100);
                                set("nine_object", 1); // 九孔鑲嵌物品標記
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}


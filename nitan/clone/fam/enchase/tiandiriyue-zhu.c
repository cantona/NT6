inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "天地日月靈珠" NOR, ({"tiandi riyuezhu", "tiandi", "riyuezhu" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "一顆晶瑩通透，猶露欲滴的寶石，世間罕見。。\n" NOR);
                set("unit", "顆");
                set("value", 5000);
                set("enchase/name", "天地日月靈珠");
                set("enchase/point", 1);
                set("enchase/type", "def");
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


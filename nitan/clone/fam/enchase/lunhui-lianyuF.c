inherit ITEM;
#include <ansi.h>

void create()
{
         set_name(HIW "輪迴·煉獄" NOR, ({"lunhui lianyu","lunhui","lianyu" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                  set("long", HIW "輪迴之苦·煉獄為首。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                 set("enchase/name", "輪迴·煉獄");
                 set("enchase/point", 90);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}


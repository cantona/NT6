inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "輪迴·重生" NOR, ({"lunhui chongsheng","lunhui","chongsheng" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                 set("long", HIM "輪迴之苦·重生而盡。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "輪迴·重生");
                set("enchase/point", 150);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 80);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}


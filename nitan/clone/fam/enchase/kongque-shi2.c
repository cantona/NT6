inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "孔雀石" NOR, ({"kongque shi", "kongque", "shi" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 500000);
                set("enchase/name", "孔雀石");
                set("enchase/point", 1);
                set("enchase/type", "surcoat");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}


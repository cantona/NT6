inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "炎黃﹒國色天香" NOR, ({"guose tianxiang", "guose", "tianxiang" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "炎黃﹒國色天香乃炎黃之神品，放在手心，只見從中透射出陣陣醉人的光芒。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "炎黃﹒國色天香");
                set("enchase/point", 160);
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


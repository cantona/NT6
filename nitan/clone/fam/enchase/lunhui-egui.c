inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "輪迴·餓鬼" NOR, ({"lunhui egui","lunhui","egui" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                 set("long", HIM "輪迴之苦·餓鬼當道。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "輪迴·裁決");
                set("enchase/point", 95);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 85);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}


inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "天轎﹒沉淪" NOR, ({"tianjiao chenlun", "chenlun" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("value", 50000);
                set("enchase/name", "天轎﹒沉淪");
                set("enchase/point", 80);
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


inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "龍女﹒曙光" NOR, ({"longnv shuguang", "longnv", "shuguang" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "龍女﹒曙光乃東海寶物，見光則暗，無光則明。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "龍女﹒曙光");
                set("enchase/point", 200);
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


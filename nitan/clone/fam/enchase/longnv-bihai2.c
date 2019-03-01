inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "龍女﹒碧海神龍" NOR, ({"bihao shenlong", "bihai", "shenlong" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "龍女﹒碧海神龍乃東海之寶，散發著碧藍色的鋒芒。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "龍女﹒碧海神龍");
                set("enchase/point", 190);
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


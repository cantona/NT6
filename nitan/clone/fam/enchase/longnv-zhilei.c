inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "龍女之淚" NOR, ({"longnv zhilei", "longnv", "zhilei" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "傳說龍女之淚乃東海小龍女心淚凝而成，擁有著令世人無法抗拒的力量。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "龍女之淚");
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


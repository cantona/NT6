inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "龍女﹒蝕" NOR, ({"longnv shi", "longnv", "shi" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "龍女﹒蝕呈深紅色，乃東海邪靈所化，拿在手中有種不祥的感覺。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "龍女﹒蝕");
                set("enchase/point", 180);
                set("enchase/type", "all");
                                set("enchase/cur_firm", 90);
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}


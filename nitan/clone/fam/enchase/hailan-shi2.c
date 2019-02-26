inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "海藍石" NOR, ({"hailan shi", "hailan", "shi" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "東海之寶，千年難求。據説是東海龍女嫁粧。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "海藍石");
                set("enchase/point", 1);
                set("enchase/type", "att");
                                set("enchase/cur_firm", 90);
                                set("nine_object", 1); // 九孔鑲嵌物品標記
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}


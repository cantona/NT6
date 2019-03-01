inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + MAG "天羽奇石" NOR, ({"tianyu shi", "tianyu", "shi"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "一塊周身泛著紫光的石頭，似乎蘊藏著不尋常的力量。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "天羽奇石");
                set("enchase/point", 30);
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


inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "天魔·妖晶" NOR, ({"tianmo yaojing", "yaojing" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一塊晶瑩的寶石，拿在手中卻有一種不詳的感覺。\n" NOR);
                set("unit", "塊");
                set("value", 50000);
                set("enchase/name", "天魔·妖晶");
                set("enchase/point", 90);
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


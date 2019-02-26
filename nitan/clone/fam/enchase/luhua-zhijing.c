inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "露華之晶" NOR, ({"luhua zhijing", "luhua", "zhijing" }));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "露華之晶乃是崑崙仙境之顛的露珠，吸取宇宙大地之塵埃結晶而成，藴涵宇宙萬物之精華。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "露華之晶");
                set("enchase/point", 1);
                set("enchase/type", "10k");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["luhua-zhijing":1]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}


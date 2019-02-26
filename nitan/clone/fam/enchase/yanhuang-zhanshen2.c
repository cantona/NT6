 inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "炎黃·戰神" NOR, ({"yanhuang zhanshen", "yanhuang", "zhanshen" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "炎黃·戰神乃炎黃之神品，擁有着無窮的力量。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "炎黃·戰神");
                set("enchase/point", 160);
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


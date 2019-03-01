inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "炎黃之星" NOR, ({"yhhero" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                 set("long", HIG "炎黃之星乃炎黃之神品，你將它放在手上卻隱隱有種臨攝天下的感覺。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "炎黃之星");
                set("enchase/point", 200);
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


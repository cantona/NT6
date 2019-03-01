inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "炎黃﹒君臨天下" NOR, ({"junlin tianxia", "junlin", "tianxia" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "炎黃﹒君臨天下乃炎黃之神品，你將它放在手上卻隱隱有種臨攝天下的感覺。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "炎黃﹒君臨天下");
                set("enchase/point", 220);
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


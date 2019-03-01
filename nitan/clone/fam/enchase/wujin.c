inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + BLU "鎢精" NOR, ({"wu jing", "wu", "jing"}));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + BLU "一塊看似普通的礦物，周身烏黑，投射出陣陣攝人氣息。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
                set("enchase/name", "鎢精");
                set("enchase/point", 40);
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


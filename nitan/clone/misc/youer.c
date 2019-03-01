#include <ansi.h>
inherit COMBINED_ITEM; 

void create()
{
        set_name(HIY "誘餌" NOR, ({ "you er","you", "er" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是專門用來引誘各種禽獸的。 \n");
                set("base_unit", "塊"); 
                set("base_weight", 30); 
                set("base_value", 1000); 
                set("no_sell", "這野獸吃的東西你也給我？"); 
                set("lure", 1);
                set("level", 10);
        }
        set_amount(1);
        setup();
}

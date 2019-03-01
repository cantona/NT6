#include "herb.h"

void create()
{
        set_name(HIC "六月還陽" NOR, ({ "hy-ly", "Sedum aizoon", "herb_hy_ly" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "景天科植物費菜(Sedum aizoon)的全草或根。因其在6月開始開花，；故得此名。又因它具有活血化瘀、止血的功效，民間認為其療效可以同參三七娘美，故又稱：為“土三七”。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

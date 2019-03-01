#include "herb.h"

void create()
{
        set_name(HIC "五月還陽" NOR, ({ "huanyang5", "Sedum odontophyllum", "herb_5yhuanyang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "景天科植物齒葉景天(Sedum odontophyllum)的全草。因它消腫止痛功效很強，又因這一植物一般在5月開花，所以也稱“五月還陽”。\n" NOR);
                set("base_unit", "根");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}


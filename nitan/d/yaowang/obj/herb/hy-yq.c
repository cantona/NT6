#include "herb.h"

void create()
{
        set_name(HIC "鴉雀還陽" NOR, ({ "hy-yq", "Pholidota yunnanensis", "herb_hy_yq" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "蘭科植物雲南石仙桃(Pholidota yunnanensis)的帶假鱗莖的全草。因其兩葉形似喜鵲張嘴.故得此名。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

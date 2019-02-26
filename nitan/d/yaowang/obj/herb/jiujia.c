#include "herb.h"

void create()
{
        set_name(HIW "大救駕" NOR, ({ "dajiujia", "Chamaenerion angustifloium", "herb_jiujia" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "柳葉菜科植物柳蘭(Chamaenerion angustifloium)的乾燥根莖，因其具有活血散瘀、止痛的功效，可治療跌打損傷、骨折等症，且藥效作用快，故得此名。\n" NOR);
                set("base_unit", "根");
                set("base_value", 30000);
                set("base_weight", 100);
        }
        setup();
}

#include <ansi.h>
#include "stone.h"

void create()
{
        set_name(HIY "嵐石" NOR, ({ "lan shi", "lan", "shi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "顆");
                set("base_value", 50000);
                set("base_weight", 100);
        }
        setup();
}

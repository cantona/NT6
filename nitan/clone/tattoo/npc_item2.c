#include <weapon.h>
#include <ansi.h>

inherit PIN;

void create()
{
        set_name(HIY "金針" NOR, ({ "jin zhen", "jin", "zhen", "pin" }));
        set_weight(24);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", HIY "鑄造極為精細的金針，有著各種用途。\n" NOR);
                set("value", 120);
                set("material", "silver");
                set("wield_msg", HIY "$N手一抖，亮出一根$n。\n" NOR);
                set("unwield_msg", HIY "$N收起了$n。\n" NOR);
        }

        init_pin(20);
        setup();
}
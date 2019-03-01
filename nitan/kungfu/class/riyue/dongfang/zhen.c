#include <ansi.h>
#include <weapon.h>

inherit PIN;

void create()
{
        set_name(HIY "長針" NOR, ({ "zhen" }) );
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long",HIY "這是一根細長的針。\n" NOR);
                set("value", 300);
                set("material", "iron");
                set("wield_msg", "$N拿出一根$n，捏在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
                set("stable", 0);
        }

        init_pin(55);
        setup();
}
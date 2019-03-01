#include <ansi.h>
#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name(HIY "金火槍" NOR, ({"jin huoqiang", "jin", "huoqiang"}));
        set_weight(5000);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", HIY "一支由黃金鑄成，做工精細的火槍。\n" NOR);
                set("value", 25000);
                set("wield_msg", HIY "$N摸出一支金黃色的火槍握在手中。\n" NOR);
                set("unwield_msg", HIY "$N把手中的金火槍放入懷中。\n" NOR);
        }
        init_hammer(30);
        setup();
}
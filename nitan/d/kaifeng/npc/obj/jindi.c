#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIY "金笛" NOR, ({ "jin di", "jin", "di" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", HIY "一根由純金打鑄的笛子，在陽光下閃閃生輝。\n" NOR);
                set("value", 25000);
                set("material", "steel");
                set("wield_msg", HIY "$N" HIY "從腰間抽出一根金笛握在手中，輕輕玩弄。\n" NOR);
                set("unwield_msg", HIY "$N" HIY "微微一笑，將手中的金笛插回腰間。\n" NOR);
        }
        init_sword(30);
        setup();
}
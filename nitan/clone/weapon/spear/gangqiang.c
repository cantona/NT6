// gangqiang.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>

inherit SPEAR;

void create()
{
        set_name(HIC "點鋼槍" NOR, ({ "steel spear","qiang","spear" }));
        set_weight(9000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "杆");
                set("value", 14000);
                set("material", "steel");
                set("long", "一柄烏黑的鋼槍，上面連槍纓都沒有。\n");
                set("wield_msg", "$N橫握起一柄$n，果然威風凜凜。\n");
                set("unwield_msg", "$N收起$n，想順手擼一下槍纓，卻沒找到。\n");
        }
        init_spear(60);
        setup();
}

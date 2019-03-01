// snow_sword.c 

#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIB"風回"HIW"雪舞"HIG"劍"NOR, ({"snowsword","xue jian","sword"}));
        set_weight(400);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 0);
                set("material", "steel");
                set("long", "這是一把用來練舞的劍，劍身細長，輕巧尤鋒利。\n");
                set("wield_msg", "$N抽出一把劍身細長的劍，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        setup();
}

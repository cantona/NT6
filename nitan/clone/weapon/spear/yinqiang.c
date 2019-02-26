// yinqiang.c
// Last Modified by winder on May. 25 2001

#include <ansi.h>
#include <weapon.h>
inherit SPEAR;

void create()
{
        set_name(HIW "亮銀槍" NOR, ({"silver spear", "qiang", "spear"}));
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long","這是把沉重的長槍，槍尖是純銀打製，鋒利無比．\n");
                set("value", 18000);
                set("material", "silver");
                set("wield_msg","$N拿出一把$n握在手中，眼前閃過一道寒光．\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_spear(70);
        setup();
}

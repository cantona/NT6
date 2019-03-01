// jinqiang.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>
inherit SPEAR;

void create()
{
        set_name(HIY "點金槍" NOR, ({ "golden spear","qiang","spear" }));
        set_weight(14000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("value", 10000);
                set("material", "gold");
                set("long", "此槍以黃金為頭銅為桿。\n");
                set("wield_msg", "$N抄起一桿$n，順手抖了個槍花。\n");
        }
        init_spear(60);
        setup();
}

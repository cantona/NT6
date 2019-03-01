// shexing.c

#include <ansi.h>
#include <weapon.h>

inherit STAFF;

void create()
{
        set_name(HIC"蛇形杖"NOR, ({"shexing zhang", "zhang"}) );
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "條");
                set("long", "一條蛇形長杖，是歐陽克的兵器。\n");
                set("value", 50000);
                set("material", "steel");
                set("wield_msg", "“嗖”的一聲，$N手中已多了一根$n。\n");
                set("unwield_msg", "你眼前一花，$N手中的$n已不見了。\n");
        }

        init_staff(30);
        setup();
}
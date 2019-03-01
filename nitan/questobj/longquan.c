// youlong.c

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(CYN"龍泉劍"NOR, ({ "longquan sword", "longquan", "sword" }) );
        set("taskobj", 1);
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long",
"這是柄一看就知道是寶劍的利器。\n");
                set("value", 0);
                set("material", "blacksteel");
                set("wield_msg", 
"只聽見「颼」地一聲，$N的手中已經多了一把寒光四射的寶劍──$n。\n");
                set("unequip_msg", "$N將手中的$n插入腰間的劍鞘。\n");
        }
        setup();
}


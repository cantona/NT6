// youlong.c

#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("游龍劍", ({ "youlong sword", "youlong", "sword" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",
"這是把看起來很普通的長劍，但仔細一看，劍身上有幾條細紋閃爍不定。\n");
                set("value", 2400);
                set("material", "steel");
                set("wield_msg", 
"只聽見「颼」地一聲，$N的手中已經多了一把寒光四射的寶劍——$n。\n");
                set("unequip_msg", "$N將手中的$n插入腰間的劍鞘。\n");
                set("stable", 75);
        }
        init_sword(80);
        setup();
}
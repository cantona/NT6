// youlong.c 遊龍劍
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name("遊龍劍", ({ "youlong sword", "youlong", "sword" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",
"這是把看起來很普通的長劍，但仔細一看，劍身上有幾條細紋閃爍不定。\n");
                set("value", 2400);
                set("material", "blacksteel");
                set("wield_msg", 
"只聽見「颼」地一聲，$N的手中已經多了一把寒光四射的寶劍──$n。\n");
                set("unequip_msg", "$N將手中的$n插入腰間的劍鞘。\n");
        }
        init_sword(100);
        setup();
}

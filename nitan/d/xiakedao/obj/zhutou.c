// zhutou.c

#include <weapon.h>

inherit HAMMER;
inherit F_FOOD;

void create()
{
        set_name("豬頭", ({ "zhutou","tou" }) );
        set_weight(350);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一個大豬頭。\n");
                set("value", 80);
                set("unit", "顆");
                set("food_remaining", 4);
                set("food_supply", 15);
                set("wield_msg", "$N抓起一顆$n，握在手中當武器。\n");
                set("material", "bone");
        }
        init_hammer(1);
        setup();
}

int finish_eat()
{
        if( !query("weapon_prop") ) return 0;
        set_name("啃得精光的骨頭", ({ "bone" }) );
        set_weight(150);
        set("long", "啃得精光的骨頭。\n");
        return 1;
}
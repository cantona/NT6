//shigu.c
#include <weapon.h>

inherit HAMMER;

void create()
{
    set_name("屍骨", ({ "shi gu", "shi","gu" }) );
    set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("value", 50);
                set("material", "wood");
                set("long", "這是一隻白森森的屍骨。\n");
                set("wield_msg","$N手中握住一把$n，眼中露出陰邪的笑意。\n");
                set("unwield_msg", "$N將$n插回腰間，臉色頓時也恢復了正常。\n");
        }
            init_hammer(10);
        setup();
}
// jitui.c 雞腿

#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name("啃得精光的雞腿骨頭", ({ "bone" }));
        set_weight(150);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一根啃得精光的雞腿骨頭。\n");
                set("unit", "根");
                set("wield_msg", "$N抓起一根$n，握在手中當武器。\n");
                set("material", "bone");
        }
        init_hammer(1);
        setup();
}
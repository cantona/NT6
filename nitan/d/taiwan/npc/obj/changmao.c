// changmao.c 長矛
// Last Modifyed by Ahda on Jan. 4 2002

#include <weapon.h>
inherit SPEAR;

void create()
{
        set_name("長矛", ({ "changmao" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("long", "這是一根用木頭削尖的長矛。\n");
                set("value", 0);
                set("rigidity",50);
                set("material", "bamboo");
                set("wield_msg", "$N掣出一桿$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n反別身後。\n");
        }
        init_spear(25);
        setup();
}

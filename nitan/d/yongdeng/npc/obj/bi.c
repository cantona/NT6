// bi.c

#include <weapon.h>
#include <ansi.h>
inherit DAGGER;

void create()
{
        set_name(HIC"判官筆"NOR, ({ "panguan bi" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枝");
                set("long", "這是一枝精鐵打就的判官筆。\n");
                set("value", 1500);
                set("rigidity",100);
                set("material", "steel");
                set("wield_msg", "$N掣出一枝$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n反別腰後。\n");
        }
          init_dagger(20);
        setup();
}

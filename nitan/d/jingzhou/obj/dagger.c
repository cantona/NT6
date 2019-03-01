// gangjian.c

#include <weapon.h>
inherit DAGGER;

void create()
{
        set_name("普通匕首", ({ "bishou" }));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把普通的小匕首。用來暗算別人比較合適。\n");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N從兜裡掏出一把$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n放會兜裡。\n");
        }
        init_dagger(30,0);
        setup();
}
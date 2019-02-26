// gangjian.c

#include <weapon.h>
inherit DAGGER;

void create()
{
        set_name("紙扇", ({ "zhi shan", "shan" }));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把製作精美的紙扇，上面寫着“白駝少主”四個鏤金纂字。\n");
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N從兜裏掏出一把$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n放會兜裏。\n");
        }
        init_dagger(100,0);
        setup();
}
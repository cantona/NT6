#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
        set_name(NOR + CYN "鐵骨扇" NOR, ({ "tiegu shan", "tigu", "shan" }));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", NOR + CYN "這是一把鐵骨扇，武林中人常常"
                            "用它作為打穴的兵器。\n" NOR);
                set("value", 3000);
                set("material", "steel");
                set("wield_msg", "$N從兜裏掏出一把$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n放回兜裏。\n");
        }
        init_dagger(40, 0);
        setup();
}
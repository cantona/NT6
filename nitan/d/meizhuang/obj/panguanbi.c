#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
        set_name(NOR + CYN "判官筆" NOR, ({ "panguan bi", "bi", "panguan" }));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", "一支鑌鐵所鑄的判官筆，武林中人常常用它作為打穴的兵器。\n");
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N從兜裡掏出一把$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n放回兜裡。\n");
        }
        init_dagger(40, 0);
        setup();
}
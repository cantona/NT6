#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
        set_name(WHT "毛筆" NOR, ({ "mao bi", "bi", "mao" }));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", "一支普通的毛筆，武林中人常常用它作為打穴的兵器。\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N從兜裏掏出一把$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n放回兜裏。\n");
        }
        init_dagger(15, 0);
        setup();
}
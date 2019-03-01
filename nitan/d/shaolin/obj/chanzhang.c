#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("禪杖", ({ "chan zhang", "zhang" }));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根黑黝黝的鑌鐵禪杖，約四十來斤，是件稱手的重兵器。\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
                set("shaolin",1);
        }
        init_staff(25);
        setup();
}

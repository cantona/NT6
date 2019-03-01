#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("哭喪棒", ({ "kusang bang", "kusang", "bang" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根精鐵打鑄的哭喪棒。\n");
                set("value", 800);
                set("rigidity", 100);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        init_staff(35);
        setup();
}
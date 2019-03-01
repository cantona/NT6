// langyabang.c 狼牙棒
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
inherit STICK;
inherit F_UNIQUE;

void create()
{
        set_name("狼牙棒", ({ "langya bang", "bang", "stick" }));
        set_weight(30000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根兩頭狼牙棒，約兩百來斤，是件稱手的重兵器。\n");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
                set("shaolin",1);
        }
        init_stick(150);
        setup();
}

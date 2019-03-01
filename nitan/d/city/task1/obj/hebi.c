// hebi.c 鶴嘴筆

#include <weapon.h>
inherit DAGGER;

void create()
{
        set_name("鶴嘴筆", ({ "hebi" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", "這是一支筆端銳如鶴嘴，卻是晶光閃亮的兵器。\n");
                set("value", 1500);
                set("rigidity",100);
                set("material", "steel");
                set("wield_msg", "$N抽出一支$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
          init_dagger(40);
        setup();
}
// gangzhang.c 鋼杖

#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("鋼杖", ({ "gangzhang" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根粗重的鋼杖。\n");
                set("value", 500);
                set("rigidity",100);
            set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
          init_staff(25);
        setup();
}
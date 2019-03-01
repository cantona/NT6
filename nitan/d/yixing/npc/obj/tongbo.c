//Cracked by Kafei
// tongbo.c 銅鈸

#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("銅鈸", ({ "tongbo", "bo" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "對");
                set("long", "這是一對銅鈸，鈸邊閃閃生光，鋒利異常。\n");
                set("value", 300);
                set("material", "steel");
                set("wield_msg", "$N取出一對$n，雙手合處，當地一聲，震耳欲聾。\n");
                set("unwield_msg", "$N將手中的$n收好。\n");
        }
        init_blade(30);
        setup();
}
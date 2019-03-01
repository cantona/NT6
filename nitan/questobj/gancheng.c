// gancheng.c

#include <weapon.h>
inherit CLUB;

void create()
{
        set_name("桿秤", ({ "gan cheng" }));
        set_weight(5000);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("long", "一桿鬧市貨物常用的桿秤。\n");
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N抽出一桿$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        setup();
}
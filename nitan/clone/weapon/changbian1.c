// longsword.c 長鞭

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("長鞭", ({ "changbian", "bian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long","這是一柄比武專用的長鞭,威力非比尋常。\n");
                set("value", 0);
                set("material", "leather");
                set("wield_msg", "$N「唰」的一聲抖出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n捲回腰間。\n");
        }
        init_whip(100);
        setup();
}
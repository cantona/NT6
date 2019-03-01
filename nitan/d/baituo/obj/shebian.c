#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("蛇鞭", ({ "she bian", "she", "bian" }));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄蛇皮長鞭。\n");
                set("value", 300);
                set("material", "leather");
                set("wield_msg", "$N「唰」的一聲抖出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n卷回腰間。\n");
        }
        init_whip(30);
        setup();
}
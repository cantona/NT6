// changbian.c 長鞭

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
                set("long", "這是一柄普通的長鞭，由水牛皮精工編織而成。\n");
                set("value", 100);
                set("material", "leather");
                set("wield_msg", "$N「唰」的一聲抖出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n卷回腰間。\n");
        }
        init_whip(25);
        setup();
}

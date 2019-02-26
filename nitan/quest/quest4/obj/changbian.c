// longsword.c 長鞭

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("長鞭", ({ "changbian", "bian" }));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄普通的長鞭，由水牛精工編織而成。\n");
                set("rigidity", 100); 
                set("value", 100);
                set("material", "leather");
                set("wield_msg", "$N「唰」的一聲抖出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n捲回腰間。\n");
        }
        init_whip(40);
        setup();
}


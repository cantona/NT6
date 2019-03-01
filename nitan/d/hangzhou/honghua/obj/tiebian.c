// tiebian.c 鐵鞭

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("鐵鞭", ({ "changbian", "bian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄粗大的鐵鞭，總有三十來斤重。\n");
                set("value", 100);
                set("material", "leather");
                set("wield_msg", "$N「唰」的一聲抖出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n別回腰間。\n");
        }
        init_whip(40);
        setup();
}
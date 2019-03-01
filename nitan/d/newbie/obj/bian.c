// bian.c 鞭

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("長鞭", ({ "chang bian", "bian","whip" }));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄普通的長鞭，做工粗糙。\n");
                set("wield_msg", "$N「唰」的一聲從腰後抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n別回腰後。\n");
        }
        init_whip(5);
        setup();
}

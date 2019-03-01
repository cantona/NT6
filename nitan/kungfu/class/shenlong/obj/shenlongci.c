// shenlongchi.c 神龍刺

#include <ansi.h>
#include <weapon.h>
inherit HOOK;

void create()
{
        set_name(HIY"神龍刺"NOR, ({ "shenlong ci", "ci" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long","這是一柄短小晶亮、前帶彎鉤的兵器，是神龍島的獨門兵器。\n");
                set("value", 500);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回後腰。\n");
        }
        init_hook(30);
        setup();
}

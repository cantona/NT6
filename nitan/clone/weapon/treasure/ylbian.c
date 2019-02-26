// ylbian.c 雲龍鞭

#include <ansi.h>
#include <weapon.h>
inherit WHIP;
inherit F_UNIQUE;

void create()
{
        set_name(HIC "雲龍鞭" NOR, ({ "yunlong bian", "bian" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是天地會總舵主陳近南的貼身神兵。\n");
                set("value", 100);
                set("material", "leather");
                set("wield_msg", "$N「唰」的一聲抖出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n捲回腰間。\n");
        }
        init_whip(150);
        setup();
}
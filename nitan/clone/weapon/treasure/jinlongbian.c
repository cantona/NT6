// jinlongbian.c 金龍鞭

#include <ansi.h>
#include <weapon.h>
inherit WHIP;
inherit F_UNIQUE;

void create()
{
        set_name(YEL "金龍鞭" NOR, ({ "jinlong bian", "bian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是西域富商大賈尹克西的貼身兵器金龍鞭，\n"
                            "它的柄乃純金打造而成，通身鑲滿各種寶石。\n");
                set("value", 20000);
                set("material", "leather");
                set("wield_msg", "$N「唰」的一聲抖出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n捲回腰間。\n");
        }
        init_whip(150);
        setup();
}
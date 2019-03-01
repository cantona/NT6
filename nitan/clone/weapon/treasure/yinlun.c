// yinlun.c 銀輪
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>;
#include <weapon.h>;
inherit HAMMER;
inherit F_UNIQUE;

void create()
{
        set_name(HIW"銀輪"NOR ,({ "yin lun", "lun", "yinlun" }));
        set_weight(70000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",HIW"這是一柄銀光閃閃的法輪。\n"NOR);
                set("value", 10000);
                set("material", "silver");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg","$N將手中的$n放回腰間。\n");
        }
        init_hammer(100);
        setup();
}
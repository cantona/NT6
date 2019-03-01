// greenwater-sword.c 碧水劍
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
#include <ansi.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(HIG"碧水劍"NOR, ({ "greenwater sword", "jian", "sword" }) );
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把通體晶瑩剔透的劍!\n");
                set("value", 400);
                set("material", "crimsonsteel");
                set("wield_msg", "$N「唰」地一聲抽出一把$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插入腰間的劍鞘。\n");
        }
        init_sword(100);
        setup();
}
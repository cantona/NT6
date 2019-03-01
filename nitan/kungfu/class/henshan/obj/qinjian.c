// qinjian.c
// Last Modified by winder on Sep. 2 2001

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("琴劍", ({ "qin jian", "jian", "sword" }) );
        set_weight(1400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 700);
                set("material", "steel");
                set("long", "這是一把又細又長的劍，反手插在胡琴裡。是衡山派掌門莫大先生的配劍。\n");
                set("wield_msg", "只聽“叮當”一聲輕響，$N從琴底抽出一把極細極亮的劍來。\n");
                set("unequip_msg", "“叮當”一聲響，$N反手把劍插回胡琴底。\n");
                set("weapon_prop/courage", -4);
        }
        init_sword(50);
        setup();
}
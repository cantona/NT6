// fork.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>

inherit FORK;

void create()
{
        set_name("鋼叉", ({ "gang cha", "cha","fork" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 1000);
                set("material", "iron");
                set("long", "一柄鋒利的鋼叉。\n");
                set("wield_msg", "$N抄起一柄$n，還拿衣服擦了擦叉尖。\n");
        }
        init_fork(25);
        setup();
}

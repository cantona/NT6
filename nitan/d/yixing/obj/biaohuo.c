// /d/yixing/obj/biaohuo.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(RED"紅鏢"NOR, ({"hong biao", "biao"}));
        set("weight", 20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一份紅鏢，包裝非常仔細，不知裝著什麼東西。\n");
                set("unit", "份");
                set("value", 30);
        }
        setup();
}
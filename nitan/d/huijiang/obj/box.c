// Room: /d/huijiang/obj/box.c 寶箱
// Last Modified by winder on Sep. 12 2001

#include <ansi.h>;
inherit ITEM;

void create()
{
        set_name(YEL"寶箱"NOR, ({ "gold xiang", "xiang", "box" }) );
        set_weight(3000);
        set_max_encumbrance(500000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long","一個裝錢的箱子，紅花會從各地劫來的不義之財全放在這裏。\n");
                set("value", 1000);
                set("material", "wood");
                set("no_get",1);
                set("no_drop",1);
                set("amount",30);
        }
        setup();
}

int is_container() { return 1; }
// Room: /d/gumu/obj/box.c 鐵盒
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(RED "大鐵盒" NOR, ({ "da tiehe", "tiehe", "box" }) );
        set_weight(30000000);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一個鏽跡斑斑的大鐵盒子，看來很久沒有人動過了。\n");
                set("value", 1000);
                set("material", "steel");
                set("no_get",1);
                set("no_drop",1);
                set("amount",30);
        }
        setup();
}

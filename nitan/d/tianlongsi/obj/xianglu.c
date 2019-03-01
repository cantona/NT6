#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("香爐", ({ "xiang lu", "lu" }) );
        set_weight(3000);
        set_max_encumbrance(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是一個廟裡常見的香爐，用來讓善男信女們插香(pushin)進願。\n");
                set("value", 1000);
                set("material", "gold");
                set("no_get",1);
                set("no_drop",1);
                set("amount",30);
        }
        setup();
}

void init()
{
        add_action("do_pushin", "pushin");
}

int do_pushin(string arg)
{
        object me, ob;
        
        me = this_player();

        if(!arg&&arg!="xiang") return notify_fail("你要插什麼東西？\n");

        // if( me->query_temp("marks/dian_temp") &&  random(2) == 1 )
        if( random(2) == 1 )
        {
                ob=new("/d/tianlongsi/obj/box");
                ob->move(me);
                tell_object(me, "\n你忽然覺得香在插下時被什麼擋住了！\n你扒開香灰，發現了一個盒子。\n");
                return 1;
        }
        else
                return notify_fail("你把一柱香插進香爐，拜了兩拜。\n");
        return 0;
}
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
這裏是絕情谷內堂西側一間廚房，平常絕情谷的弟子們餓
了便可以到這裏來要(serve)些食物吃。房中灶火正旺，一個
廚師正忙的滿頭大汗。屋角放着一個大水缸。  
LONG);
        set("exits", ([
               "east" : __DIR__"neitang",
        ]));
        
        set("objects", ([
                __DIR__"npc/chushi" : 1,
        ]));

        set("no_fight", 1);
        set("ricewater", 5);

        setup();
}

void init()
{
        add_action("do_serve", "serve");
}

int do_serve()
{
        object me;
        object food;
        object water;
        me = this_player();

        if( query("family/family_name", me) != "絕情谷" )
                return notify_fail(CYN "廚師大眼一瞪，説道：你又不是絕情谷的，吃白食啊？\n" NOR);

        if (present("man tou", this_player())) 
                return notify_fail(CYN "廚師眉頭一皺，説道：吃完了再拿，別浪費食物。\n" NOR);

        if (present("water", this_object())) 
                return notify_fail(CYN "廚師眉頭一皺，説道：吃完了再拿，別浪費食物。\n" NOR);

        if (query("ricewater") > 0)
        {
                message_vision(CYN "廚師將一個饅頭和一碗清水遞到$N手中，笑"
                               "道：你慢用。\n" NOR, me);
                food = new(__DIR__"npc/obj/mantou");
                water = new(__DIR__"npc/obj/water");
                food->move(me);
                water->move(me);
                addn("ricewater", -1);
        }
        else 
                message_vision(CYN "廚師對$N" CYN "歉聲道：嗨，吃的喝的都"
                               "沒了。\n" NOR, me);
        return 1; 
}



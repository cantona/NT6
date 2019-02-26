#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
這裏是衡山派長廊東北側的一間廚房，平常衡山的弟子們餓了便
可以到這裏來要(serve)些食物吃。房中灶火正旺，一個廚師正忙的滿
頭大汗。屋角放着一個大水缸。  
LONG );
        set("exits", ([
                 "southwest" : __DIR__"changlang",
        ]));
        
        set("objects", ([
                __DIR__"npc/chushi" : 1,
        ]));

        set("ricewater", 5);

	set("coor/x", -6910);
	set("coor/y", -5480);
	set("coor/z", 40);
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

        if( query("family/family_name", me) != "衡山派" )
                return notify_fail(CYN "廚師大眼一瞪，説道：你又不是衡山派的，吃白食啊？\n" NOR);

        if (present("man tou", this_player())) 
                return notify_fail(CYN "廚師眉頭一皺，説道：吃完了再拿，別浪費食物。\n" NOR);

        if (present("water", this_object())) 
                return notify_fail(CYN "廚師眉頭一皺，説道：吃完了再拿，別浪費食物。\n" NOR);

        if (query("ricewater") > 0)
        {
                message_vision(CYN "廚師將一個饅頭和一碗清水遞到$N手中，笑"
                               "道：你慢用。\n" NOR, me);
                food = new(__DIR__"obj/mantou");
                water = new(__DIR__"obj/water");
                food->move(me);
                water->move(me);
                addn("ricewater", -1);
        }
        else 
                message_vision(CYN "廚師對$N" CYN "歉聲道：嗨，吃的喝的都"
                               "沒了。\n" NOR,me);
        return 1; 
}
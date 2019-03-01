#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
這裡是苗家大院北側的一間廚房，平常苗家的弟子們餓了
便可以到這裡來要 (serve)些食物。房中灶火正旺，一個大廚
師正忙的滿頭大汗。屋角放著一個大水缸。  
LONG);
        set("exits", ([
                  "south" : __DIR__"miaojia_dayuan",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/chushi" : 1,
        ]));
        set("ricewater", 5);
        set("coor/x", -9020);
	set("coor/y", -950);
	set("coor/z", 0);
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

        if( query("family/family_name", me) != "中原苗家" )
                return notify_fail(CYN "廚師大眼一瞪，說道：你又不是苗家的，吃白食啊？\n" NOR);

        if (present("rice", this_player())) 
                return notify_fail(CYN "廚師眉頭一皺，說道：吃完了再拿，別浪費食物。\n" NOR);

        if (present("soup", this_object())) 
                return notify_fail(CYN "廚師眉頭一皺，說道：吃完了再拿，別浪費食物。\n" NOR);

        if (query("ricewater") > 0)
        {
                message_vision(CYN "廚師將熱氣騰騰的飯菜遞到你手中，笑"
                               "道：你慢用。\n" NOR, me);
                food = new("/d/kaifeng/obj/rice");
                water = new("/d/kaifeng/obj/soup");
                food->move(me);
                water->move(me);
                addn("ricewater", -1);
        }
        else 
                message_vision(CYN "廚師對$N" CYN "歉聲道：嗨，吃的喝的都"
                               "沒了。\n" NOR,me);
        return 1; 
}
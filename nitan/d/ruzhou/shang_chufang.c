#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
這裏是商家堡後院西側的一間廚房，平常商家的弟子們餓了
便可以到這裏來要 (serve)些食物。房中灶火正旺，一個大廚師
正忙的滿頭大汗。屋角放着一個大水缸。  
LONG);
        set("exits", ([
                "east"  : __DIR__"shang_houyuan",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/shang3" : 1,
        ]));
        set("ricewater", 5);
	set("coor/x", -6760);
	set("coor/y", 1920);
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

        if( query("family/family_name", me) != "商家堡" )
                return notify_fail(CYN "廚師大眼一瞪，説道：你又不是商家堡的，吃白食啊？\n" NOR);

        if (present("tangcu liji", this_player())) 
                return notify_fail(CYN "廚師眉頭一皺，説道：吃完了再拿，別浪費食物。\n" NOR);

        if (present("soup", this_object())) 
                return notify_fail(CYN "廚師眉頭一皺，説道：吃完了再拿，別浪費食物。\n" NOR);

        if (query("ricewater") > 0)
        {
                message_vision(CYN "廚師將熱氣騰騰的飯菜遞到你手中，笑"
                               "道：你慢用。\n" NOR, me);
                food = new("/d/shaolin/obj/food");
                water = new("/d/shaolin/obj/soup");
                food->move(me);
                water->move(me);
                addn("ricewater", -1);
        }
        else 
                message_vision(CYN "廚師對$N" CYN "歉聲道：嗨，吃的喝的都"
                               "沒了。\n" NOR,me);
        return 1; 
}
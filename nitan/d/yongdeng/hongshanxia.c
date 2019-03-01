// Room: /huanghe/hongshanxia.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "紅山峽");
        set("long", @LONG
紅山峽是個非常險峻的峽谷，兩邊是數十丈的黃土坡，很是陡峭，中
間只有一條可以通行一人一馬的窄道，俗稱“一線天”。附近沒有什麼生
物，卻有商旅常在這裡失蹤。
LONG );
        set("exits", ([
                "north"     : __DIR__"shimen",
                "south"     : __DIR__"jingyuan",
        ]));
        set("objects", ([
                __DIR__"npc/mazei" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16070);
	set("coor/y", 4260);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
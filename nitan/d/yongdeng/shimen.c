// Room: /huanghe/shimen.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "石門");
        set("long", @LONG
這裏是石門，是西夏的採石場，當地沒有別的物產，只有遍地的白玉
石，西夏王宮裏的玉石地板就是用這裏出產的白玉石鋪成的。時常有大批
的苦力被官府徵到這兒來，沒日沒夜的開採白玉石礦，許多人倒下後就沒
有再站起來。北面有一座寺廟。
LONG );
        set("exits", ([
                "northwest" : __DIR__"yinpanshui",
                "south"     : __DIR__"hongshanxia",
                "north"     : __DIR__"wufosi",
        ]));
        set("objects", ([
                __DIR__"npc/xixiabing" : 1,
                __DIR__"npc/caishiren" : 2,
        ]));
        set("outdoors", "yongdeng");
        set("coor/x", -16070);
	set("coor/y", 4270);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
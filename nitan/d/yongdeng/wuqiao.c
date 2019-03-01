// Room: /huanghe/wuqiao.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "烏鞘嶺");
        set("long", @LONG
烏鞘嶺是武威東南的一個險要地段，黑石山上密林重重，時常有野
獸出沒。一條官道從山下蜿蜒而過。
LONG );
        set("exits", ([
                "south"     : __DIR__"dacaigou",
                "northwest" : __DIR__"wuwei",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16100);
	set("coor/y", 4230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
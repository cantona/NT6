// Room: /huanghe/gulang.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "古浪");
        set("long", @LONG
古浪城建于西周，本名鬼武，後整修于漢，更名古浪。古浪是西北
地區的毛皮集散地，當初的紫羊羔皮襖，一出于張家口，另一出處就是
古浪了，過了古浪再往西四十裡，跨過紀水河即到蘭州。
LONG );
        set("exits", ([
                "south"     : __DIR__"yongdeng",
                "north"     : __DIR__"xueguan",
                "east"      : __DIR__"yaocaidian",
                "west"      : __DIR__"xiaojiaqiao",
                "northeast" : __DIR__"dacaigou",
        ]));
        set("objects", ([
                "/d/taishan/npc/dao-ke" : 1,
        ]));
        set("outdoors", "yongdeng");
        set("coor/x", -16110);
	set("coor/y", 4210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
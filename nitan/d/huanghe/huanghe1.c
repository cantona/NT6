// Room: /huanghe/huanghe1.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃河岸邊");
        set("long", @LONG
這裏是黃河岸邊。黃河流淌到這裏，已經泥沙渾濁了。黃色的河水
在河牀裏翻滾着，咆哮着，捲起一個個巨大的漩渦。西邊有個寨子。
LONG );
        set("exits", ([
                "north" : __DIR__"weifen",
                //"south" : __DIR__"tiandi4", 
                "east"  : __DIR__"huanghe2",
                "west"  : __DIR__"huanghegate",
        ]));
        set("objects", ([
                __DIR__"npc/hou" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -1000);
        set("coor/y", 520);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

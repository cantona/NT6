// Room: /huanghe/huanghe2.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃河岸邊");
        set("long", @LONG
這裡是黃河岸邊。黃河流淌到這裡，已經泥沙渾濁了。黃色的河水
在河床裡翻滾著，咆哮著，卷起一個個巨大的漩渦。
LONG );
        set("exits", ([
                "south" : __DIR__"tiandi4", 
                "east"  : __DIR__"huanghe3",
                "west"  : __DIR__"huanghe1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -500);
        set("coor/y", 520);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

// Room: /lingzhou/dongmen.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "靈州東門");
        set("long", @LONG
這是東城門，城門正上方刻著幾個西夏文字。城牆上貼著幾張官府
告示。一條路往東北通向城外一片鬆林。
LONG );
        set("exits", ([
                "west"      : __DIR__"dongdajie",
                "northeast" : __DIR__"luorilin1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6255);
        set("coor/y", 2915);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
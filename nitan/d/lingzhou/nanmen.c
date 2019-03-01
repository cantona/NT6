// Room: /lingzhou/nanmen.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "靈州南門");
        set("long", @LONG
這是南城門，城門正上方刻得有幾個西夏文字。城牆上貼著幾張官
府告示。一條大路往南通向黃羊灘。
LONG );
        set("exits", ([
                "south" : __DIR__"huangyangtan",
                "north" : __DIR__"nandajie",
        ]));
        set("objects", ([
                __DIR__"npc/xiaowei" : 1,
                __DIR__"npc/xixiabing" : 2,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "lingzhou");
        set("coor/x", -6285);
        set("coor/y", 2915);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

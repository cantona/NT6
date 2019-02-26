// Room: /lingzhou/yipinjieyin.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "接引堂");
        set("long", @LONG
這裏是西夏一品堂的接引堂，每個自願加入一品堂的江湖高手，都
需有人充當接引人，查清底細，方能入堂。入堂以後，才有資格由赫連
主管分派任務，為一品堂效力。好在這裏有個專職接引的漢子，為一品
堂廣開賢路，所以一品堂在江湖中也確實聲名雀起。
LONG );
        set("exits", ([
                "west"  : __DIR__"yipindayuan",
        ]));
        set("objects", ([
                __DIR__"npc/nuerhai" :1,
        ]));
        set("coor/x", -6295);
        set("coor/y", 2955);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
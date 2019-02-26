// Room: /huanghe/huanghe6.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃河岸邊");
        set("long", @LONG
這裏是黃河岸邊。黃河流淌到這裏，河牀寬闊。黃色的河水在靜靜
地向東流去，使人忘記它發洪水時的狂威。
LONG );
        set("exits", ([
                "northeast" : __DIR__"huanghe7",
                "southwest" : __DIR__"huanghe5",
        ]));
        set("objects", ([
                __DIR__"npc/zu" : 1,
        ]));
        set("outdoors", "huanghe");
        set("coor/x", 300);
        set("coor/y", 800);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
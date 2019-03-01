// Room: /huanghe/huanghe5.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃河岸邊");
        set("long", @LONG
這裡是黃河岸邊。黃河流淌到這裡，河床寬闊。黃色的河水在靜靜
地向東流去，使人忘記它發洪水時的狂威。
LONG );
        set("exits", ([
                "east"      : "/d/taishan/daizong",
                "northeast" : __DIR__"huanghe6",
                "southwest" : __DIR__"huanghe4",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", 150);
        set("coor/y", 530);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
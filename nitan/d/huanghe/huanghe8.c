// Room: /huanghe/huanghe8.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃河入海口");
        set("long", @LONG
黃河流經青藏高原、黃土高原、華北平原，總長一萬零九百里，
在這裏匯入大海。
LONG );
        set("exits", ([
                "southwest" : __DIR__"huanghe7",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", 800);
        set("coor/y", 1200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
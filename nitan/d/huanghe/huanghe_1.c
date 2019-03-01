// Room: /huanghe/huanghe_1.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃河");
        set("long", @LONG
黃河沿蒙古高原南邊向東流淌，遇太行山脈的阻攔，便轉頭南下，
形成晉陝的分界。東北方向好象有個渡口。
LONG );
        set("exits", ([
                "south"     : __DIR__"weifen",
                "west"      : __DIR__"hetao",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -1000);
        set("coor/y", 800);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
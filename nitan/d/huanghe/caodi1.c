// Room: /huanghe/caodi1.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "草地");
        set("long", @LONG
這裏是一片綠茵茵的草地，像是一方綠色的毯子鋪在地上。草叢中
開着一些不知名的小花，有紅的、黃的，還有紫的。花瓣上、草葉上的
露珠閃着晶瑩的光。
LONG );
        set("exits", ([
                "east" : "/d/city/beimen",
                "west" : __DIR__"caodi2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -100);
        set("coor/y", 100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

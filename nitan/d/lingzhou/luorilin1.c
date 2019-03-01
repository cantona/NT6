// Room: /lingzhou/luorilin1.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "落日林");
        set("long", @LONG
落日林位于靈州的東北，在西夏王陵和靈州的中間，延綿百裡，多
長的是紅鬆。
LONG );
        set("exits", ([
                "north"     : __DIR__"dalu",
                "southwest" : __DIR__"dongmen",
        ]));
        set("objects", ([ 
                CLASS_D("xuanming") + "/bai" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6245);
        set("coor/y", 2925);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
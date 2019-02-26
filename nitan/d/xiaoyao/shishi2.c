// shishi2.c
// Modified by Winder June.25 2000

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "石室");
        set("long", @LONG
這是一個石頭砌成的房間，因為好久沒有人來過，散發着一些很難
聞的氣味，房間中到處可以看到蛛絲和蟲跡。
LONG );
        set("exits", ([
                "north" : __DIR__"shiji3",
                "west" : __DIR__"shiji2",
        ]));
        create_door("north", "石門", "south", DOOR_CLOSED);
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", -21040);
        set("coor/z", -40);
        setup();
}

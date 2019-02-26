#include <room.h>
inherit ROOM;

void create()
{
        set("short", "後山小院");
        set("long", @LONG
這裏是武當後山的一座小院，佈置簡簡單單，僅除了一牀一桌、
一椅、一蒲團，再也沒有別的什物。比較引人注目的是牆上掛着一把
劍。這裏就是武當開山祖師張三丰的練功所在。
LONG );
        set("exits", ([
                "north" : __DIR__"xiaolu2",
        ]));

        set("objects", ([
                CLASS_D("wudang") + "/zhang" : 1,
        ]));

        create_door("north", "竹門", "south", DOOR_CLOSED);
        set("coor/x", -370);
        set("coor/y", -340);
        set("coor/z", 90);
        setup();
        // (CLASS_D("wudang") + "/zhang")->come_here();
}
// Room: /lingzhou/caodi1.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "衙門");
        set("long", @LONG
這是靈州府衙所在地，黑色大門平時緊緊閉着，門前四個身着皂服
的衙役沒精打采的拄着水火棍站着。邊上有個大鼓。
LONG );
        set("exits", ([
                "south" : __DIR__"dongdajie",
        ]));
        set("objects", ([
                "/d/city/npc/yayi" : 4,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6255);
        set("coor/y", 2925);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
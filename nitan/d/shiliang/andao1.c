// Feb. 6, 1999 by Winder
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "暗道");
        set("long", @LONG
這是溫家下面一條很隱秘的暗道，也不知道是誰修建的。 
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"andao2",
                "up"    : __DIR__"xiaoting",
        ]));
        set("coor/x", 1620);
        set("coor/y", -1770);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}
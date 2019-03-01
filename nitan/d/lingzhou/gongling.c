// Room: /lingzhou/deling.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "恭陵");
        set("long", @LONG
這是西夏先主拓跋思恭的陵墓，拓跋思恭當年率党項羌族歸順唐太
宗李世民而被賜姓為李，這李思恭在唐初也是極有名的大將。如今因為
年代久遠他的陵墓也不復當年的雄偉而看上去有點破敗。
LONG );
        set("exits", ([
                "south"   : __DIR__"deling",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6235);
        set("coor/y", 3015);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}
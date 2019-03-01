// Room: /lingzhou/dawu.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "林中大屋");
        set("long", @LONG
這是一幢原木制成的三層高大建築，看上去已有些年月但仍堅固異
常，底層是由數根巨木架空，一座木梯通向二樓，三樓的樓頂上掛著一
面繡著一條青龍的大旗，看上去已破舊不堪。人們只知道主人姓李。
LONG );
        set("exits", ([
                "out"     : __DIR__"kongdi",
        ]));
        set("objects", ([
                __DIR__"npc/ye" : 1,
        ]));
        set("coor/x", -6235);
        set("coor/y", 2975);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
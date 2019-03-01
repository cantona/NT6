// houtang2.c 後堂二進
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "後堂二進");
        set("long", @LONG
這裏是全真教弟子平常研討武功的地方，這個堂不大，由於經常
要在這裏演武，索性連桌椅也全都靠到牆邊去了，這樣騰出了一大片
空地來。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"houtang3",
                "west" : __DIR__"houtang1",
                "south" : __DIR__"wuchang1",
                "north" : __DIR__"liangong",
        ]));

        set("coor/x", -2750);
        set("coor/y", 110);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}
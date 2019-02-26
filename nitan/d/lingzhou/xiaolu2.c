// Room: /lingzhou/xiaolu2.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "林中小路");
        set("long", @LONG
這是陡坡上的一條雜草叢生的羊腸小路，看起來平時沒什麼人跡，
路邊開着不知名的野花，兩邊的松樹依然高大、挺拔。陽光透下來照
的你身上是斑斑駁駁的影子。
LONG );
        set("exits", ([
                "south"  : __DIR__"xiaolu1",
                "west"   : __DIR__"xiaolu3",
                "east"   : __DIR__"baxian",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6235);
        set("coor/y", 2965);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
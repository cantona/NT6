#include <room.h>
inherit ROOM;

void create()
{
        set("short", "虎坊路");
        set("long", @LONG
這裡是京城的虎坊路，它西接凡陛橋。只要你身上有兩錢兒，在
這裡就會受到熱情的招呼。任何你不知道的事，在這裡打聽一下，都
可以知道個八九不離十。南邊有一家小小的面館，從裡面傳來一陣轟
鬧聲。
LONG );
        set("exits", ([
                "south" : "/d/beijing/mianguan",
                "east" : "/d/beijing/fu_2",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
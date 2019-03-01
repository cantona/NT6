#include <room.h>
inherit ROOM;

void create()
{
        set("short", "虎坊路");
        set("long", @LONG
這裡是京城的虎坊路，它西接凡陛橋。只要你身上有兩錢兒，在
這裡就會受到熱情的招呼。任何你不知道的事，在這裡打聽一下，都
可以知道個八九不離十。北邊鄰街處有一家不大的客棧。南邊是一座
巨大的宅院，像是某個達官貴人居住的場所。
LONG );
        set("exits", ([
                "south" : "/d/beijing/hai_men",
                "north" : "/d/beijing/fukedian",
                "east" : "/d/beijing/tianqiao",
                "west" : "/d/beijing/fu_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/haoke1" : 1,
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
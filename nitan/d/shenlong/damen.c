// damen.c

#include <ansi.h>

inherit ROOM;

string* npcs = ({
	__DIR__"npc/boy",
	__DIR__"npc/boy2",
	__DIR__"npc/boy3",
	__DIR__"npc/boy4",
	__DIR__"npc/girl",
	__DIR__"npc/boy",
	__DIR__"npc/boy2",
	__DIR__"npc/boy3",
	__DIR__"npc/boy4",
	__DIR__"npc/girl",
	__DIR__"npc/girl",
});

void create()
{
    set("short", "大門");
    set("long", @LONG
這是間很大的竹屋。門外站着幾個年輕弟子.再住北就是神龍教大
廳，隔得雖遠，卻也可以聽得到廳上眾人齊聲念頌之聲。
LONG
    );

    set("exits", ([
		"south" : __DIR__"road2",
		"north" : __DIR__"dating",
    ]));
    set("objects", ([
		npcs[random(sizeof(npcs))] : 1,
		npcs[random(sizeof(npcs))] : 1,
		npcs[random(sizeof(npcs))] : 1,
		npcs[random(sizeof(npcs))] : 1,
		npcs[random(sizeof(npcs))] : 1,
    ]));
    set("outdoors", "shenlong");
    setup();
    replace_program(ROOM); 
}

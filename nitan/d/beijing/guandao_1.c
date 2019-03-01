#include <room.h>
inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
你走在一條塵土飛揚的大官道上。不時有兩三騎快馬從身邊飛馳
而過，揚起一路塵埃。道路兩旁是整整齊齊的楊樹林。
LONG );
       set("exits", ([
                "east" : "/d/beijing/shi_2",
                "north" : "/d/beijing/guandao_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
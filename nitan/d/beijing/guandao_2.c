#include <room.h>
inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
你走在一條塵土飛揚的大官道上。不時有兩三騎快馬從身邊飛馳
而過，揚起一路塵埃。道路兩旁是整整齊齊的楊樹林。北方不遠處就
是京城著名的名勝十三皇陵。
LONG );
       set("exits", ([
                "north" : "/d/beijing/huangling",
                "south" : "/d/beijing/guandao_1",
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
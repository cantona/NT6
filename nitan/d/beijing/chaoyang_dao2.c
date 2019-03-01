#include <room.h>
inherit ROOM;

void create()
{
        set("short", "朝陽道");
        set("long", @LONG
你走在塵土飛揚的朝陽道上，道路兩旁是整整齊齊的楊樹林，不
時有兩三騎快馬從身邊飛馳而過，揚起一路塵埃。東邊就是朝陽門了，
西邊不遠處是繁華的王府井大街，人聲鼎沸，十分熱鬧。
LONG );
       set("exits", ([
                "west" : "/d/beijing/chaoyang_dao1",
                "east" : "/d/beijing/chaoyangmen",
        ]));
        set("objects", ([
                "/kungfu/class/hu/pingsi" : 1,
                "/d/beijing/npc/tiaofu" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2750);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
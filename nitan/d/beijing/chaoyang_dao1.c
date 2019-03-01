#include <room.h>
inherit ROOM;

void create()
{
        set("short", "朝陽道");
        set("long", @LONG
你走在塵土飛揚的朝陽道上，道路兩旁是整整齊齊的楊樹林，不
時有兩三騎快馬從身邊飛馳而過，揚起一路塵埃。東邊不遠處就是朝
陽門了，西邊是繁華的王府井大街，人聲鼎沸，十分熱鬧。
LONG );
       set("exits", ([
                "west" : "/d/beijing/wang_4",
                "east" : "/d/beijing/chaoyang_dao2",
        ]));
        set("objects", ([
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2760);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
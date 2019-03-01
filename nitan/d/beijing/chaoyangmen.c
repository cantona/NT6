#include <room.h>
inherit ROOM;

void create()
{
        set("short", "朝陽門");
        set("long", @LONG
這裡就是京城的朝陽門了，城牆上刻著『朝陽門』三個大字。向
西可以通往京城最熱鬧王府井大街。這裡人來車往，是進出京城的要
道，城門兩旁站滿了官兵，盤查十分嚴密。一條寬闊的大道沿著東西
走向延伸，從這裡出城到達京城的東郊。
LONG );
       set("exits", ([
              "east" : "/d/beijing/road1",
                "west" : "/d/beijing/chaoyang_dao2",
                "south" : __DIR__"matou",
        ]));

        set("objects", ([
                "/d/beijing/npc/ducha" : 1,
                "/d/beijing/npc/bing1" : 2,
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7610);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
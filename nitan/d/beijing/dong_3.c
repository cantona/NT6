#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地東大街");
        set("long", @LONG
這裡是北京城地安門的東街。街道是整整齊齊的楊樹林，道上行
人絡繹不絕，車輛馬匹穿插其中。大街上有閒逛的遊人，上京趕考的
考生，背負著擔子的挑夫以及正在玩耍著的幼童構出了一幅繁忙熱鬧
的盛世景象。北邊是文廟。南邊是寬闊的王府井大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wenmiao",
                "south" : "/d/beijing/wang_9",
                "west" : "/d/beijing/dong_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
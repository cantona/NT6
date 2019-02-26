#include <room.h>
inherit ROOM;

void create()
{
        set("short", "康府走廊");
        set("long", @LONG
這是一條木製的走廊，地面很是光滑，被打整得一塵不染。幾個
康府的下人在此走動。南邊是康府的大廳，左右兩側是兩個廂房。北
邊是康親王的書房所在。這裏站着一個禿頭和尚，那是康府的侍衞頭
領。
LONG );
       set("exits", ([
                "north" : "/d/beijing/kangfu_shufang",
                "south" : "/d/beijing/kangfu_dating",
                "west" : "/d/beijing/kangfu_xifang",
                "east" : "/d/beijing/kangfu_dongfang",
        ]));
        set("objects", ([
                "/d/beijing/npc/jiading_k" : 1,
                "/d/beijing/npc/yahuan_k" : 1,
                "/d/beijing/npc/shenzhao" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青木堂");
        set("long", @LONG
這裏是一間看似很普通的民居，不過卻要比通常的民居大了數倍。
房間中坐着一個乾瘦老頭。房間的南邊又是一道門。
LONG );
       set("exits", ([
                "south" : "/d/beijing/qingmu_dating",
                "west" : "/d/beijing/qingmu_dayuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/xutianchuan" : 1
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
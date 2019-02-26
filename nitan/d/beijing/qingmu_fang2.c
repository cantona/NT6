#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青木堂");
        set("long", @LONG
這裏是一間看似很普通的民居，不過卻要比通常的民居大了數倍。
房間正中一張長桌，天地會的青木堂的羣豪圍桌而坐，大聲喧談。
LONG );
       set("exits", ([
                "north" : "/d/beijing/qingmu_dayuan",
        ]));
        set("objects", ([
                 "/d/beijing/npc/guananji" : 1,
                 "/d/beijing/npc/qianlaoben" : 1,
                 "/d/beijing/npc/jialaoliu" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7610);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青木堂");
        set("long", @LONG
這裡是一間看似很普通的民居，不過卻要比通常的民居大了數倍。
房間正中一張長桌，天地會的青木堂的群豪圍桌而坐，大聲喧談。
LONG );
        set("exits", ([
                "east" : "/d/beijing/qingmu_dayuan",
        ]));

        set("objects", ([
                "/d/beijing/npc/qibiaoqing" : 1,
                "/d/beijing/npc/fangang" : 1,
                "/d/beijing/npc/fengjizhong" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
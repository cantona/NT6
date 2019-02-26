#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "西城門");
        set("long", @LONG
這裏是京城的西城門，厚實堅固的古城牆高高聳立着。城門兩旁
整齊的站着幾個衞兵，仔細的監守着這裏。每天都有許多人經過這裏
出入京城。出了西城門，一條筆直的大官道向東西兩邊延伸。西邊的
官道上人來車往，塵土飛揚。東方則是通往京城的西單北大街。
LONG );
        set("exits", ([
                "east" : "/d/beijing/ximenkou",
                "west" : "/d/beijing/ximenwai",
        ]));
        set("objects", ([
                "/d/beijing/npc/ducha" : 1,
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2850);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
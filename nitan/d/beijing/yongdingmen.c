#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "永定門");
        set("long", @LONG
這裡是是紫禁城永定門，高大的城門正上方刻著『永定門』三個
大字，厚實堅固的古城牆高高聳立著。城門兩旁整齊的站著幾個衛兵，
仔細的監守著這裡。每天都有許多人經過這裡出入京城。出了永定門，
一條筆直的大官道向南北兩邊延伸。南邊的官道上人來車往，塵土飛
揚。北方則是通往京城的中心。
LONG );
        set("exits", ([
                "north" : "/d/beijing/yongdingdao",
                "south" : "/d/beijing/road5",
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
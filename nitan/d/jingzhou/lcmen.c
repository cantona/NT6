#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "糧倉大門");
        set("long", @LONG
你正站在荊州糧倉的門口，可以看到兩個穿着制服的官兵正在此
地巡邏，不時地傳來吶喊聲。老百姓是不允許在此觀看的，你最好趕
快走開。
LONG );
        set("exits", ([
                "west" : __DIR__"nandajie2",
                "east" : __DIR__"liangcang",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 2,
        ]));

        set("coor/x", -7090);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "east" &&
           objectp(present("guan bing", environment(me))))
                return notify_fail(CYN "官兵一把攔住你，罵道：糧倉重地，豈是你們這些"
                                   "泥腿子隨便來得的？\n" NOR);                
        return ::valid_leave(me, dir);
}
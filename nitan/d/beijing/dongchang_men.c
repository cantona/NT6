inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",RED"東廠大門"NOR);
        set("long", @LONG
這裡就是京城的特務機構──東廠的大門。這裡警備深嚴，不時
有穿著制服的東廠官兵進進出出，望大門裡望去，可以望見大門裡面
有許多太監。大門兩旁的東廠官兵正如狼似虎的盯著你看，如果你不
想找死的話，最好還是趕快離開的好。[2；37；0m
LONG );
        set("exits", ([
                "south" : "/d/beijing/dongchang",
                "north" : "/d/beijing/dong_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing2" : 2,
                "/d/beijing/npc/taijian" : 1,
        ]));
        set("no_fight", 0);
	set("coor/x", -2790);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("guan bing", environment(me))) && dir == "south")
                return notify_fail("東廠官兵伸手將你攔住。\n\n");
        return ::valid_leave(me, dir);
}
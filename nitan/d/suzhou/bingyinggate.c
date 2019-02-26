// Room: /d/suzhou/bingyinggate.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "兵營大門");
        set("long", @LONG
你正站在兵營的門口，面對着一排簡陋的營房，可以看到穿着制服
的官兵正在操練，不時地傳來吶喊聲。老百姓是不允許在此觀看的，你
最好趕快走開。
LONG
        );
        set("outdoors","suzhou");
        set("exits", ([
                "south" : __DIR__"bingying",
                "north" : __DIR__"xidajie1",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", 1100);
	set("coor/y", -1070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if (!wizardp(me) && objectp(present("guan bing", environment(me))) && 
                dir == "south")
                return notify_fail("官兵攔住了你的去路。\n");
        return ::valid_leave(me, dir);
}
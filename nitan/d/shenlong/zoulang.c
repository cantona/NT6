#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是一條走廊，兩邊都是石頭柱子。西邊是大廳，東邊是廚房，
南面是一片廣闊的練武場，北面則是休息室。
LONG );

        set("exits", ([
	        "east" : __DIR__"chufang",
	        "west" : __DIR__"dating",
	        "south" : __DIR__"wuchang",
	        "north" : __DIR__"xiuxishi",
        ]));
        set("objects", ([
	        CLASS_D("shenlong")+"/zhang" : 1,
        ]));
        set("outdoors", "shenlong");
        setup();
}

int valid_leave(object me, string dir)
{
        object guarder;

	if (dir == "west" )
                return 1;

        if (objectp(guarder = present("zhang danyue", this_object())))
                return guarder->permit_pass(me, dir);

        return 1;
}

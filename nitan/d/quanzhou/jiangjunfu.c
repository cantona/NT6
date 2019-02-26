// Room: /d/quanzhou/jiangjunfu.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "施琅將軍府");
        set("long", @LONG
這是一座氣勢恢宏的大宅院，琉璃瓦頂，飛檐斗拱，風格迥異。大
紅的正門上方掛着一塊橫匾，上書四個金光閃閃的「靖海侯府」，乃是
皇上所敕之宅，以彰施琅將軍攻破台灣的功績。
LONG );
        set("exits", ([
                "west"  : __DIR__"daxixiang",
                "north" : __DIR__"jiangjunfu1",
                "south" : __DIR__"guitangxiang",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", -880);
	set("coor/y", -7680);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && objectp(present("wu jiang", environment(me))))
                return notify_fail("武將大喝道：將軍有令，閒雜人等迴避！\n");
        return ::valid_leave(me, dir);
}
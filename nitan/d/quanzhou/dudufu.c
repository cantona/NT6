// Room: /d/quanzhou/dudufu.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "都督府");
        set("long", @LONG
這是泉州都督的府邸。泉州都督掌管泉州的海陸兵權，控制着西洋
廣大海域，管轄當世最強大的遠洋水師，乃一等一重要的官職。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "west"  : __DIR__"duduxiang",
                "south" : __DIR__"micangxiang",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", -880);
	set("coor/y", -7640);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "south" && objectp(present("wu jiang", environment(me))))
                return notify_fail("武將大喝道：都督有令，閒雜人等不能由此經過！\n");
        return ::valid_leave(me, dir);
}
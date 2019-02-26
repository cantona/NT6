// Room: /d/quanzhou/liangcang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "糧倉");
        set("long", @LONG
糧倉是所佔地寬廣的庫房，堆放着堆積如山的軍糧，逢到旱澇災年
也做濟災之用。由於倉廣人少，經常引起匪徒的窺視。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "northeast" : __DIR__"micangxiang",
                "south"     : __DIR__"eastroad1",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", -890);
	set("coor/y", -7660);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "northeast" && objectp(present("wu jiang", environment(me))))
                return notify_fail("武將大喝道：都督有令，閒雜人等不能由此經過！\n");
        return ::valid_leave(me, dir);
}
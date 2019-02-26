// Room: /d/quanzhou/shunjiqiao.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "順濟橋");
        set("long", @LONG
這是橫跨晉河的一座石拱橋。橋寬水深，水陸交通便捷，是南去的
唯一出口。一隊官兵駐紮在這裏。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "south"     : __DIR__"portroad3",
                "north"     : __DIR__"huajiaoting",
                "southeast" : __DIR__"shibosi",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", -900);
	set("coor/y", -7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
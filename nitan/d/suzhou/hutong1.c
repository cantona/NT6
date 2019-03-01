// Room: /d/suzhou/hutong1.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "胡同");
        set("long", @LONG
這是一條黑暗、骯臟的小巷，空氣中仿佛飄揚著一股罪惡的氣息，
東北邊通向小巷深處，正人君子當然是不會往那邊走去的。往南走就會
回到城中大路了。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"dongdajie1",
                "northeast" : __DIR__"hutong2",
        ]));
        set("objects", ([
                "/d/city/npc/liumang" : 2,
        ]));
	set("coor/x", 1120);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
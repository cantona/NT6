// Room: /d/suzhou/gumujiaohe.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "古木交訶");
        set("long", @LONG
古木交訶在荷花廳的西面，一排不同圖案的漏窗，使你透過漏窗隱
隱看到中部的水光山色和高低錯落的樓閣，此處賞景，有“移步幻影”
之妙。穿過西窗孔望去，可以遙望綠蔭軒、明瑟樓，給人一種“庭院深
深深幾許”和空間不盡之感。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"hehuating",
                "southwest" : __DIR__"chitang",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
	set("coor/x", 1080);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
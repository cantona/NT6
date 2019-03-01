// Room: /d/xiangyang/westroad2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "西內大街");
        set("long", @LONG
這是一條青石舖就的大街。北面是十字街口。隱隱地能望見南面
是一座很高的彩樓，東面是一堵蓋著紅色琉璃瓦的高牆，裡面是郭府
大院。西面是襄陽城內新開的一家書店，聽說裡面能買到很好的書。
LONG );
        set("outdoors", "xiangyang");

        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"shudian",
                "south" : __DIR__"westroad1",
                "north" : __DIR__"jiekou1",
        ]));
        set("coor/x", -7830);
	set("coor/y", -750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
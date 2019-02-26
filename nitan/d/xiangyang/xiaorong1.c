// Room: /d/xiangyang/xiaorong1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "衚衕");
        set("long", @LONG
這裏是襄陽城內老百姓的居住區。只見小弄兩邊是有些小店面，
有米行、小雜貨鋪等。一些居民從這裏進進出出。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "west" : __DIR__"jiekou2",
                "north" : __DIR__"wjb_damen",
        ]));
        set("objects", ([
                __DIR__"npc/kid" : 2,
                "/clone/npc/walker"  : 1,
        ]));
        set("coor/x", -7780);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
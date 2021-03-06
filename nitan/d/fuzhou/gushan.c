// Room: /d/fuzhou/gushan.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "鼓山");
        set("long", @LONG
鼓山以山上有石形如鼓，扣之如擂鼓而得名，非只山勢如鼓覆地。
山上蒼松滴翠，巖秀谷幽，風景秀麗，四季如春。有晉以來，即為“八
閩二絕”之一。
LONG );
        set("exits", ([
                "north"    : __DIR__"yongquan",
                "westdown" : __DIR__"shulin",
                "southdown": __DIR__"luoxingta",
        ]));
        set("objects", ([
                "/d/wudang/npc/monkey": 1,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -30);
	set("coor/y", -6180);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
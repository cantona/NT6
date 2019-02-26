// Room: /d/taishan/xiangshan.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "象山");
        set("long", @LONG
天街南為象山，俗稱象鼻峯，山南崖奇石下垂似象鼻而名。峯西為
白雲洞，峯東有青雲洞。
LONG );
        set("exits", ([
                "north"    : __DIR__"tianjie",
                "eastdown" : __DIR__"qingyun",
                "westdown" : __DIR__"baiyun",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 40);
	set("coor/y", 290);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}
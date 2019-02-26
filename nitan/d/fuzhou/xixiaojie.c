// Room: /d/fuzhou/ximendajie.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "西小街");
        set("long", @LONG
青石板路筆直地伸展出去，直通西門。街北望去，好一片的瀲灩水
色，街南卻是一片叢林，佛號鍾呤，悠遠傳音。
LONG );
        set("exits", ([
                "west"  : __DIR__"ximen",
                "east"  : __DIR__"xidajie",
                "north" : __DIR__"xihu",
                "south" : __DIR__"xichansi",
        ]));
        set("objects", ([
                __DIR__"npc/cui": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -110);
	set("coor/y", -6180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
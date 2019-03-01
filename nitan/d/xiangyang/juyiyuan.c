// Room: /d/xiangyang/juyiyuan.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "大院");
        set("long", @LONG
這裡是襄陽安撫使按照郭靖、黃蓉的意思建的用來安置各地前來
效力的義士的地方。南面是一條長長的通廊，東西兩邊是練武場。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"juyilianwu1",
                "west"  : __DIR__"juyilianwu2",
                "south" : __DIR__"juyilang",
                "north" : __DIR__"westjie2",
        ]));
        set("objects", ([
                __DIR__"npc/zhuziliu" : 1,
        ]));
        set("coor/x", -7840);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
這是一條寬闊的青石板街道，向東西兩頭延伸。行人絡繹不絕，
北邊是當地有名的關聖廟，東邊有一個熱鬧的廣場。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"xidajie1",
                "west" : __DIR__"jzximen",
                "north" : __DIR__"guanmiao",
                "south" : __DIR__"lydao1",
        ]));
        set("objects", ([
                "/d/beijing/npc/hunhun" : 1,
        ]));
        set("coor/x", -7120);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
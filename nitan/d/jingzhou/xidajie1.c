inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
這是一條寬闊的青石板街道，向東西兩頭延伸。這裡行人稀少，
靜悄悄地很是冷清。東邊是一個熱鬧的廣場。南邊是荊州府衙。北邊
是一座豪華大院，那就是萬門萬府了。
LONG );
        set("outdoors", "jingzhou");

        set("exits", ([
                "east" : __DIR__"guangchang",
                "south" : __DIR__"jzyamen",
                "west" : __DIR__"xidajie2",
                "north" : __DIR__"wan_damen",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
        ]));
        set("coor/x", -7110);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
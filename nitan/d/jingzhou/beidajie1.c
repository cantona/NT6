inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
你走在一條繁忙的街道上，看著操著南腔北調的人們行色匆匆，
許多人都往南邊走去，那裡有一個熱鬧的廣場。東邊是一家生意興隆
的客棧，來自各地的人們進進出出，西邊是一家錢莊，可以聽到叮叮
當當的金銀聲音。
LONG );
        set("outdoors", "jingzhou");

        set("exits", ([
                "east" : __DIR__"kedian",
                "south" : __DIR__"guangchang",
                "west" : __DIR__"qianzhuang",
                "north" : __DIR__"beidajie2",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl1" : 1,
        ]));
        set("coor/x", -7100);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
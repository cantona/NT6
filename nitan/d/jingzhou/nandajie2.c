inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
你走在一條繁華的街道上，向南北兩頭延伸。南邊是南城門，北
邊通往市中心，西邊是一家顧客眾多荊州的兵器庫，東邊是荊州糧倉，
荊州向來是軍事要地，所以兵器糧草屯積豐厚。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"lcmen",
                "south" : __DIR__"jznanmen",
                "west" : __DIR__"bqkumen",
                "north" : __DIR__"nandajie1",
                "westdown" : __DIR__"lydao4",
        ]));
        set("objects", ([
                "/d/beijing/npc/old1" : 1,
                "/d/beijing/npc/boy2" : 1,
        ]));
        set("coor/x", -7100);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "荊州中心" );
        set("long", @LONG
這裏是荊州的中心要十字路口，人來人往，很是熱鬧，南邊住着
一些本城的富人，北邊是官府，真是一個好地方啊。許多從四川來的
人都在此落腳，休息以後再趕路。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "west" : __DIR__"xidajie1",
                "north" : __DIR__"beidajie1",
                "south" : __DIR__"nandajie1",
        ]));
        set("objects", ([
                "/d/beijing/npc/haoke1" : 1,
                "/d/beijing/npc/maiyi1" : 1,
                "/d/beijing/npc/boy1" : 1,
                "/d/beijing/npc/old2" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -7100);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
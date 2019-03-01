inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
你走在一條小路上。前面道路崎嶇，行人很少。前方隱約有房屋
可見。
LONG );
        set("exits", ([
                "south" : "/d/beijing/zhuang1",
                "north" : "/d/beijing/zhuang3",
        ]));
        set("objects", ([
                "/d/wudang/npc/tufei1" : 1,
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "官道" );
        set("long", @LONG
你走在一條大官道上，兩旁不時有人從你身邊走過，西面通向荊
州，東邊是武昌城的西門。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : "/d/wuchang/ximen",
                  "west" : __DIR__"guandao2",
        ]));

        set("no_clean_up", 0);

        set("coor/x", -7040);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
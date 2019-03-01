inherit ROOM;

void create()
{
        set("short", "官道" );
        set("long", @LONG
你走在一條大官道上，兩旁不時有人從你身邊走過，可以分辯出
有幾個是江湖中人。西面隱約可以看見荊州，東邊是通往武昌城。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                  "east" : __DIR__"guandao1",
                  "west" : __DIR__"guandao3",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7050);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
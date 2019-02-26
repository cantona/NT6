inherit ROOM;

void create()
{
        set("short", "藥鋪");
        set("long", @LONG
這是一家藥鋪，一股濃濃的藥味讓你幾欲窒息，那是從藥櫃上的
幾百個小抽屜裏散發出來的。神醫平一指坐在茶几旁獨自喝着茶，看
也不看你一眼。
LONG );
        set("objects", ([
                "/d/city/npc/ping" : 1,
        ]));
        set("no_fight", 1);     
        set("no_sleep_room", 1);
        set("exits", ([
                "east" : __DIR__"road",
        ]));
	set("coor/x", -5060);
	set("coor/y", 2230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
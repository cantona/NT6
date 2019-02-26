// guandao1.c 官道
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
這是一條大道，西面通往武功鎮。道上的行人很多，大多是低
着頭自己趕自己的路。忽然在你的身後響起得得的馬蹄聲，不一會
兒，幾匹駿馬從你身邊飛馳而過，掠起了一片黃沙。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "west" : __DIR__"guandao2",
                "east" : "/d/changan/road3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12210);
	set("coor/y", 810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
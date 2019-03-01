inherit ROOM;

void create()
{
        set("short", "白馬客棧");
        set("long", @LONG
這是洛陽城裡最大的一家客棧，緊靠洛陽中心，以洛陽的名勝白馬寺
來命名，曰“白馬客棧”，由于價格公道，因此到這裡來借宿的客人川流
息，絡繹不絕，生意及其興隆，大堂內擺了七八張桌子，店小二跑來跑去
接待著從四面八方來的客人。二樓上是雅廳，客棧後面是馬廄。
LONG);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"majiu",
                "up" : __DIR__"kezhan2",
                "west" : __DIR__"sroad1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
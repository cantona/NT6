// guandao2.c 官道
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
這是一條官府修建的大道，西面隱約可以看見武功鎮的東門。
遠處好像可以看見巍峨的城牆。往東是通往中原的路。走在這裏，
你似乎有了一種‘勸君更進一杯酒，西出陽關無故人’的感覺。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "east" : __DIR__"guandao1",
                "west" : __DIR__"dongmen",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12220);
	set("coor/y", 810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
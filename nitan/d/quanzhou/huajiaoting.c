// Room: /d/quanzhou/huajiaoting.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "花橋亭");
        set("long", @LONG
這是一個建在大路中央的小亭子，三三兩兩的行人在此休息。南去
便是順濟橋，可通往港口。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"shunjiqiao",
                "north" : __DIR__"jishi",
        ]));
	set("coor/x", -900);
	set("coor/y", -7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
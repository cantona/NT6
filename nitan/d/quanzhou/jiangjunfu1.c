// Room: /d/quanzhou/jiangjunfu1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "將軍府書房");
        set("long", @LONG
這是靖海侯府的書房，裡面除了書籍之外，更多的還是各種兵刃。
LONG );
        set("exits", ([
                "south" : __DIR__"jiangjunfu",
        ]));
        set("objects", ([
                __DIR__"npc/shi" : 1,
        ]));
	set("coor/x", -880);
	set("coor/y", -7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
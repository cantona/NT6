// Room: /d/quanzhou/kedian2.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "客店二樓");
        set("long", @LONG
你正走在客店二樓的走廊上，可以聽到從客房裡不時地呼呼的打酣
聲，一陣高過一陣。不時有睡意朦朧的旅客進進出出，到樓下的掌櫃處
付了錢再上來睡覺。
LONG );
        set("exits", ([
                "down"  : __DIR__"kedian",
                "enter" : __DIR__"kedian3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -890);
	set("coor/y", -7660);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
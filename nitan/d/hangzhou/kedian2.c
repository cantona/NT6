// kedian2.c
// Date: Nov.1997 by Venus
inherit ROOM;

void create()
{
        set("short", "天外天客店二樓");
        set("long", @LONG
你正走在天外天客店二樓的走廊上，可以聽到從客房裡不時地呼呼
的打酣聲，一陣高過一陣。不時有睡意朦朧的旅客進進出出，到樓下的
掌櫃處付了錢再上來睡覺。
LONG );
        set("exits", ([
                "down"  : __DIR__"kedian",
                "enter" : __DIR__"kedian3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 840);
	set("coor/y", -2070);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
// Room: /city/kedian2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "客店二樓");
        set("long", @LONG
你正走在客店二樓的走廊上，可以聽到從客房裡不時地呼呼的打
酣聲，一陣高過一陣。不時有睡意朦朧的旅客進進出出，到樓下的掌
櫃處付了錢再上來睡覺。
LONG );
	set("exits", ([
		"down"  : "/d/city/kedian",
		"enter" : "/d/city/kedian3",
	]));

	set("objects", ([
                CLASS_D("shaolin") + "/xingzhe" : 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", 10);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
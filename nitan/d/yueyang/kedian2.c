// Room: /d/yueyang/kedian2.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "牡丹樓二樓");
        set("long", @LONG
你正走在牡丹樓二樓的走廊上，可以聽到從客房裏不時地呼呼的打
酣聲，一陣高過一陣。不時有睡意朦朧的旅客進進出出，到樓下的掌櫃
處付了錢再上來睡覺。
LONG );
        set("exits", ([
                "down"  : __DIR__"kedian",
                "enter" : __DIR__"kedian3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6190);
	set("coor/y", -3020);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
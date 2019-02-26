inherit ROOM;

void create()
{
        set("short", "客店二樓");
        set("long", @LONG
你正走在客店二樓的走廊上，可以聽到從客房裏不時地呼呼的打
酣聲，一陣高過一陣。不時有睡意朦朧的旅客進進出出。到樓下的掌
櫃處付了錢再上來睡覺。
LONG );
        set("exits", ([
                "down" : __DIR__"kedian",
                "enter" : __DIR__"kedian3",
        ]));        
        set("coor/x", -7090);
	set("coor/y", -2040);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
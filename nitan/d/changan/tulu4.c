// Room:/d/changan/tulu4.c

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
這是一條黃土飛揚的路，不算太寬，路上的行人也不多，大概是
地處偏遠的緣故，幾乎沒有什麼人煙。
LONG );
        set("exits",  ([  /*  sizeof()  ==  2  */
                "southwest" : "/d/changan/tulu3",
        ]));
        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 2020);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
// Room:/d/changan/tulu3.c

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
這是一條黃土飛揚的路，不算太寬，路上幾乎沒有行人，四周一
片荒寂。
LONG );
        set("exits",  ([  /*  sizeof()  ==  2  */
                "northeast" : "/d/changan/tulu4",
                "southdown" : "/d/changan/tulu2",
        ]));
        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 2010);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
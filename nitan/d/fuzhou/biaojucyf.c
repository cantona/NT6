// Room: /city/biaojucyf.c

inherit ROOM;

void create()
{
        set("short", "簽押房");
           set("long", @LONG
這裏是福威鏢局簽押房。鏢局和官府交情既深，與江湖上的同道自
也不免也是瓜葛重重。這些局子裏大面上的迎來送往，都由這裏招呼。
LONG
        );
        set("exits", ([
                "east" : __DIR__"biaojudy",
        ]));
        set("objects", ([
                __DIR__"npc/gao" : 1,
        ]));
	set("coor/x", -111);
	set("coor/y", -6171);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}
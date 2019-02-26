inherit ROOM;

void create()
{
        set("short", "汝州城");
        set("long", @LONG
汝州城是本府的大城，立來是兵家必爭之地。故州治在此駐紮重
兵，盤查南來北往的行人，並負責翦滅附近山上的草寇。由於這裏是
去嵩山的必經之道，官兵盤查也十分嚴格。從這裏向東出城門，可以
到五嶽之中的嵩山了。
LONG
        );

        set("exits", ([
                "south" : __DIR__"nandajie",
                "west"  : __DIR__"xidajie",
                "east"  : __DIR__"dongdajie",
                "north" : __DIR__"beidajie",
        ]));

        set("objects", ([
                "/clone/npc/xunbu" : 1,
                "/clone/npc/walker"  : 1,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

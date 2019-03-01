//  Room:  /d/lanzhou/northgate.c

inherit  ROOM;

void  create  ()
{
        set("short",  "北門");
        set("long",  @LONG
這裡便是蘭州北門。由于最近正在加固城牆，因此顯得有些凌亂。
城牆上下堆滿了土石，上百民夫正在勞作。看來不等城牆修建好，城門
是不會開放的了。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"road4",
                "south" : __DIR__"road3",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/city/npc/wujiang": 1,
                "/d/city/npc/bing": 2,
        ]));
        set("outdoors", "lanzhou");
	set("coor/x", -15750);
	set("coor/y", 3840);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
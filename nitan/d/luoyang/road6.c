//  Room:  /d/luoyang/road5.c

inherit  ROOM;

void  create  ()
{
        set("short",  "北郊小路");
        set("long",  @LONG
這是洛陽城郊的一條茅草小路，東北面彷彿是通往渡口的小路，而
南面則是洛陽城門。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "northeast" :  __DIR__"dukou",
                "northup"   :  __DIR__"mangshan",
                "south"     :  __DIR__"road5",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/taishan/npc/tiao-fu" : 1,
        ]));
        set("outdoors", "luoyang");
	set("coor/x", -6990);
	set("coor/y", 2260);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
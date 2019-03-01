//  Room:  /d/lanzhou/road3.c

inherit  ROOM;

void  create  ()
{
        set("short",  "林蔭道");
        set("long",  @LONG
這是一條寬闊的青石板街道，從北門一直向南延伸。兩旁路樹成蔭，
不時有過往行人走過，和剛才城外荒涼的景象形成鮮明對比。南邊是城
內最大的大街------濱河大街。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"northgate",
                "south" : __DIR__"street2",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15750);
	set("coor/y", 3830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
//  Room:  /d/lanzhou/road2.c

inherit  ROOM;

void  create  ()
{
        set("short",  "林蔭道");
        set("long",  @LONG
這是一條寬闊的青石板街道，從南門一直向北延伸。兩旁路樹成蔭，
不時有過往行人走過，和剛才城外荒涼的景象形成鮮明對比。北邊是個
熱鬧的廣場。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south" : __DIR__"southgate",
                "north" : __DIR__"square",
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15750);
	set("coor/y", 3800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
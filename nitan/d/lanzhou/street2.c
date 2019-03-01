//  Room:  /d/lanzhou/street2.c

inherit  ROOM;

void  create  ()
{
        set("short",  "濱河大街");
        set("long",  @LONG
這是蘭州城內最大的一條街，從東門一直延伸到西門。往西可以出
西門繼續向西域進發，向北出北門，經金城古城，便是黃河渡口了。南
邊是城內的城隍廟。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"road3",
                "south" : __DIR__"square",
                "east"  : __DIR__"street1",
                "west"  : __DIR__"street3",
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15750);
	set("coor/y", 3820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
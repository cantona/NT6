//  Room:  /d/lanzhou/market.c

inherit  ROOM;

void  create  ()
{
        set("short",  "集市");
        set("long",  @LONG
熱鬧的集市裡，人來人往，摩肩接踵，不時有人從你身邊擦身而過。
偶爾也能看見幾個江湖豪客在南邊的順風客棧休息、投宿。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south" : __DIR__"kedian",
                "north" : __DIR__"street1",
                "east"  : __DIR__"yangrouguan",
                "west"  : __DIR__"square",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/xiaofan" : 1,
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15740);
	set("coor/y", 3810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
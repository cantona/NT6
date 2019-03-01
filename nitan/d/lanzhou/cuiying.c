//  Room:  /d/lanzhou/cuiying.c

inherit  ROOM;

void  create  ()
{
        set("short",  "翠英門");
        set("long",  @LONG
你走在大街上，踩著堅實的青石板地面。迎面一座牌坊，上書“翠
英門”三個大字，書法龍飛鳳舞，想必為名家所提。雖東邊有廟會，可
這裡卻還是相當幽雅恬靜，南邊不時傳來朗朗書聲。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"street3",
                "south" : __DIR__"zhigong",
                "east"  : __DIR__"square",
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15760);
	set("coor/y", 3810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
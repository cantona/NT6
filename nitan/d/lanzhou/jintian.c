//  Room:  /d/lanzhou/jintian.c

inherit  ROOM;

void  create  ()
{
        set("short",  "金天觀");
        set("long",  @LONG
你走過樹林，發現樹林後一道山門，上書------金天觀。相傳本觀
始建于建文二年，主祀“雷祖”，故又稱雷壇。永樂年間，賜名金天觀。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south" : __DIR__"street3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -15760);
	set("coor/y", 3830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
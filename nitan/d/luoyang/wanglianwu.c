//  Room:  /d/luoyang/wanglianwu.c

inherit  ROOM;

void  create  ()
{
        set("short",  "練武廳");
        set("long",  @LONG
據説，王家威震豫鄂的武功，就是在這個練武廳裏練出來的。可你
看見的也只不過是一個很尋常的屋子而已，唯一突出的，不過是東牆上
掛滿的一壁單刀罷了。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"  :  __DIR__"wanghuating",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -7021);
	set("coor/y", 2139);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}
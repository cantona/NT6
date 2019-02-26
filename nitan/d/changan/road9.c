//  Room:  /d/changan/road9.c

inherit  ROOM;

void  create  ()
{
        set("short",  "官道");
        set("long",  @LONG
一條青石鋪就的官道，向北通往蘭州，往東南則到達長安。道路兩
旁是一片茂密的樹林。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"     :  "/d/lanzhou/caoyuan1",
                "southeast" :  __DIR__"road8",
        ]));
        set("outdoors", "changan");
        set("no_clean_up", 0);
        set("coor/x", -10800);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
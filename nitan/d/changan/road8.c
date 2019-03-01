//  Room:  /d/changan/road8.c

inherit  ROOM;

void  create  ()
{
        set("short",  "官道");
        set("long",  @LONG
一條青石舖就的官道，向西北通往蘭州，往東南則到達長安。道路
兩旁是一片茂密的樹林。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "northwest" :  __DIR__"road9",
                "southeast" :  __DIR__"road7",
        ]));
        set("outdoors", "changan");
        set("no_clean_up", 0);
        set("coor/x", -10790);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
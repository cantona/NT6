//  Room:  /d/lanzhou/road1.c

inherit  ROOM;

void  create  ()
{
        set("short",  "官道");
        set("long",  @LONG
一條青石舖就的官道，向北通往蘭州，往東則到達長安。道路兩旁
是一片茂密的樹林。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"southgate",
                "east"  : __DIR__"caoyuan5",
                "west"  : __DIR__"yizhan",
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15750);
	set("coor/y", 3780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
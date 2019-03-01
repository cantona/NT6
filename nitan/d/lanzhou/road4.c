//  Room:  /d/lanzhou/road4.c

inherit  ROOM;

void  create  ()
{
        set("short",  "官道");
        set("long",  @LONG
一條青石舖就的官道，向南通往蘭州，往北三十裡就是金城。道路
兩旁是一片茂密的樹林。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south" : __DIR__"northgate",
                "north" : __DIR__"jincheng",
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15750);
	set("coor/y", 3850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
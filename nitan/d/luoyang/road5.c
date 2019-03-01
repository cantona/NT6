//  Room:  /d/luoyang/road5.c

inherit  ROOM;

void  create  ()
{
        set("short",  "北郊小路");
        set("long",  @LONG
這是洛陽城郊的一條茅草小路，草叢中時有小獸出沒，小路向北延
伸直達黃河岸邊。往東北通往牡丹園，南面可以遙遙看到洛陽城門。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"     : __DIR__"road6",
                "south"     : __DIR__"nbridge",
                "northeast" : __DIR__"mudan",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6990);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
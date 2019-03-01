//  Room:  /d/changan/road7.c

inherit  ROOM;

void  create  ()
{
        set("short",  "官道");
        set("long",  @LONG
一條青石舖就的官道，向西北通往蘭州，往東則到達長安。道路兩
旁是一片茂密的樹林。西邊是一座廢墟，看起來已經有些年代了。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"      :  __DIR__"apanggong",
                "northwest" :  __DIR__"road8",
                "east"      :  __DIR__"xi-chengmen",
        ]));
        set("outdoors", "changan");
        set("no_clean_up", 0);
        set("coor/x", -10780);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
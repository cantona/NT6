// Room: /d/xiangyang/westjie3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
這是一條寬闊的青石街道，向東西兩頭延伸。西面是白虎內門，
東邊是一個大十字街口，只見人來人往，絡繹不絕。南邊是大校場。
北面是襄陽城的西兵營，隱隱能聽見裡面傳來的宋兵的操練聲。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"westjie2",
                "west"  : __DIR__"westgate1",
                "south" : __DIR__"dajiaochang",
                "north" : __DIR__"bingying4",
        ]));
        set("coor/x", -7850);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
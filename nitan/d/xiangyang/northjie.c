// Room: /d/xiangyang/northjie.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
這是一條寬闊的青石街道，向南北兩頭延伸。北面是玄武內門，
南邊顯得很繁忙。東邊是一茶館，一面上書『茶』的招幡在風中輕輕
地搖曳著，一股股茶香撲面而來。西面是襄陽城的北兵營，隱隱能聽
見裡面傳來的操練聲。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"chaguan",
                "south" : __DIR__"dingzi",
                "west"  : __DIR__"bingying1",
                "north" : __DIR__"northgate1",
        ]));
        set("coor/x", -7810);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
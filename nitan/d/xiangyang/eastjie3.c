// Room: /d/xiangyang/eastjie3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
這是一條寬闊的青石街道，向東西兩頭延伸。東面是青龍內門，
南邊是木匠鋪，鋸木聲、刨木聲聲聲入耳。北面是襄陽城的東兵營，
隱隱能聽見裏面傳來宋兵的操練聲。西邊是一個十字街口，只見人來
人往、絡繹不絕。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"eastgate1",
                "west"  : __DIR__"eastjie2",
                "south" : __DIR__"mujiang",
                "north" : __DIR__"bingying2",
        ]));
        set("coor/x", -7790);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
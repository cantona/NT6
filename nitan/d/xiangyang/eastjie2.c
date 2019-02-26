// Room: /d/xiangyang/eastjie2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
這兒是很大的十字街口，北邊是東內大街，南面是一條街道，聽
説有錢人一般都住在裏面，東面通向襄陽城的青龍門，向西可到達中
央廣場。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"eastjie3",
                "west"  : __DIR__"eastjie1",
                "south" : __DIR__"jiedao",
                "north" : __DIR__"eastroad1",
        ]));
        set("coor/x", -7800);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
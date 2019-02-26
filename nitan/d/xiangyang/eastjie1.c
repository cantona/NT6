// Room: /d/xiangyang/eastjie1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
這是一條寬闊的青石板街道，向東西兩頭延伸。東邊是一個大十
字街口。西面是襄陽的中央廣場，北邊是襄陽守城大將王堅的府邸大
門，只見那兒守備森嚴，閒雜人等一般是不能接近的。南面飄來一縷
縷的藥香，噢，原來是一家藥鋪。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"eastjie2",
                "west"  : __DIR__"guangchang",
                "south" : __DIR__"yaopu",
                "north" : __DIR__"jiangjungate",
        ]));
        set("coor/x", -7810);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
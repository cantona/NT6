// Room: /d/xiangyang/guangchang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "中央廣場");
        set("long", @LONG
這裏是襄陽的中央廣場，鋪着青石地面。東面通向青龍門，西面
通向白虎門，南面直達朱雀門，遠遠地你可看到北面是襄陽安撫使衙
門。近年來蒙古大軍屢次攻打襄陽，官府為防止蒙古奸細混雜進來，
已經不允許人們在此聚集。只見一隊官兵在此往來巡邏，你還是快離
開吧。
LONG );
        set("outdoors", "xiangyang");
        set("item_desc", ([
                "dong" : "\n",
        ]));

        set("exits", ([
                "east"  : __DIR__"eastjie1",
                "west"  : __DIR__"westjie1",
                "south" : __DIR__"southjie1",
                "north" : __DIR__"anfupailou",
        ]));
        set("objects", ([
                __DIR__"npc/pian" : 1,
                __DIR__"npc/bing" : 1,
                "/clone/npc/walker"  : 1, 
        ]));
        set("coor/x", -7820);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
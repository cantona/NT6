// Room: /d/wuxi/northroad1.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
一條典型的江南街道，地面雖然是用小青磚鋪成，但也是十分地平
整。兩邊的店鋪飛檐瓦當，無不透着水鄉的秀氣。大街上操着南腔北調
的人們行色匆匆，南邊就是無錫城的中心廣場。東邊是江南名剎崇安寺，
來自各地的人們進進出出，香火十分旺盛。西邊是一家專售無錫惠山泥
人的店鋪，是來這裏的外地旅客最愛光顧的地方。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "north" : __DIR__"jinlianqiao",
                "south" : __DIR__"guangchang",
                "east"  : __DIR__"chongansi",
                "west"  : __DIR__"nirenpu",
        ]));
        set("objects", ([
                        __DIR__"npc/lady" : 1,
        ]));
        set("coor/x", 1040);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
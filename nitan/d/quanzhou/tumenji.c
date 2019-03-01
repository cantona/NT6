// Room: /d/quanzhou/tumenji.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "塗門集");
        set("long", @LONG
這是泉州南面東西向的一條幹道，規模不大。南邊是泉州著名的鴻
翔綢緞莊。西邊是個集市，東邊便是去往港口的主要通道「塗門水關」。
LONG );
        set("outdoors", "quanzhou");
        set("objects", ([
                "/d/taishan/npc/tangzi": 1,
        ]));
        set("exits", ([
                "east"  : __DIR__"tumenshuiguan",
                "west"  : __DIR__"jishi",
                "south" : __DIR__"road1",
                "north" : __DIR__"qingjingsi",
        ]));
	set("coor/x", -890);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
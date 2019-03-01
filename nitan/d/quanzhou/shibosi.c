// Room: /d/quanzhou/shibosi.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "市舶司");
        set("long", @LONG
這是負責接待海外使節及籌備出海西洋必要手續的地方。門口左右
兩邊各有一個青石獅子，形態矯健，仰天高吼。西北邊通往順濟橋，西
南邊通往港口路，北邊的街道盡頭則是塗門集。
LONG );
        set("exits", ([
                "north"     : __DIR__"road2",
                "southwest" : __DIR__"portroad3",
                "northwest" : __DIR__"shunjiqiao",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", -890);
	set("coor/y", -7750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
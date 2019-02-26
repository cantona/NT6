// Room: /d/quanzhou/portroad2.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "港口路");
        set("long", @LONG
這是用大塊花崗石鋪成的寬敞大道，平坦結實。路上馬車都拉着沉
重的貨物南來北往。不少馬隊都有鏢師保護，看來都是價值不菲的貨物。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "south" : __DIR__"houzhu",
                "north" : __DIR__"portroad1",
        ]));
        set("objects", ([
//                "/d/taishan/npc/tangzi" : 1,
                "/d/taishan/npc/tiao-fu" : 1,
                __DIR__"npc/kuli" : 1,
                __DIR__"npc/langren" : 1,
        ]));
	set("coor/x", -870);
	set("coor/y", -7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
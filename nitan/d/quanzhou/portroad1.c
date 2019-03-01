// Room: /d/quanzhou/portroad1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "港口路");
        set("long", @LONG
這是用大塊花崗石舖成的寬敞大道，平坦結實。路上馬車都拉著沉
重的貨物南來北往。不少馬隊都有鏢師保護，看來都是價值不菲的貨物。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "south" : __DIR__"portroad2",
                "north" : __DIR__"lingshan",
        ]));
/*
        set("objects", ([
                "/d/fuzhou/npc/biaotou" : 1,
        ]));
*/
	set("coor/x", -870);
	set("coor/y", -7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
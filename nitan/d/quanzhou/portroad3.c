// Room: /d/quanzhou/portroad3.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "港口路");
        set("long", @LONG
這是用大塊花崗石舖成的寬敞大道，平坦結實。路上馬車都拉著沉
重的貨物南來北往。不少馬隊都有鏢師保護，看來都是價值不菲的貨物。
東北邊是海外交通使節府，北邊接著順濟橋。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "northeast" : __DIR__"shibosi",
                "southeast" : __DIR__"portroad4",
                "north"     : __DIR__"shunjiqiao",
        ]));
        set("objects", ([
                "/d/taishan/npc/tangzi" : 2,
                //"/d/fuzhou/npc/biaotou" : 1,
        ]));
	set("coor/x", -900);
	set("coor/y", -7750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
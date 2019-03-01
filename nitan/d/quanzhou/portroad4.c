// Room: /d/quanzhou/portroad4.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "港口路");
        set("long", @LONG
這是用大塊花崗石舖成的寬敞大道，平坦結實。路上馬車都拉著沉
重的貨物南來北往。不少馬隊都有鏢師保護，看來都是價值不菲的貨物。
南邊是安海港，東邊是船塢，東南邊則是永寧港。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "east"      : __DIR__"chuanwu",
                "south"     : __DIR__"anhaigang",
                "northwest" : __DIR__"portroad3",
                "southeast" : __DIR__"yongninggang",
        ]));
        set("objects", ([
                "/d/taishan/npc/tangzi" : 1,
                __DIR__"npc/kuli" : 2,
        ]));
	set("coor/x", -890);
	set("coor/y", -7760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
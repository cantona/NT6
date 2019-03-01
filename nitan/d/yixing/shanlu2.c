// Room: /yixing/shanlu2.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裡是一片農田。不遠處有一些村莊，炊煙裊裊升起。村莊周圍是
一塊塊的田地，田裡有一些正在耕作的農人。
LONG );
        set("outdoors", "yixing");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"shanlu1",
                "southeast" : "/d/wuxi/road17",
        ]));
        set("objects", ([
//                __DIR__"npc/qiuqianzhang" : 1,
        ]));
        set("coor/x", 290);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
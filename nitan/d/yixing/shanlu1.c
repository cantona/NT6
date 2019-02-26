// Room: /yixing/shanlu1.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裏是一片農田。不遠處有一些村莊，炊煙裊裊升起。村莊周圍是
一塊塊的田地，田裏有一些正在耕作的農人。
LONG );
        set("outdoors", "yixing");
        set("exits", ([
                "north"     : __DIR__"shulin4",
                "south"     : __DIR__"taihu",
                "northeast" : __DIR__"shanlu2",
        ]));
        set("objects", ([
                "/d/village/npc/poorman" : 1,
        ]));
        set("coor/x", 280);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
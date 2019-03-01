// Room: /d/quanzhou/shanlu1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是清源山區的碎石小徑，曲折蜿蜒，兩旁林木茂盛，遮天蔽日。
滿徑落葉，柔軟稀鬆。蟲鳥啾啾。涼風習習。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "southup"   : __DIR__"qingyuandong",
                "northdown" : __DIR__"anpingqiao",
        ]));
        set("objects", ([
                __DIR__"npc/banjiu" : 1,
        ]));
	set("coor/x", -910);
	set("coor/y", -7510);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
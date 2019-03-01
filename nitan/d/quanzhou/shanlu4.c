// Room: /d/quanzhou/shanlu4.c
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
                "southup" : __DIR__"cienyan",
                "northup" : __DIR__"wangzhouting",
        ]));
        set("objects", ([
                "/d/wudang/npc/yetu" : 1,
        ]));
	set("coor/x", -900);
	set("coor/y", -7590);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
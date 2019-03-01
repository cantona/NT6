// Room: /d/quanzhou/shanlu3.c
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
                "southup" : __DIR__"ruixiangyan",
                "northup" : __DIR__"shanlu2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -900);
	set("coor/y", -7560);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}
// Room: /d/quanzhou/jishitang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "濟世堂老店");
        set("long", @LONG
這是間老字號的中藥鋪，屋裏瀰漫着濃厚的藥味。正前方有一個紅
漆櫃枱，櫃枱後是一個碩大無比的藥櫃，幾乎蓋住了整堵牆，櫃子上有
無數的盛藥的小抽屜，每個抽屜均標了小字，註明藥物名稱。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east"    : __DIR__"yaofang",
                "enter"   : __DIR__"neitang",
                "north"   : __DIR__"westroad2",
        ]));
        set("objects", ([
                __DIR__"npc/wang" : 1,
        ]));
	set("coor/x", -920);
	set("coor/y", -7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
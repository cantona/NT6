// Room: /d/quanzhou/yaofang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "藥房");
        set("long", @LONG
這裏是濟世堂配藥煉藥的地方，屋子正中放了一隻煉藥用的藥臼，
一個小廝正不停的加藥、鼓火、添水，爐中不停的冒出騰騰水霧，並散
發着濃濃的藥氣。
LONG );
        set("exits", ([
                "west" : __DIR__"jishitang",
        ]));
        set("objects", ([
                "/clone/misc/yaojiu" : 1,
                __DIR__"npc/xiaosi" : 1,
        ]));
	set("coor/x", -910);
	set("coor/y", -7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
// Room: /d/suzhou/zhenshi.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "枕石");
        set("long", @LONG
在山半腰有一塊巨石，因石形如枕而得名枕石。相傳東晉高僧，常
在此倚石閲經，倦則枕石休息。此石其形又象蜒蚰，故亦稱“蜒蚰石”。
另因有“唐寅三笑姻緣”的傳説，故又名“鴛鴦石”。這塊大石，實系
海湧山遺物。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"shijianshi",
        ]));
        set("objects", ([
                "/d/taishan/npc/seng-ren" : 1,
        ]));
	set("coor/x", 1100);
	set("coor/y", -1020);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
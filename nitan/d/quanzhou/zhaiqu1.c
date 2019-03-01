// Room: /d/quanzhou/zhaiqu1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "宅區");
        set("long", @LONG
這是泉州居民區。區內小巷縱橫，四通八達。一式的石砌矮屋，紅
頂青牆，方正對稱，極具閩南特色，可謂錯致落有，小巧玲瓏。西邊是
間戲院，南邊也是一大片宅區。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"southroad1",
                "west"  : __DIR__"xiyuan",
                "south" : __DIR__"zhaiqu2",
        ]));
        set("objects", ([
                "/d/village/npc/boy" : random(3),
        ]));
	set("coor/x", -910);
	set("coor/y", -7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
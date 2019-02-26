// Room: /d/quanzhou/zhaiqu3.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "宅區");
        set("long", @LONG
這是泉州居民區。區內小巷縱橫，四通八達。一式的石砌矮屋，紅
頂青牆，方正對稱，極具閩南特色，可謂錯致落有，小巧玲瓏。東邊的
刺桐南路傳來繁鬧的喧譁聲。西邊有家出名的蜜餞製作鋪「源和堂」。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"southroad2",
                "west"  : __DIR__"yuanhetang",
                "north" : __DIR__"zhaiqu2",
        ]));
        set("objects", ([
                "/d/village/npc/girl" : random(3),
        ]));
	set("coor/x", -910);
	set("coor/y", -7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
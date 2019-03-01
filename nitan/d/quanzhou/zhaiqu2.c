// Room: /d/quanzhou/zhaiqu2.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "宅區");
        set("long", @LONG
這是泉州居民區。區內小巷縱橫，四通八達。一式的石砌矮屋，紅
頂青牆，方正對稱，極具閩南特色，可謂錯致落有，小巧玲瓏。北邊和
南邊都是宅區。西邊則是泉州最大的「揚威武館」。西南可通至源和堂。
間戲院，南邊也是一大片宅區。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "northwest" : __DIR__"xiyuan",
                "southwest" : __DIR__"yuanhetang",
                "west"      : __DIR__"wuguangate",
                "south"     : __DIR__"zhaiqu3",
                "north"     : __DIR__"zhaiqu1",
        ]));
        set("objects", ([
                "/d/village/npc/kid" : random(3),
                "/d/village/npc/oldwoman" : random(3),
        ]));
	set("coor/x", -910);
	set("coor/y", -7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
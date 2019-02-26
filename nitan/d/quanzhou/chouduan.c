// Room: /d/quanzhou/chouduan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "鴻翔綢緞莊");
        set("long", @LONG
這就是天下聞名的絲綢銷售中心，古色古香的店面，門上掛幹飄着
一面質地上好的綢面，繡着紅色的「鴻翔綢緞」四個大字。中原來的上
等絲綢在此加工後源源不斷的運往西洋各國。莊內各式花色和質地的綢
緞應有盡有，琳琅滿目。
LONG );
        set("exits", ([
                "west"   : __DIR__"road1",
        ]));
        set("objects", ([
                __DIR__"npc/xu" : 1,
        ]));
	set("coor/x", -880);
	set("coor/y", -7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
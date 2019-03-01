// Room: /d/quanzhou/liandanshi.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "練膽石");
        set("long", @LONG
這是立崖上的一方窄石 (stone)，正處風口。人立其上，但覺狂風
撕扯，面如刀割，頭暈目眩，搖搖欲墜。相傳這是明朝抗倭英雄俞大猷
少年時的練膽石，上有他題刻的「恩重如山」四個字。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("item_desc", ([
                "stone" :"只見窄石聳立在崖上，任狂風暴哮始終不倒，你不禁感嘆造物之奇。\n",
        ]));
        set("exits", ([
                "eastdown"  : __DIR__"shanlu2",
                "northwest" : __DIR__"mituoyan",
        ]));
	set("coor/x", -910);
	set("coor/y", -7550);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
//Room: /d/dali/shanlu2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","山路");
        set("long",@LONG
一條山路，四面皆是茂密的樹林和延綿不絕的大山，道路兩旁間
或可見一些夷族的村鎮，西面一片高山高聳入雲，山顛白雪皚皚終年
不化。正路向西上山，一條岔路向南北蜿蜒着。
LONG);
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "east"      : __DIR__"shanlu3",
            "south"     : __DIR__"shanlu4",
            "northup"   : __DIR__"nianhuasi",
            "westup"    : __DIR__"biluoxueshan",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19160);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
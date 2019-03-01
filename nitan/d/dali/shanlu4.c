//Room: /d/dali/shanlu4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","山路");
        set("long", @LONG
一條山路，兩邊是茂密的樹林，西面是延綿不絕的大山，道路兩
旁間或可見一些夷族的村鎮。山路向南蜿蜒著。
LONG );
        set("objects", ([
           "/d/dali/npc/shennongdizi": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/shanlu2",
            "southwest"  : "/d/dali/shanlu5",
            "westup"     : "/d/wuliang/shanlu1",
        ]));
	set("coor/x", -19160);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
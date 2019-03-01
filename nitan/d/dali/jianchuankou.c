//Room: /d/dali/jianchuankou.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","劍川山口");
        set("long", @LONG
這裡是蒼山北麓的一個烏夷城鎮。此地正處山口，兩邊崇山峻嶺
聳立，幾乎無路可行，唯有穿此鎮可入蒼山，因此是從蜀中至大理的
軍事要沖，大理國在此修有刁樓箭塔，常年駐軍。有官兵在鎮口站崗
巡邏，盤察過往行人。
LONG );
        set("objects", ([
           "/d/dali/npc/jiang": 1,
           "/d/dali/npc/bing": 3,
        ]));
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/shanlu1",
            "south"      : "/d/dali/jianchuan",
        ]));
	set("coor/x", -19180);
	set("coor/y", -6800);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
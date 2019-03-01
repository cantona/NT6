// Room: /d/quanzhou/ruixiangyan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "瑞象巖");
        set("long", @LONG
這是座落在半山腰的小峽谷中的一塊石坪。登上此處，即可見一座
漂亮的仿木石室。石室後高聳的大巖石叫作「天柱峰」。古時一位巧匠
將其雕成「釋迦牟尼」瑞象，作立狀，神像莊嚴大方，維妙維肖。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "southup"     : __DIR__"wangzhouting",
                "northdown"   : __DIR__"shanlu3",
        ]));
        set("objects", ([
                "/d/wudang/npc/monkey" : 1,
        ]));
	set("coor/x", -900);
	set("coor/y", -7570);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
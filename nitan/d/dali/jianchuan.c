//Room: /d/dali/jianchuan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","劍川鎮");
        set("long", @LONG
這裡是劍川的鎮中心，鎮子不大，居民絕大部分是烏夷族，幾乎
全都以狩獵為生。由于山高地寒，附近山林的野獸大多皮粗毛厚，有
不少皮貨商在這裡和當地獵人交易。北出山口則屬大理北疆，也是入
蜀之途，南穿蒼山則可抵大理內陸。
LONG );
        set("objects", ([
           "/d/dali/npc/lieren": 1,
           "/d/dali/npc/pihuoshang": 1,
        ]));
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/jianchuankou",
            "south"      : "/d/dali/cangshanzhong",
        ]));
	set("coor/x", -19180);
	set("coor/y", -6810);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
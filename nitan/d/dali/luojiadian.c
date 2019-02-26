//Room: /d/dali/luojiadian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","羅伽甸");
        set("long", @LONG
這裏是滇池的東南，是麼些蠻的羅伽部落聚居的地方。麼些蠻族
屬擺夷。擺夷喜居平原沿水，（沿水的平原壩子，即為『甸』）。這
裏土壤肥沃，灌溉便易。羅伽是一個大部落，羅伽甸是個相當大的鎮
子，大理國在這裏設有治府。
LONG );
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "northwest"  : "/d/dali/yanchi3",
            "southwest"  : "/d/dali/yanan1",
            "east"       : "/d/dali/nongtian2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19070);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
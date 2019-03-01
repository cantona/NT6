//Room: /d/dali/shanlu1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","川西山路");
        set("long", @LONG
你走在川西山間的一條土路上。此間屬古蜀國境內，地勢甚高，
可山勢相對較平緩。西面可見白雪皚皚的青藏高原群山，向南一路穿
越山陵直通向雲南大理。附近山間有些烏夷人的村落。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "northup"    : "/d/dali/wunong",
            "south"      : "/d/dali/jianchuankou",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19180);
	set("coor/y", -6790);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
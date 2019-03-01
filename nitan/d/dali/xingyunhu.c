//Room: /d/dali/xingyunhu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","星雲湖畔");
        set("long",@LONG
星雲湖又名小鏡湖，方圓有十數裡。東靠玉霞山，碧水清澈，風
光嫵媚，乃是大理東部名景。明月之夜，皎潔的月光映照湖面，風拂
水波，搖曳生姿，如繁星落入湖中，晶亮如雲，故名之。在此遠眺湖
之東南岸，可見青青翠竹，似有房舍隱在其中。
LONG);
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "north"    : __DIR__"buxiongbu",
            "eastup"   : __DIR__"yuxiashan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19020);
	set("coor/y", -6920);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
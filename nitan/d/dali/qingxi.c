//Room: /d/dali/qingxi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","清溪三潭");
        set("long", @LONG
清溪三潭，又名翠盆水，隱藏在蒼山馬龍峯與聖應峯之間幽深的
峽谷中。山泉巖根湧出，噴珠瀉玉，巖溪匯池，壯若大盆，分三疊，
水清石麗，翠碧交加，故俗稱清碧溪。
LONG );
        set("objects", ([
           "/d/dali/npc/biaotou": 1,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "northup"   : "/d/dali/dadieshui",
            "eastup"    : "/d/dali/bijishan",
            "southdown" : "/d/dali/xiaodao1",
        ]));
	set("coor/x", -19110);
	set("coor/y", -6880);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
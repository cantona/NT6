//Room: /d/dali/road3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","官道");
        set("long", @LONG
你走在一條青石官道上，這裏已經是南詔境內了，路上時時可以
看到各色各樣的商人來來往往，絡繹不絕。路邊站了些個衣飾華豔的
擺夷女子，其中一個身穿白衣的顯得格外秀麗。此去向南即是大理國
北關口太和城，沿官道向東北可達中原。
LONG );
        set("objects", ([
           "/d/dali/npc/girl": 1,
        ]));
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : "/d/dali/road2",
            "south"      : "/d/dali/dehuabei",
            "northwest"  : "/d/wanjiegu/riverside2",
        ]));
	set("coor/x", -19160);
	set("coor/y", -6820);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
//Room: /d/dali/tusiyishi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","議事廳");
        set("long", @LONG
議事廳中央有神龕，龕下陳列着刀、叉、矛、戟等兵器。寬闊的
大樓上下，柱樑粗實。廳堂寬敞，前後各有一長排坐欄，供人納涼憩
息。
LONG );
        set("objects", ([
           "/d/dali/npc/datusi": 1,
           "/d/dali/npc/zutouren": 2,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "down"  : "/d/dali/tusimentang",
        ]));
	set("coor/x", -19141);
	set("coor/y", -6891);
	set("coor/z", 9);
	setup();
        replace_program(ROOM);
}
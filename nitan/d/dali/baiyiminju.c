//Room: /d/dali/baiyiminju.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","擺夷民居");
        set("long", @LONG
擺夷是大理第一大族，大多散布在蒼山洱海附近。擺夷民居是以
石塊壘成，別局風格。朝花節那天，家家戶戶都把盆栽花木擺在門口，
擺搭成一座座的『花山』，招引四野鄉村的人來觀花街。
LONG );
        set("objects", ([
           "/d/dali/npc/oldman": 1,
           "/d/dali/npc/girl1": 2,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/dahejieeast",
        ]));
     set("no_fight",0);
	set("coor/x", -19120);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
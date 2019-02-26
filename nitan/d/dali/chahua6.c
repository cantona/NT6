//Room: /d/dali/chahua6.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花園");
        set("long", @LONG
大理茶花冠絕天下，鎮南王府的茶花自然更非凡品。你站在茶花
園中，四周是翠綠的灌木，環繞着的是碧玉般柔潤的寒茵，一條清徹
的小溪輕輕流下南面的小湖，中間是一盆嬌豔的茶花。
LONG );
        set("objects", ([
           "/d/dali/obj/chahua5": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/chahua3",
            "north"  : "/d/dali/chahua7",
        ]));
	set("coor/x", -19071);
	set("coor/y", -6831);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}
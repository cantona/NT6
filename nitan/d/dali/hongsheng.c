//Room: /d/dali/hongsheng.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","宏聖寺塔");
        set("long", @LONG
宏聖寺塔又名『一塔』，屹立於蒼山之麓，面向洱海，為雲南著
名唐塔之一。宏聖寺塔為四方形空心磚石塔，塔身各層之間用磚砌出
跌澀椽，使其四角飛翹。整個塔身輪廓呈拋物線，優美流暢。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "west"      : "/d/dali/cangshan",
            "enter"     : "/d/dali/hongsheng1",
            "south"     : "/d/tianlongsi/damen",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalin"); 
        set("no_clean_up", 0);
	set("coor/x", -19150);
	set("coor/y", -6820);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
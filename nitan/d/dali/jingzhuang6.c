//Room: /d/dali/jingzhuang6.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","第六層");
        set("long", @LONG
有神龕五座，內中雕有佛像浮雕二百餘座。佈局嚴密，層次分明；
表情各異，比例協調；刀痕尤勁，備極精巧；線條流暢，栩栩如生；
不愧是滇南石雕藝術的珍品。世代金文家皆贊『滇中藝術，此及品也
』。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "up"    : "/d/dali/jingzhuang7",
            "down"  : "/d/dali/jingzhuang5",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 59);
	setup();
        replace_program(ROOM);
}
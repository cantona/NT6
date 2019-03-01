//Room: /d/dali/dating.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","五華樓大廳");
        set("long",@LONG
這裡是五華樓的前大廳，異常寬敞明亮，足有一裡見方，全是雲
石舖地，黑白相間，足足可以容納二、三千人。時時可見錦衣侍者手
托美食來回行走。
LONG);
        set("objects", ([
           __DIR__"npc/shizhe": 3,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "north"   : __DIR__"louti",
            "out"     : __DIR__"gudao",
        ]));
	set("coor/x", -19151);
	set("coor/y", -6921);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}
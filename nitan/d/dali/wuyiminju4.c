//Room: /d/dali/wuyiminju4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","烏夷民居");
        set("long",@LONG
這是一座用木柴及獸皮搭成的烏夷民居。此地的村民主要從事耕
作，由於實行換季輪耕，不得不經常遷徙，因而房舍都頗簡陋，説是
房舍，倒不如説更象帳篷，拆、建都甚方便。
LONG);
        set("objects", ([
           __DIR__"npc/kid": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "north"  : __DIR__"yixibu",
        ]));
	set("coor/x", -19200);
	set("coor/y", -6910);
	set("coor/z", 20);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/wymj4", 1, me);
        }
}
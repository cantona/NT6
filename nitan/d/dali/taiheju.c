//Room: /d/dali/taiheju.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","太和居");
        set("long", @LONG
這是大理城內最大的酒樓，樓下賣些大理的小吃，過往行人常常
買來作路菜。樓上是雅座。
LONG );
        set("objects", ([
           "/d/dali/npc/xiaoer2": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "west"  : "/d/dali/center",
            "up"    : "/d/dali/taiheju2",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
}
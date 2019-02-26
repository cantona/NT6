//Room: /d/dali/taiheju2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","太和居二樓");
        set("long", @LONG
這裏是太和居的二樓，樓梯邊上坐了些手持雲板，瑤琴的歌女。
富商土豪在這裏邊吃喝作樂，也有文人墨客在此飲酒清談，從南面窗
口望出，可以看道城外五華樓前的一波碧水。
LONG );
        set("objects", ([
           "/d/dali/npc/genu": 2,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "down"  : "/d/dali/taiheju",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6890);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
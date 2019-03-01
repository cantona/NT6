//Room: /d/dali/zhangfang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","帳房");
        set("long", @LONG
這裡是鎮南王府的帳房，王府每天的銀米出入，往來消耗，全由
這裡經手，包括家丁下人的薪俸賞賜，在在都是麻煩多多。這裡卻從
來沒出過差錯。
LONG );
        set("objects", ([
           "/d/dali/npc/huo": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/wfdating",
        ]));
	set("coor/x", -19131);
	set("coor/y", -6861);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}
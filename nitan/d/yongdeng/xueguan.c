// Room: /huanghe/xueguan.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "學館");
        set("long", @LONG
一間簡陋的私塾，四壁皆空，屋子中擺滿了學生從自己家裡抬來的
方桌、長凳。一張書案放在屋子的一頭，案上擺著幾本翻開了的□三字
經□、□百家姓□和一把戒尺。至聖先師孔老夫子的石刻拓片側身像貼
在書案的後面。
LONG );
        set("exits", ([
                "south"    : __DIR__"gulang",
        ]));
        set("objects", ([
                __DIR__"npc/xiucai" : 1,
        ]));
        set("coor/x", -16110);
	set("coor/y", 4220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
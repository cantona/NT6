// Room: /huanghe/yaocaidian.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "皮貨藥材店");
        set("long", @LONG
這是古浪城裡唯一的一家店舖，一踏進舖內就可聞到一股淡淡的膻
味，隱隱可以看見堆放在後院翻曬的各式皮貨，怕有不下千余件。在西
牆邊，立了一個大紅木藥櫃，裡面盛放了草藥。
LONG );
        set("exits", ([
                "west" : __DIR__"gulang",
        ]));
        set("objects", ([
                __DIR__"npc/huoji" : 1,
        ]));
        set("coor/x", -16100);
	set("coor/y", 4210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
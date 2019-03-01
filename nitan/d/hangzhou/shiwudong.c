// shiwudong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "石屋洞");
        set("long", @LONG
山路旁是石屋洞。石屋洞，洞中有洞，洞洞相連。主洞高大寬敞，
潔淨明亮，上寬下窄，狀如浮螺。西上便到了滿覺隴；山路的盡頭連着
一條由北至南的大道。
LONG);
        set("exits", ([
                "westup"    : __DIR__"manjuelong",
                "east"      : __DIR__"road18",
        ]));
        set("objects", ([
            __DIR__"npc/xiezi": 1,
        ]));
//        set("no_clean_up", 0);
	set("coor/x", 810);
	set("coor/y", -2110);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
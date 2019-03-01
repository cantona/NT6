#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
這是一條寬敞的大道。全由亂石堆成，顯然曾花了不少人力。西
邊是一片開闊地。
LONG );

        set("exits", ([
	        "west" : __DIR__"kongdi",
	        "north" : __DIR__"road2",
        ]));
        set("objects", ([
	        __DIR__"npc/old": 2,
        ]));
        set("outdoors", "shenlong");
        setup();
        replace_program(ROOM); 
}

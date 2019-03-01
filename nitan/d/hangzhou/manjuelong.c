// manjuelong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "滿覺隴");
        set("long", @LONG
山路旁有一個小村落，村落四周桂花成林。每當仲秋，桂花盛開，
飄香數裡。被稱為“金雪世界”。西上是水樂洞，東下石屋洞。
LONG);
        set("outdoors", "hangzhou");
        set("exits", ([
                "westup"    : __DIR__"shuiledong",
                "eastdown"  : __DIR__"shiwudong",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 800);
	set("coor/y", -2110);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
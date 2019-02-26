inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","花廳");
        set("long", @LONG
這個花廳是喝酒賞月的佳所，一個小亭子建造在廳的中央，四周
圍繞着一些葡萄藤。一陣微風吹過，空氣中似乎有隱隱的花香飄來，
中人慾醉。
LONG );
        set("exits", ([
                "west" : "/d/beijing/hai_dayuan",
        ]));

	set("coor/x", -2800);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
}
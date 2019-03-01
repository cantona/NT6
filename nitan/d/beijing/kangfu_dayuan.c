#include <room.h>
inherit ROOM;

void create()
{
        set("short", "康府大院");
        set("long", @LONG
這是康親王府大門東邊的一個寬闊的大院，院內打掃得非常幹凈，
周圍還種滿了各類花草，康府裡的下人穿梭其中，北邊是一條木制走
廊，通往康府的大廳。
LONG );
       set("exits", ([
                "west" : "/d/beijing/kangfu_men",
                "north" : "/d/beijing/kangfu_zoulang1",
        ]));
        set("objects", ([
                "/d/beijing/npc/jiading_k" : 2,
                "/d/beijing/npc/yuanding" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
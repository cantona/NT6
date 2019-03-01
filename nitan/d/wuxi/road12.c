// Room: /d/wuxi/road12.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "湖邊小徑");
        set("long", @LONG
這是太湖邊上的一條小徑，道旁花草雜生，耳中鶯歌燕啼。東面
是一望無際的太湖，碧波萬頃，煙波浩渺，眺之身心舒暢。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"road11",
                "northeast" : __DIR__"road13",
        ]));
        set("coor/x", 1050);
	set("coor/y", -810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
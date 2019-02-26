inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","海澄公府");
        set("long", @LONG
你來到一所巨宅門前，巨宅的大門緊緊關閉着，門上掛着一塊大
匾，匾上寫着『海澄公府』四個大字，雖然和鹿鼎公府同是公爵府，
可是大小、派頭卻大不相同，大門匾額上那『海澄公府』四字是黑字，
一點也不起眼。
LONG );
        set("exits", ([
                "north" : "/d/beijing/fu_2",
                "south" : "/d/beijing/hai_dayuan",
        ]));

	set("coor/x", -2810);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
}
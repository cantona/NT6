inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","後院");
        set("long", @LONG
這裏是海澄公府大廳後側的一個小花園，雜亂地種着各種花草，
看來無人打理，雜草已經長得很高了。一些鮮花夾雜在草叢中，陣陣
花香不斷地飄過。
LONG );
        set("exits", ([
                "north" : "/d/beijing/hai_dating",
        ]));

	set("coor/x", -2810);
	set("coor/y", 7610);
	set("coor/z", 0);
	setup();
}
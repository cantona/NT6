#include <room.h>
inherit ROOM;

void create()
{
        set("short", "楊柳衚衕");
        set("long", @LONG
這裏是楊柳衚衕的底端，走到這裏，行人已經不多見了。一路上，
衚衕兩旁四合院的大門緊閉着，唯獨這裏南邊的一個四合院大門是敞
開着的。你不禁想去看一看。
LONG );
       set("exits", ([
                "north" : "/d/beijing/yangliu2",
                "south" : "/d/beijing/qingmu_men",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
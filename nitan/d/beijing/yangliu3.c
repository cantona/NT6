#include <room.h>
inherit ROOM;

void create()
{
        set("short", "楊柳胡同");
        set("long", @LONG
這裡是楊柳胡同的底端，走到這裡，行人已經不多見了。一路上，
胡同兩旁四合院的大門緊閉著，唯獨這裡南邊的一個四合院大門是敞
開著的。你不禁想去看一看。
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
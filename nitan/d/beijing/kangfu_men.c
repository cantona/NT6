inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","康府大門");
        set("long", @LONG
這裏便是康親王的王府大門所在。來到這裏，一座富麗堂皇的巨
宅院出現在你的眼前，大門兩側是兩頭高大的石獅子。門上掛着兩個
燈籠，赫然寫着大大的『康』字。門前站着兩個提刀的侍衞，警惕的
注視着過往的行人。
LONG );
        set("exits", ([
                "west" : "/d/beijing/bei_2",
                "east" : "/d/beijing/kangfu_dayuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/shi_k" : 2,
        ]));
	set("coor/x", -2810);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("shi wei", environment(me))) && dir == "east")
                return notify_fail("康府侍衞一把攔住你，朗聲喝道：王府要地，怎由閒雜人等隨便進出。\n\n");
        return ::valid_leave(me, dir);
}
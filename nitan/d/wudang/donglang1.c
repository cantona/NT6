#include <room.h>
inherit ROOM;

void create()
{
        set("short", "東廂走廊");
        set("long", @LONG
你走在一條走廊上，東邊有幾間雅室，人來人往很是熱鬧。西邊
則是武當派的大殿。
LONG );
        set("exits", ([
                "east" : __DIR__"donglang2",
                "west" : __DIR__"sanqingdian",
        ]));
        set("objects", ([
                CLASS_D("wudang") + "/xi" : 1
        ]));
        set("coor/x", -360);
        set("coor/y", -300);
        set("coor/z", 90);
        setup();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir != "east")
                return 1;

        if (! objectp(guarder = present("zhang songxi", environment(me))))
                return 1;

        return guarder->permit_pass(me, dir);
}
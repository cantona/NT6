// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蛇谷山道");
        set("long", @LONG
這是白駝山蛇谷中的山路，是一條人馬踩出來的小道，隨著地勢
曲折起伏，蜿蜒難行。
LONG );

        set("exits", ([ 
                "southeast" : __DIR__"shegu2",
                "northeast" : __DIR__"shegu4",
        ]));

        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49980);
        set("coor/y", 20130);
        set("coor/z", 20);
        setup();
}

void init()
{
        set("enter_shegu", 1, this_player());
}
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蛇谷山道");
        set("long", @LONG
這是白駝山蛇谷中的山路，是一條人馬踩出來的小道，隨着地勢
曲折起伏，蜿蜒難行。山路兩旁林木葱鬱，草叢中不時響起沙沙之聲，
似乎有什麼在草裏來回竄動。西北邊的樹木似乎比較稀少。
LONG );

        set("exits", ([
                "southeast" : __DIR__"shegu4",
                "northwest" : __DIR__"shegu6",
        ]));

        set("objects", ([
                __DIR__"obj/branch2" : 1,
                __DIR__"npc/maque" : 2,
        ]));

        set("hide_snake", random(3));
        set("grass", 1);

        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49980);
        set("coor/y", 20150);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"
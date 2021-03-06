// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蛇谷樹林");
        set("long", @LONG
這是白駝山的蛇谷之中，林木葱鬱，草叢中不時響起沙沙之聲，
似乎有什麼在草裏來回竄動。
LONG );

        set("exits", ([ 
            "west" : __DIR__"shegu9",
            "northeast" : __DIR__"shegu7",
        ]));

        set("hide_snake", random(3));
        set("grass", 1);

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -50010);
        set("coor/y", 20170);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"
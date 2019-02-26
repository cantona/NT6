// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蛇谷荒地");
        set("long", @LONG
這裏是蛇谷深處，草木大多枯黃凋敝，極是荒僻。四下幽暗寂靜，
山谷中微風時起，帶來陣陣草木腐敗的氣味。地上偶爾出現一些小動
物的骸骨，不知是被什麼毒蛇猛獸吃掉了。
LONG );

        set("exits", ([ 
            "northeast" : __DIR__"shegu25",
            "northwest" : __DIR__"shegu_maze" + (5+random(4)),
            "southwest" : __DIR__"shegu_maze7",
            "southeast" : __DIR__"shegu_maze6",
        ]));

        set("hide_python", random(2));

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49990);
        set("coor/y", 20200);
        set("coor/z", 20);
        setup();
}

#include "python_room.h"
// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;
string look_crack();

void create()
{
        set("short", "蛇谷樹林");
        set("long", @LONG
這是白駝山蛇谷中的一處密林，雜草叢生，樹木枝椏茂密，幽暗
陰森，古木盤根錯節，有些樹根間的裂縫(crack)中響着細碎的聲音。
LONG );

        set("exits", ([
            "west" : __DIR__"shegu18",
            "southeast" : __DIR__"shegu16",
        ]));

        set("item_desc", ([
        "crack" : (: look_crack :),
        ]));

        set("objects", ([
            __DIR__"obj/branch"+(1+random(4)) : 1,
        ]));

        set("hide_snake", 1+random(3));
        set("grass", 1);
        set("crack", 1);

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49940);
        set("coor/y", 20180);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"
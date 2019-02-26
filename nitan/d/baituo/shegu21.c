// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;
string look_bush();

void create()
{
        set("short", "蛇谷樹林");
        set("long", @LONG
這是白駝山的蛇谷之中，四周生長着叢叢矮樹(bush)，滿地都是
雜草和枯枝敗葉，氣味不大好聞。小路曲折地穿過樹叢，不知道通往
哪裏。
LONG );

        set("exits", ([ 
            "east" : __DIR__"shegu20",
            "northwest" : __DIR__"shegu22",
        ]));

        set("item_desc", ([
        "bush" : (: look_bush :),
        ]));

        set("hide_snake", random(3));
        set("grass", 1);
        set("bush", 1);

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -50010);
        set("coor/y", 20180);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"
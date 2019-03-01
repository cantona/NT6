// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "水池");
        set("long", @LONG
一潭清澈的池水，由蛇谷山麓間的流水積蓄而成，是谷中動物的
重要水源，許多飛禽走獸都在這裡飲水。
LONG );

        set("exits", ([ 
            "south" : __DIR__"shegu12",
        ]));

        set("hide_snake", random(3));

        set("resource/water",1);
        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -50050);
        set("coor/y", 20180);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"
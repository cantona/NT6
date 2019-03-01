// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蛇谷坡地");
        set("long", @LONG
這裡已經是蛇谷的另一端，山勢起伏較大，西南邊是一片樹林，
往北則是亂石嶙峋的山崖。
LONG );

        set("exits", ([ 
            "northup" : __DIR__"shegu_shanya",
            "southwest" : __DIR__"shegu18",
        ]));

        set("objects", ([
            __DIR__"npc/bt_snake" : 2,
        ]));

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49940);
        set("coor/y", 20190);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"
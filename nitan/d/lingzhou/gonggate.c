// Room: /lingzhou/gonggate.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "皇宮大門");
        set("long", @LONG
這裏就是西夏皇宮正門，四扇寬闊的硃紅大門，上面包着拳頭大的
銅釘。門的兩邊站着兩排衣甲鮮明的武士，戒備深嚴。
LONG );
        set("exits", ([
                "north"  : __DIR__"gongsquare",
                "south"  : __DIR__"beidajie",
        ]));
        set("outdoors", "lingzhou");
        set("objects", ([
                __DIR__"npc/gongweishi" : 2,
        ]));
        set("coor/x", -6265);
        set("coor/y", 2945);
        set("coor/z", 0);
        setup();
        create_door("north" , "紅漆宮門", "south" , DOOR_CLOSED);
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && 
            objectp(present("wei shi", environment(me))))
           return notify_fail("衞士對你大吼一聲：放肆！那不是你能進去的地方。\n");

        return ::valid_leave(me, dir);
}
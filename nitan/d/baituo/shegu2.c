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
                "southup"   : __DIR__"shegu1",
                "northwest" : __DIR__"shegu3",
        ]));

        set("outdoors", "baituo");
        set("shegu", 1);
        set("coor/x", -49970);
        set("coor/y", 20120);
        set("coor/z", 20);
        setup();
}

void init()
{
        set("enter_shegu", 1, this_player());
}

int valid_leave(object me, string dir)
{
        object room;
        int i, w;

        room = load_object(__DIR__"shegu1");

        if (dir == "southup") {
                if( !query("baituo/shegu_permit", me) && query("defense", room) )
                        return notify_fail("你想走出蛇谷，但是谷口紅霧彌漫，你一走近，便覺腥臭撲鼻，感覺竟有些暈眩。\n"
                                "看來這是極為厲害的毒霧，難以強行通過。\n");
        }
        return ::valid_leave(me,dir);
}
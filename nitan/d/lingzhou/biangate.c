// Room: /lingzhou/biangate.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "邊門");
        set("long", @LONG
這裡是皇宮的邊門，供侍衛和內侍們出入之用，宮裡所需的東西一
般都由此運入，因為比較偏僻，守衛的衛士也不多。
LONG );
        set("exits", ([
                "west" : __DIR__"chaifang",
                "east" : __DIR__"xiaolu3",
        ]));
        set("objects", ([
                __DIR__"npc/gongweishi" : 2,
        ]));
        set("outdoors", "xixiagong");
        set("coor/x", -6255);
        set("coor/y", 2985);
        set("coor/z", 0);
        setup();
        create_door("west" , "木門", "east" , DOOR_CLOSED);
}

int valid_leave(object me, string dir)
{
        if (dir == "west" && objectp(present("wei shi", environment(me))))
                return notify_fail("衛士對你大吼一聲：放肆！那不是你能進去的地方。\n");

        return ::valid_leave(me, dir);
}
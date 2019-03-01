// mishi1.c 密室
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
這裡是古墓中的密室，四周密不透風，你只能借著牆上昏暗的燈光
來勉強分辨方向。牆是用整塊的青石砌合起來的，接合的甚是完美，你
難以從中找出一絲縫隙。
LONG        );
        set("exits", ([
                "out"   : __DIR__"bianhou",
                "north" : __DIR__"mishi2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", 20);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}

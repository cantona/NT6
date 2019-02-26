// Room: /d/changcheng/fenghuotai1_2.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "烽火台");
        set("long", WHT @LONG
這裏是烽火台的二樓，站在這裏你可以看的很遠。戍邊的將士們就
是長年守衞在這裏，防止匈奴的進攻，保衞邊疆的安全。從這裏向東你
隱隱約約可以看到長城上著名的居庸關。
LONG
NOR );
        set("outdoors", "changcheng");
        set("objects", ([
                __DIR__"npc/guanbing" : 2,
        ]));
        set("exits", ([
                "down" :__DIR__"fenghuotai1-1",
        ]));
        set("coor/x", -6000);
        set("coor/y", 7000);
        set("coor/z", 110);
        setup();
        replace_program(ROOM);
}
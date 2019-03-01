// Room: /d/changcheng/fenghuotai2-2.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "烽火台");
        set("long", WHT @LONG
這裡是烽火台的二樓，站在這裡你可以看的很遠。戍邊的將士們就
是長年守衛在這裡，防止匈奴的進攻，保衛邊疆的安全。
LONG
NOR  );
        set("outdoors", "changcheng");
        set("objects", ([
                __DIR__"npc/guanbing" : 2,
        ]));
        set("exits", ([
                "down" :__DIR__"fenghuotai2-1",
        ]));
        set("coor/x", -10010);
        set("coor/y", 8000);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}
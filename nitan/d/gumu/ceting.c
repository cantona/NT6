// ceting.c 側廳
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

int do_tang(string arg);
int do_niu(string arg);

void create()
{
        set("short", "側廳");
        set("long", @LONG
這裡是古墓的側廳，密封得嚴嚴實實，沒有一絲的縫隙。在昏暗的
燈光下，很難看清楚廳裡的陳設。
LONG        );
        set("exits", ([
                "east"  : __DIR__"mudao20",
                "north" : __DIR__"mudao19",
                "south" : __DIR__"mudao23",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3180);
        set("coor/y", -10);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}

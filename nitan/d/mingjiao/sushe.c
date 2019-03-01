// Room: /d/mingjiao/sushe.c
// Jan.5 1997 by Venus

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "雷門宿舍");
        set("long", @LONG
走進這間宿舍，滿目異國情調。雷門教眾似乎不大理睬你。許是
言語不通，你也不想在此多留。
LONG );
    set("exits", ([
        "out" : __DIR__"mjleimen1",
    ]));
    set("no_clean_up", 0);
    set("sleep_room", 1);
    set("no_fight", 1);
    setup();
    replace_program(ROOM);
}
// Room: /d/pk/turen4.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "碎屍場" NOR);
        set("long", @LONG
這裏陰森恐怖，地上到處是殘肢碎屍，無處不是暗紅色的血滴。你心中
忐忑不安，萬分警惕，不知道從哪裏就會竄出一個黑影。
LONG
        );
        set("exits", ([
                "east"  : __DIR__"turen5",
                "south" : __DIR__"turen8",
                "west"  : __DIR__"turen3",
                "north" : __DIR__"turen1",
        ]));
        set("no_learn", 1);

        setup();
        replace_program(ROOM);
}
// Room: /d/pk/turen9.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "送命場" NOR);
        set("long", @LONG
這裏陰森恐怖，地上到處是殘肢碎屍，無處不是暗紅色的血滴。你心中
忐忑不安，萬分警惕，不知道從哪裏就會竄出一個黑影。
LONG
        );
        set("exits", ([
                "east"  : __DIR__"turen10",
                "south" : __DIR__"turen12",
                "west"  : __DIR__"turen8",
                "north" : __DIR__"turen5",
        ]));
        set("no_learn", 1);

        setup();
        replace_program(ROOM);
}
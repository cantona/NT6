// Room: /d/pk/turen7.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "喪命場" NOR);
        set("long", @LONG
這裡陰森恐怖，地上到處是殘肢碎屍，無處不是暗紅色的血滴。你心中
忐忑不安，萬分警惕，不知道從哪裡就會竄出一個黑影。
LONG
        );
        set("exits", ([
                "east"  : __DIR__"turen8",
                "southeast" : __DIR__"turen11",
                "north" : __DIR__"turen3",
        ]));
        set("no_learn", 1);

        setup();
        replace_program(ROOM);
}
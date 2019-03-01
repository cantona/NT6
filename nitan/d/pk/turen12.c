// Room: /d/pk/turen12.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "戮人場" NOR);
        set("long", @LONG
這裡陰森恐怖，地上到處是殘肢碎屍，無處不是暗紅色的血滴。你心中
忐忑不安，萬分警惕，不知道從哪裡就會竄出一個黑影。
LONG
        );
        set("exits", ([
                "northeast"  : __DIR__"turen10",
                "west"  : __DIR__"turen11",
                "north" : __DIR__"turen9",
        ]));
        set("no_learn", 1);

        setup();
        replace_program(ROOM);
}
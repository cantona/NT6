// Room: /d/pk/turen11.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "誅人場" NOR);
        set("long", @LONG
這裡陰森恐怖，地上到處是殘肢碎屍，無處不是暗紅色的血滴。你心中
忐忑不安，萬分警惕，不知道從哪裡就會竄出一個黑影。
LONG
        );
        set("exits", ([
                "east"  : __DIR__"turen12",
                "northwest"  : __DIR__"turen7",
                "north" : __DIR__"turen8",
        ]));
        set("no_learn", 1);

        setup();
        replace_program(ROOM);
}
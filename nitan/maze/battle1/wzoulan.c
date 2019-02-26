// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG"小道"NOR);
        set("long", @LONG
這裏是一條林中小道，寂靜得讓人害怕。
LONG
        );
        set("exits", ([
                "north" : __DIR__"wgarden",
                "east"  : __DIR__"room_04",
        ]));
        set("outdoors", "battle");

        setup();
}

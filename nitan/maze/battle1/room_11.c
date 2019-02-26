// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIM"山道"NOR);
        set("long", @LONG
這裏是一條陡峭的山道，通望險峻的山峯。這裏地勢險要，真是一關把道，萬夫莫行。
LONG
    );
        set("exits", ([
                "west"      : __DIR__"room_02",
                "south"     : __DIR__"room_12",
                "northeast" : __DIR__"room_10",
        ]));
        set("outdoors", "battle");
        setup();
}

// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG"山道"NOR);
        set("long", @LONG
這裏是一條陡峭的山道，通望險峻的山峯。這裏地勢險要，真是一關把道，萬夫莫行。
LONG
    );
        set("exits", ([
                "east"  : __DIR__"room_08",
                "south" : __DIR__"room_06",
                "west"  : __DIR__"room_16",
        ]));
        set("outdoors", "battle");
        setup();
}

// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIM"山道"NOR);
        set("long", @LONG
這裡是一條陡峭的山道，通望險峻的山峰。這裡地勢險要，真是一關把道，萬夫莫行。
LONG
    );
        set("exits", ([
                "north"     : __DIR__"room_17",
                "southwest"     : __DIR__"room_19",
                "east"      : __DIR__"room_08",
        ]));
        set("outdoors", "battle");
        setup();
}

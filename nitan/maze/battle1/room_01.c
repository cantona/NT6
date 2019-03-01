// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
         set("short", HIG"山道"NOR);
         set("long", @LONG
這裡是一條陡峭的山道，通望險峻的山峰。這裡地勢險要，真是一關把道，萬夫莫行。
LONG
    );
        set("exits", ([
                "east" : __DIR__"room_03",
                "up" : __DIR__"wtower1",
                "west" : __DIR__"wgarden",
        ]));

        set("outdoors", "battle");
        setup();
}

//nzlang2.c                四川唐門─走廊

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long",
"這裡是蓮雲閣北側的走廊。兩旁是碧綠的湖水，無數荷花含苞欲放，\n"
"這美景讓人留連忘返，止步不前。這裡通向蓮雲閣後宅。\n"
);
        set("exits", ([
                        "south" : __DIR__"houzhai",
                        "north" : __DIR__"nzlang3",
                        "west" : __DIR__"tangwen",
                        "east" : __DIR__"tanggan",
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}
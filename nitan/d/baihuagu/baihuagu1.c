// Room: /d/baihuagu/baihuagu1.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIM"百花谷內"NOR);
        set("long", 
HIG"只見奼紫嫣紅，滿山錦繡，彩蝶紛飛，羣蜂輕舞。縱是宇外瓊地，
世外桃源，也不過如此。\n"NOR);
        set("outdoors", "baihuagu");
        set("exits", ([
                "north" : __DIR__"baihuagu",
                "south" : __FILE__,
                "west"  : __DIR__"baihuagu",
                "east"  : __DIR__"baihuagu2",
        ]));
        set("objects", ([
        ]));
        set("no_clean_up", 0);
        set("coor/x", -430);
        set("coor/y", -360);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
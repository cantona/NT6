// Room: /d/baihuagu/baihuagu2.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIM"百花谷內"NOR);
        set("long", 
HIG"只見奼紫嫣紅，滿山錦繡，彩蝶紛飛，羣蜂輕舞。縱是宇外瓊地，
世外桃源，也不過如此。山坡下一列掛着七八個木製的蜂巢另一面山
山坡上蓋着三間茅屋。\n"NOR);
        set("outdoors", "baihuagu");
        set("exits", ([
                "north"    : __DIR__"baihuagu",
                "westup"   : __DIR__"shanpo1",
                "eastdown" : __DIR__"shanpo2",
                "south"    : __DIR__"baihuagu1",
                "west"     : __DIR__"baihuagu",
                "east"     : __FILE__,
        ]));
        set("objects", ([
        ]));
        set("no_clean_up", 0);
        set("coor/x", -400);
        set("coor/y", -360);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
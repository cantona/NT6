// Room: /d/changcheng/fenghuotai2-1.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "烽火台");
        set("long", WHT @LONG
這裡是烽火台的內部，這裡不是很亮，四周亂糟糟的放著一些雜物，
但靠牆的兵器架上的兵器卻擦的亮光閃閃，可見雖然生活很艱苦，但將
士們卻沒有忘記自己的責任。
LONG
NOR );
        set("exits", ([
                "up"       :__DIR__"fenghuotai2-2",
                "east"     :__DIR__"changcheng13",
                "northwest":__DIR__"changcheng14",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -10010);
        set("coor/y", 8000);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}
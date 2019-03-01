// Room: /d/changcheng/changcheng10.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT@LONG
這裡就是舉世聞名的──長城。站在長城上，你可以看到四周群山
環繞，山上可以看見不少矮矮的灌木叢，但不少的樹也被砍光了，很多
地方已經露出了一片片的黃土，舉目望去，你腳下的長城順著山脊象一
條巨龍般蜿蜒的向西，向南延伸出去。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "west"    :__DIR__"changcheng11",
                "southup" :__DIR__"changcheng9",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -7000);
        set("coor/y", 9000);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}
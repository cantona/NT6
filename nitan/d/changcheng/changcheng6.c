// Room: /d/changcheng/changcheng6.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT @LONG
這裏就是舉世聞名的──長城。站在長城上，你可以看到四周羣山
環繞，山上可以看見不少矮矮的灌木叢，但不少的樹也被砍光了，很多
地方已經露出了一片片的黃土，舉目望去，你腳下的長城順着山脊象一
條巨龍般蜿蜒的向西北，向東延伸出去。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "northwest" :__DIR__"changcheng7.c",
                "east"      :__DIR__"changcheng5.c",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -5000);
        set("coor/y", 5000);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}
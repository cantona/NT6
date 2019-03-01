// Room: /d/changcheng/changcheng12.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT @LONG
這裡就是舉世聞名的──長城。站在長城上，你可以看到四周群山
環繞，山上的灌木叢已經不象東邊的那麼多了，樹也被砍了不少，很多
地方已經露出了一片片的黃土，舉目望去，你腳下的長城順著山脊象一
條巨龍般蜿蜒的向東，向南延伸出去。四面望去，人煙稀少，讓你感到
一片荒涼。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "south" :__DIR__"changcheng13",
                "east"  :__DIR__"changcheng11",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -10000);
        set("coor/y", 9000);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}
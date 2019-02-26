// Room: /d/changcheng/changcheng22.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT@LONG
這裏就是舉世聞名的──長城。站在長城上，你可以看到四周羣山
環繞，山上到處都是矮矮的灌木叢，舉目望去，你腳下的長城順着山脊
象一條巨龍般蜿蜒的向東北和西方延伸出去。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "westup"    :__DIR__"nansilou",
                "northeast" :__DIR__"changcheng23",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 3000);
        set("coor/y", 5000);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}
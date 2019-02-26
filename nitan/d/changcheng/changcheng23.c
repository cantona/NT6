// Room: /d/changcheng/changcheng23.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT@LONG
這裏就是舉世聞名的──長城。站在長城上，你可以看到四周羣山
環繞，山上到處都是矮矮的灌木叢，舉目望去，你腳下的長城順着山脊
象一條巨龍般蜿蜒的向西南和東南方延伸出去。在這裏，你已經能看到
東南方遠處的海和一座雄偉的關城了。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "southeast" :__DIR__"shanhaiguan",
                "southwest" :__DIR__"changcheng22",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 4000);
        set("coor/y", 6000);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}
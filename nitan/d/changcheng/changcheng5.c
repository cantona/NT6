// Room: /d/changcheng/changcheng5.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT @LONG
這裡就是舉世聞名的──長城。站在長城上，你可以看到四周群山
環繞，山上可以看見不少矮矮的灌木叢，但有的地方已經露出了一片片
的黃土地，舉目望去，你腳下的長城順著山脊象一條巨龍般蜿蜒的向東
和向西延伸出去。從這裡向東你隱隱約約可以看到東邊似乎有一座很大
的關卡。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "west"     :__DIR__"changcheng6.c",
                "eastdown" :__DIR__"changcheng4.c",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -4000);
        set("coor/y", 5000);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}
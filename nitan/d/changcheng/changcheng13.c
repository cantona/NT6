// Room: /d/changcheng/changcheng13.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT @LONG
這裏就是舉世聞名的──長城。站在長城上，你可以看到山脈連綿
起伏，山上已經很少看到樹和灌木叢了。山上大片的地方光禿禿的，很
多地方已經露出了大片的黃土，你腳下的長城蜿蜒的向北，向南延伸出
去。站在這裏，你已經可以感到迎面過來的大風中帶着不少沙子，而長
城厚厚的城牆也被侵蝕的七零八落，不遠處的一段城牆已經倒塌。你只
好向南繞過去。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "west"  :__DIR__"fenghuotai2-1",
                "north" :__DIR__"changcheng12",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -10000);
        set("coor/y", 8000);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}
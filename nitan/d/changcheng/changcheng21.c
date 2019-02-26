// Room: /d/changcheng/changcheng21.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT@LONG
由於長期受到風沙的侵蝕，不少城牆已經倒塌。牆角的黃沙中有許
多從城牆上掉下來的青磚。前面不遠處就是長城的終點──嘉峪關。由
於這裏是西域通往關內的必經之路，所以人也多了起來。只見許多碧眼
金髮的商人帶着他們的商隊匆匆向離去。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "southwest" : __DIR__"jiayuguan",
                "east"            : __DIR__"changcheng20",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -17000);
        set("coor/y", 9000);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
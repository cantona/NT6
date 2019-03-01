// Room: /d/hengshan/yunge.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "雲閣臥波");
        set("long", @LONG
過完棧道，就到雲閣虹橋。前往恆山主峰見性峰，都要在這裡跨過
唐峪河。拱橋臥波，水天亮麗，倍覺胸襟舒暢。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "east"      : __DIR__"daziling",
                "northdown" : __DIR__"zhandao",
        ]));
        set("objects", ([
                CLASS_D("hengshan")+"/zhi" : 1,
        ]));
        set("outdoors", "hengshan");
//        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 3140);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}

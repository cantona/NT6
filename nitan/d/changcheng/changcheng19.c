// Room: /d/changcheng/changcheng19.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT @LONG
你唱着，唱着，忽然迎面刮來一陣大風，吹的你滿頭，滿臉，滿嘴
的沙子。你的急忙閉上了嘴，興致一下全沒了。你看了一下周圍，只見
四周已經很少看到植物，到處是黃沙，使人感到一片荒涼。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "southwest" :__DIR__"changcheng20",
                "northeast" :__DIR__"changcheng18",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15000);
        set("coor/y", 10000);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}

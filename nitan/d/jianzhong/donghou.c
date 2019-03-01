#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","深谷");
        set("long",@LONG
洞後深谷中風景更是幽雅，樹木蒼翠，山氣清佳，你信步過
去觀賞景色，不知不覺中走進了樹林深處。
LONG
        );
        set("exits",([
                "north":__DIR__"donghou1",
                "south":__DIR__"dongkou",
        ]));
        set("outdoors", "jianzhong");
        set("coor/x", -400);
        set("coor/y", -430);
        set("coor/z", 0);
        setup();
}
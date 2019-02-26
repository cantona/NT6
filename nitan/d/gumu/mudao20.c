// mudao20.c 墓道
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG"墓道"NOR);
        set("long", @LONG
這裏是古墓中的墓道，四周密不透風，藉着牆上昏暗的燈光，你能
勉強分辨出方向。牆是用整塊的青石砌合起來的，接合得甚是完美，難
以從中找出一絲縫隙。燈光照在青石壁上，閃爍着碧幽幽的光點。
LONG        );
        set("exits", ([
                "west" : __DIR__"ceting",
                "east" : __DIR__"woshi1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3170);
        set("coor/y", -10);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
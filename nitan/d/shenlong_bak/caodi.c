// /d/shenlong/caodi.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
這裏是一片青青的草地，有幾個少年在玩耍。四周開滿了各色的鮮
花，一陣涼風吹過，清新的空氣中傳來幾縷淡淡的花香。
LONG );
        set("exits", ([
                "west"  : __DIR__"kongdi",
                "north" : __DIR__"xiaowu",
        ]));
        set("outdoors", "shenlong");
        set("no_clean_up", 0);
        set("coor/x", 4000);
        set("coor/y", 3040);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

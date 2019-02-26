// Room: /heizhao/xixiang.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "西廂房");
        set("long", @LONG
這裏是一燈大師的弟子們平常打坐練功的地方。地上鋪着一些
蒲團，牆邊靠着一些兵器，地上的青磚都已經陷出足印了，青磚被
蹭得十分光滑。
LONG );
        set("objects", ([
                "/clone/npc/mu-ren": 6,
        ]));
        set("exits", ([
                "east"       : __DIR__"chanyuan",
        ]));
        set("coor/x", -5030);
        set("coor/y", -1200);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}
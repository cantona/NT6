// chanfang1.c 禪房
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "禪房");
        set("long", @LONG
這裏是全真教弟子擺放兵器的禪房，地下雜亂地堆着一些劍，有
的已經鏽紋斑斑了，有的還是鋒利透亮，全真弟子練功的時候，就到
這裏來挑選兵刃。
LONG
        );
        set("exits", ([
                "east" : __DIR__"chanfang2",
        ]));
        set("objects", ([
                __DIR__"npc/obj/gangjian" : random(3),
                __DIR__"npc/obj/gangdao" : random(2),
                __DIR__"npc/obj/tiejia" : random(2),
        ]));

        set("coor/x", -2750);
        set("coor/y", 130);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}
// Last Modified by Sir on May. 22 2001
// liangong.c 練功房

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "練功房");
        set("long", @LONG
這裡是恆山派弟子練功的房間。房間中央立著幾個練功用的木人。
LONG );

        set("exits", ([
                "south" : __DIR__"byaeast",                
        ]));
        
        set("objects", ([
                "/d/shaolin/npc/mu-ren" : 5,
        ]));
        set("coor/x", 50);
        set("coor/y", 3220);
        set("coor/z", 100);
        setup();
}

// Room: /d/gaibang/undergb.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short","破廟密室");
        set("long", @LONG
這是丐幫重要密道之一。由此上往，可直達破廟。四周光線昏暗，
似乎有幾個黑暗的洞口在你身邊。腳下地上扔滿了垃圾，踩上去悉悉
索索地響。
LONG );
        set("exits", ([
                "up" : __DIR__"pomiao",
                "southwest":__DIR__"zlandao2",
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/xi" : 1,
                "/d/gaibang/npc/6dai" : 1 + random(2),
                "/d/gaibang/npc/7dai" : 1 + random(2),
        ]));
        set("no_clean_up", 0);
        set("coor/x", 70);
        set("coor/y", 60);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}

// /d/shenlong/zhulin2 竹林2
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "竹林");
        set("long", @LONG
這兒是一片密實的竹林，光線暗淡，你一不小心就會被腳下的枝條
絆個跟頭。附近似乎有輕微的沙沙聲，好象是海風吹過又好象是蟲子爬
過，你覺得有點不對勁，但又說不出是什麼。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "south" : __DIR__"zhulin1",
                "north" : __DIR__"liangongfang",
        ]));
        set("snaketype", ({"zsnake"}));

        setup();
}

#include "snakeroom.h";

// 山路 shanlu4.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "山路");
        set("long", @LONG
這是一條彎彎曲曲的山路，西面傳來陣陣清香，你循著清香走了
過去。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "southdown" : __DIR__"shanlu2",
            "westdown" : __DIR__"huapu1",
        ]));

        setup();
}
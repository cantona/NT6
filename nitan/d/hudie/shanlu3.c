// 山路 shanlu3.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "山路");
        set("long", @LONG
這是一條彎彎曲曲的山路，東面傳來陣陣清香，你循着清香走了
過去。
LONG );
        
        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "southdown" : __DIR__"shanlu1",
            "eastdown" : __DIR__"huapu1",
        ]));

        setup();
}
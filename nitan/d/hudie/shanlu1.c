// 山路 shanlu1.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "山路");
        set("long", @LONG
這是一條彎彎曲曲的山路，不知通向何方。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "northup" : __DIR__"shanlu3",
            "southwest" : __DIR__"kongdi", 
        ]));

        setup();
}
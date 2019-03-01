// 空地 kongdi.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "空地");
        set("long", @LONG
這裡是一片大的空地，據說當年蝴蝶谷誓師大會便是在這裡進行
的，空地右邊有一條小溪，彎彎曲曲不知通往何方。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "north" : __DIR__"niupeng",
            "northeast" : __DIR__"shanlu1",
            "northwest" : __DIR__"shanlu2",
            "southwest" : __DIR__"xiaojing2",
        ]));

        setup();
}
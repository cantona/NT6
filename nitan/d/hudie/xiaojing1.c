// 小徑 xiaojing1.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "小徑");
        set("long", @LONG
你沿著小路行了一程，蝴蝶逐漸多了起來，你更加加快腳步向前
走去。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "north" : __DIR__"xiaojing2",
            "south" : __DIR__"xiaojing",
        ]));

        setup();
}
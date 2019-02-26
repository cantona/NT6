// 小徑 xiaojing.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "小徑");
        set("long", @LONG
你走了一陣，突然發現幾隻蝴蝶向前飛去，你心裏不由一喜，向
着蝴蝶飛的方向走了過去。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "north" : __DIR__"xiaojing1",
            "south" : __DIR__"huacong1",
        ]));

        setup();
}
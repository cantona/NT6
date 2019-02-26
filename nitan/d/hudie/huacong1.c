// 花叢中 huacong1.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "花叢中");
        set("long", @LONG
這裏周圍都是嫣紅奼紫的鮮花，各種奇花異草，份外芬香。眼前
有一條小徑夾雜在鮮花叢中。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "north" : __DIR__"xiaojing",
            "out" : __DIR__"shanbi",
        ]));

        setup();
}
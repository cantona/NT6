// 後山 houshan.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "後山");
        set("long", @LONG
這裏是蝴蝶谷的後山，非常空曠，顯得很安靜，三面都是懸崖峭
壁，猶如世外桃源一般。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([
            "south" : __DIR__"huapu4",
        ]));

        setup();
}
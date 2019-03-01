// 廂房 xfang3.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "廂房");
        set("long", @LONG
這是一間不大的廂房，陳設擺放十分整齊，靠左右牆邊的地方各
有一張小床，看來是熬藥、作飯的兩個小童休息的地方。
LONG );

        set("exits", ([ 
            "west" : __DIR__"caotang",
            "south" : __DIR__"yaofang",
            "east" : __DIR__"shufang",
        ]));

        setup();
}
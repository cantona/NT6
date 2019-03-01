// liulangqiao.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "柳浪橋");
        set("long", @LONG
每當春至，站在橋上，沿湖垂柳在風中搖曳如翠浪翻空，黃鶯在
枝頭迎春嬉戲，鳴聲婉轉，故得名“浪橋聞鶯”。
LONG);
        set("exits", ([
            "southwest" : __DIR__"jujingyuan",
        ]));
        set("objects", ([
            __DIR__"npc/maque" : 2,
            __DIR__"npc/wuya" : 1,
        ]));
        set("outdoors", "xihu");
//        set("no_clean_up", 0);
	set("coor/x", 810);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
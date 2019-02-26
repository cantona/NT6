// yuhuangsj.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "玉皇山腳");
        set("long", @LONG
只見往上的山路曲折蜿延。山路旁有一座小六角亭，幾個遊人正
在亭裏歇腳。東北邊是一條青石大道，往西是上山的路。
LONG);
        set("exits", ([
            "northeast" : __DIR__"road15",
            "westup"    : __DIR__"shanlu7",
        ]));
        set("objects", ([
            __DIR__"npc/honghua1" : 2,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 800);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
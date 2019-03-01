// yuhuangshan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "玉皇山");
        set("long", @LONG
山腳有一座小亭，德意亭。不少遊客登山前或下山後都在此小歇。
山路蜿延往東向上。西邊有一條大路。
LONG);
        set("exits", ([
            "eastup"  : __DIR__"shanlu6",
            "west"    : __DIR__"road18",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 760);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
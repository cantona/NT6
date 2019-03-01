// yuhuangsd.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "玉皇山頂");
        set("long", @LONG
登上玉皇山，俯瞰山下，可以看到“八卦田”。據說這是皇帝祭
先農時親耕的籍田。山頂有福星觀，建於唐朝。廊宇旁有天一池和白
石井，並建有望湖亭。東西兩邊各有一條下山的路。
LONG);
        set("exits", ([
            "eastdown"  : __DIR__"shanlu7",
            "westdown"  : __DIR__"shanlu6",
        ]));
        set("objects", ([
            __DIR__"honghua/yu" : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 780);
	set("coor/y", -2100);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
// Room: /d/suzhou/liuyuan.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "留園");
        set("long", @LONG
留園是蘇州的一大名景之一，它以結構布局緊密、廳堂華麗宏敝、
裝飾精美典雅而享有“吳中第一名園”之譽。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"nandajie2",
                "west"  : __DIR__"hehuating",
        ]));
        set("objects", ([
                __DIR__"npc/lady1" : 1,
        ]));
	set("coor/x", 1100);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
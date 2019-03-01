#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","樹林");
        set("long", @LONG
這裡是衡山半山腰的一片樹林，據說這裡經常有野獸出沒。
LONG );

        set("objects",([
              __DIR__"npc/hunter" : 1,        
        ]));

        set("exits", ([
                "east"  :  __DIR__"shanlu6",
        ]));

        set("outdoors","henshan");
	set("coor/x", -6960);
	set("coor/y", -5540);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
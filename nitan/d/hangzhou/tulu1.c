// tulu1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "土路");
        set("long", @LONG
路旁一條小溪。溪水嘩嘩地流着，不時有魚兒(fish)躍出水面。
溪旁幾個男孩正低着頭專心在釣魚。
LONG);
        set("exits", ([
            "southwest"     : __DIR__"shanlu5",
            "northeast"     : __DIR__"maojiabu",
        ]));
        set("objects", ([
            __DIR__"npc/boy" : 2,
        ]));
        set("item_desc", ([
            "fish" : "“譁”一條大魚躍水而出，“噗”的一聲又掉回水裏。濺得男孩一身水。\n",
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 750);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
// Room: /d/xiangyang/caodi3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "草地");
        set("long", @LONG
這是襄陽城外的草地。蒙古兵進犯以來，這裏的百姓全進城了，
蒙古兵馳騁來去，以為牧場，塵土飛揚，甚是囂張。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "south"  : __DIR__"northgate2",
                "north"  : "/d/luoyang/guandaos6",
        ]));
        set("objects", ([
                __DIR__"npc/menggubing" : 2,
        ]));
        set("coor/x", -7810);
	set("coor/y", -700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
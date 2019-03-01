// Room: /d/xiangyang/caodi2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "草地");
        set("long", @LONG
這是襄陽城外的草地。蒙古兵進犯以來，這裡的百姓全進城了，
蒙古兵馳騁來去，以為牧場，塵土飛揚，甚是囂張。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "east"  : __DIR__"northgate2",
        ]));
        set("objects", ([
                __DIR__"npc/menggubing" : 2,
        ]));
        set("coor/x", -7820);
	set("coor/y", -710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
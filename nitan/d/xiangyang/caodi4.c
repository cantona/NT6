// Room: /d/xiangyang/caodi4.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "草地");
        set("long", @LONG
這是襄陽城外的草地。蒙古兵進犯以來，這裡的百姓全進城了，
這裡幾十裡都沒了人煙。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "west"  : __DIR__"southgate2",
        ]));

        set("objects", ([
                CLASS_D("hu") + "/cheng" : 1,
        ]));

        set("coor/x", -7810);
	set("coor/y", -820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
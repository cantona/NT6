// Room: /d/xiangyang/caodi5.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "草地");
        set("long", @LONG
這是襄陽城外的草地。蒙古兵進犯以來，這裏的百姓全進城了，
這裏幾十裏都沒了人煙。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"southgate2",
        ]));
        set("coor/x", -7830);
	set("coor/y", -820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
// Room: /d/xiangyang/caodi3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "草地");
        set("long", @LONG
這是襄陽城外的草地。蒙古兵進犯以來，這裏的百姓全進城了，
雖然蒙古兵沒來到南門，但肅殺氛圍絲毫不減。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"southgate2",
                "south"  : "/d/wudang/wdroad5",
                //"west"   : __DIR__"hunanroad1", 取消了這裏到鐵掌山的路徑
        ]));
        set("coor/x", -7820);
	set("coor/y", -830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
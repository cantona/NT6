// Room: /huanghe/yinpanshui.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "營盤水");
        set("long", @LONG
這裡是當年蒙恬修長城時駐軍的地方，蒙恬治軍有方，當年他親
自帶人在駐地挖了好幾口甜水井，使士卒們不用喝又苦又澀的咸水，
後來此地的百姓們叫這裡為營盤水，稱這裡的井為“蒙恬井”。
LONG );
        set("exits", ([
                "southwest" : __DIR__"bingcao",
                "southeast" : __DIR__"shimen",
                "northeast" : __DIR__"guchangcheng",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16080);
	set("coor/y", 4280);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
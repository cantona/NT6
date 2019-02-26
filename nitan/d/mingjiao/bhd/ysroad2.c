// ysroad2.c 巖石路
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIR"巖石路"NOR);
        set("long", @LONG
巖石路皆由火山灰堆成，厲時久，地面十分堅硬。在這裏已可以
看見那縷黑煙之中竟有紅火光不斷的噴出，原來黑煙之處是一座活火
山，走到這裏已感到一絲的熱氣撲面而來，再走十多里路就到達火山
腳下了。
LONG );
	set("exits",([
		"west" : __DIR__"hsjiao",
		"east" : __DIR__"ysroad1",
	]));
	set("outdoors","冰火島");
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "west"){ 
	   me->set_leader(0);
           me->receive_damage("jing", 100);
           me->receive_damage("qi", 100);
         }
         return ::valid_leave(me, dir); 
}

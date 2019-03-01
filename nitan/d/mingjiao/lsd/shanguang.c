// /d/mingjiao/lsd/shanguang.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", GRN"山崗"NOR);
        set("long", @LONG
只見山崗上稀稀落落長著一些花草和風棵不知名的樹木，樹木不
高，但卻長得蔥翠，山崗的另一側是一座小石山。往西而下是岸邊，
往東而下是山峰腳下。往北而下是靈蛇谷。
LONG );
	set("exits", ([ 
  		"westdown" : __DIR__"anbian",
		"northdown" : __DIR__"lsgu",
	]));
	set("outdoors","靈蛇島");
	setup();
}

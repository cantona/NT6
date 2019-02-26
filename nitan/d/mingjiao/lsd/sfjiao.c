// /u/qingyun/lsd/sfjiao.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", GRN"山峯腳下"NOR);
        set("long", @LONG
這裏四周長着許多長草，此島名為『靈蛇島』，島上定然長蟲特
多，不時會有毒蟲竄出。在這裏你只能盡往光禿的山石處落腳。往南
而上是山峯頂部，依稀可見一座茅屋座落其中。
LONG );
	set("exits", ([ 
  		"south" : __DIR__"lsgu",
  		"northup" : __DIR__"shanfeng",
	]));
	set("objects",([
            "/clone/beast/snake"  :       1,
	]));
	set("outdoors","靈蛇島");
	setup();
}

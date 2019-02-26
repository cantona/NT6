///u/qingyun/lsd/shanfeng.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", YEL"山峯"NOR);
        set("long", @LONG
沿着山坡而行，向北而上是一座山峯，山峯座落在靈蛇島的北部，
在山峯之東，可以看見一間孤零零的茅屋。
LONG );
	set("exits", ([
	  	"southdown" : __DIR__"sfjiao",
	]));
	set("objects",([
                CLASS_D("mingjiao") + "/huiyue" : 1,
                CLASS_D("mingjiao") + "/liuyun" : 1,
                CLASS_D("mingjiao") + "/miaofeng" : 1,
	]));
	set("outdoors","靈蛇島");
	setup();
}

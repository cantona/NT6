// huoshan1.c 火山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIR"火山"NOR);
        set("long", @LONG
到這裏一什麼也看不見了。。。。只是有火燒身的感覺。
LONG );
	set("exits",([
		"northup" : __DIR__"huoshan2",
		"eastdown" : __DIR__"hsjiao",
	]));
	set("outdoors","冰火島");
	setup();
}

int valid_leave(object me, string dir)
{
      if (dir == "northup")
        me->set_leader(0);
      return ::valid_leave(me, dir); 
}

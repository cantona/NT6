// huoshan2.c 火山口
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIR"火山口"NOR);
        set("long", @LONG
到了這裏就等於到了地獄了。
LONG );
	set("exits",([
		"southdown" : __DIR__"huoshan1",
	]));
        set("outdoors","冰火島");
	setup();
}

void init()
{
        object me =this_player();
        me->set_temp("die_reason", "誤入火山口燒死");
       	me->die();
}

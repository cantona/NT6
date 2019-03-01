// hsjiao.c 火山腳下
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIR"火山腳下"NOR);
        set("long", @LONG
你越走越熱，不覺已至火山腳下。此時已可看到大火從火山中怒
噴而出，到這裡你雖然是只穿單衣也是頂受不住，不覺已是口幹舌燥，
遍身大汗，但見身旁已無一株樹木花草，只余光禿禿、黃焦焦的巖石。
LONG );
	set("exits",([
		"east"	: __DIR__"ysroad2",
		"westup" : __DIR__"huoshan1",
	]));
	set("outdoor","冰火島");
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "westup"){
	   me->set_leader(0);
           me->unconcious();
        }
        return ::valid_leave(me, dir); 
}

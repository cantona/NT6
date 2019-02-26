
inherit ITEM;
#include <ansi.h>
int do_fu(string arg);
void create()
{
   set_name(HIR"死人頭"NOR, ({ "head"}));
   set_weight(100);
   set("unit", "顆");
   set("long","這是一顆死人頭,吃了他(eat head)會變得很邪惡.\n");
   set("value", 50000);
   
}

void init()
{
	add_action("do_fu","eat");
}
int do_fu(string arg)
{
	object me,ob;int i;
	ob=this_object();me=this_player();
	if(!arg||(arg!="head"&&arg!="頭"))
		return notify_fail("你要吃什麼?\n");
	me->add("bellicosity",100);
	message_vision("$N抓起一顆[死人頭]狂啃起來，滿臉都透露着邪氣。\n",me);
	destruct(ob);
	return 1;
}

inherit ITEM;
#include <ansi.h>
int do_fu(string arg);
void create()
{
   set_name(HIR"拼命丹"NOR, ({ "pinming dan","dan" }));
   set_weight(100);
   set("unit", "顆");
   set("long","這是一顆由多種不知名物品煉成的丹藥,服用(fu dan)它不知道會發生什麼.\n");
   set("value", 50000);
   
}

void init()
{
	add_action("do_fu","fu");
}
int do_fu(string arg)
{
	object me,ob;int i;
	ob=this_object();me=this_player();
	if(!arg||(arg!="dan"&&arg!="丹"))
		return notify_fail("你要服用什麼?\n");
	message_vision("$N服下了一顆[拼命丹].\n",me);
if(random(10)>6)
{
message_vision("$N感覺到內力似乎增加了.\n",me);
me->add("max_force",15+random(30));
}
else
me->set("gin",-1);
	destruct(ob);
	return 1;
}
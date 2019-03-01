
inherit ITEM;
#include <ansi.h>
int do_fu(string arg);
void create()
{
   set_name(HIR"養顏丹"NOR, ({ "yangyan dan","dan" }));
   set_weight(100);
   set("unit", "顆");
   set("long","這是一顆由多種美容物質提煉而成的丹藥,服用(fu dan)它能美容.\n");
   set("value", 150000);
   
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
                            if(me->query("per")>30)
		return notify_fail("你都這麼美了，還養什麼顏，不讓別人活了啊！\n");
	me->add("per",1);
	message_vision("$N服下了一顆[養顏丹]，感覺到自己變美了。\n",me);
	destruct(ob);
	return 1;
}
#include <ansi.h>
inherit ITEM;
void create()
{
     	set_name(HIW"九花玉露丸"NOR, ({ "jiuhuayulu wan","wan"}));
     	set_weight(100);
     	if( clonep() )
            	set_default_object(__FILE__);
     	else 
	{
             	set("long", "九花玉露丸是桃花島黃藥師的療傷聖藥，只要還有一口氣在，就能把命救回來。\n");
             	set("unit", "顆"); 
            	set("no_get",1);
            	set("no_give",1);   
             	set("value",100000);

    	}
    	setup();
}

void init()
{
    	if (environment()==this_player())
     	add_action("do_eat", "eat");
}
int do_eat(string arg)
{
  	object me = this_player();
  	int maxneili,neili;
    	neili=query("neili", me);
    	maxneili=query("max_neili", me);
  	
	if(!id(arg)) 
		return 0;
    
addn("combat_exp", random(5000), 	me);
 
//精力
     set("jingli",query("max_jingli",  me), 	me);
//精神
      set("eff_jing",query("max_jing",  me), 	me);
     set("jing",query("max_jing",  me), 	me);
//內力
     set("neili",query("max_neili",  me), 	me);
//氣血
     set("eff_qi",query("max_qi",  me), 	me);
     set("qi",query("max_qi",  me), 	me);
    
  	message_vision(HIR"$N吃下一顆九花玉露丸，所有傷勢瞬間痊癒，精神也健旺了許多。\n"NOR,me);
     	destruct(this_object());
     	return 1;
}

#include <ansi.h>
inherit ITEM;
void create()
{
      	set_name(YEL"菩提子"NOR, ({ "puti zi","zi"}));
     	set_weight(100);
     	if( clonep() )
            	set_default_object(__FILE__);
      	else 
	{       
         	set("unit", "顆"); 
            	set("no_get",1);
             	set("no_give",1);
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
    
  	if(!id(arg)) return 0;
  	if(me->is_busy()) return notify_fail("你上一個動作還沒有完成。\n");
        if( time()-query("eat_drug/putizi", me)<1800 )
                return notify_fail("你覺得現在內息未定，經脈隱隱還能感到真氣衝蕩，不敢貿然服食。\n");

        addn("max_neili", 10+random(15), me);message_vision(HIG"$N拿起菩提子吃了下去,感覺丹田傳來一陣陣熱意,內力修為好像有所增加!!!!!\n"NOR,me);
      set("eat_drug/putizi", time(), me);
      	destruct(this_object());
      	return 1;
}

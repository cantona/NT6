#include <ansi.h>
inherit ITEM;
void create()
{
      	set_name(HIR"玉清散"NOR, ({ "yuqing san","san"}));
      	set_weight(100);
      	if( clonep() )
          	set_default_object(__FILE__);
      	else 
	{       
           	set("unit", "包"); 
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

        if( time()-query("eat_drug/yuqingsan", me)<2400 )
                return notify_fail("你剛服用過藥時間不久，需藥性發揮完效用以後才能繼續服用。\n"); 
    
        addn("max_jingli", 10+random(5), me);message_vision(HIB"$N拿起玉清散吃了下去,感覺自己的精力有所增加。\n"NOR,me);
      set("eat_drug/yuqingsan", time(), me);
     	destruct(this_object());
      	return 1;
}

#include <ansi.h>
inherit ITEM;
void create()
{
    	set_name(HIG"疾風驟雨丹"NOR, ({ "jifengzhouyu dan","dan"}));
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

  	if (!me->is_fighting())
		return notify_fail("你現在沒有在戰鬥中，吃了也沒什麼用。\n");

	me->start_busy(0);
  	message_vision(HIG"$N吞下一顆疾風驟雨丹，身如疾風，脱離了忙亂狀態，轉身一招又攻了過來！\n"NOR,me);
      	destruct(this_object());
      	return 1;
}

#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void finish(object me, object ob);

void create()
{
        set_name(HIC"藥鋤"NOR, ({ "yao chu"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一把藥鋤，用來在地裏挖掘（wajue）根類藥材。\n");
                set("unit", "把"); 
                set("no_get",1);
                set("no_drop",1);             
                set("no_put",1);
                set("no_give",1);   
                set("value",100000);
        }
        init_hammer(20,2);
    setup();
}

void init()
{
    	if (environment()==this_player())
        	add_action("do_wajue", "wajue");
}

int do_wajue()
{
  	object me = this_player();
  	object ob = this_object();
    	object weapon;

    	if( !objectp(weapon=query_temp("weapon", me) )
    	 || query("id", weapon) != "yaochu" )
    	if( !objectp(weapon=query_temp("secondary_weapon", me) )
    	 || query("id", weapon) != "yaochu" )
        	return notify_fail("你手中得拿着工具才能挖藥。\n");

  	if( !query("outdoors", environment(me)) )
  	return notify_fail("你在房間裏挖個什麼勁，要挖去外面挖！\n");

  	if(!sscanf(base_name(environment(me)),"/d/wudang/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/quanzhen/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/hengshan/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/taishan/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/huashan/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/tiezhang/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/gaochang/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/kunlun/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/songshan/%*s"))
  	return notify_fail("只有名山大川，風景秀麗之處才可以挖掘藥材!\n");
  	
	if(me->is_busy())
  	return notify_fail("你現在正忙,等一下再挖吧!\n");

  	if( query("wajue", environment(me))>time() )
  	return notify_fail("這裏剛剛被人挖掘過，你等一會再來吧!\n");

  	me->start_busy(5);

	me->start_call_out( (: call_other, __FILE__, "finish", me, ob :), 3);
	message_vision( HIB"$N拿起藥鋤，在地上一陣瘋狂亂刨！\n"NOR, this_player());
	return 1;
}

void finish(object me, object ob)
{
  	object gen;

  	if(random(5)>4) 
	{
  		me->start_busy(2);
  		message_vision( HIW"$N感到好像挖到什麼東西了,仔細一看原來是石塊!\n"NOR, this_player());

   	}
  
   else if ( random(20)<2) 
	{
  		message_vision( HIG"$N突然聽到『喀嚓一聲』,鋤頭挖斷了!\n"NOR, this_player());
  		destruct(ob);
  	}
	else
   	{
addn("neili", -(query("neili", me)/10), 		me);
   addn("qi", -(query("qi", me)/10), 		me);
   addn("jing", -(query("jing", me)/10), 		me);
   set("wajue", time()+120, 		environment(me));

		gen=new(__DIR__"/yao/genlei");
   		gen->move(me);
  		me->start_busy(2);

   		message_vision(HIR"$N拿着藥鋤刨地三尺，挖出了一根"+gen->name()+HIR"！\n"NOR, this_player());
	}
}
#include <ansi.h>
#include <weapon.h>
inherit AXE;

void finish(object me, object ob);

void create()
{
        set_name(MAG"小斧頭"NOR, ({ "fu tou"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一把採藥人常用的小斧頭，用來砍伐（kanfa）木類藥材。\n");
                set("unit", "把"); 
                set("no_get",1);
                set("no_drop",1);             
                set("no_put",1);
                set("no_give",1);   
                set("value",100000);
        }
        init_axe(20,2);
    setup();
}

void init()
{
    	if (environment()==this_player())
        	add_action("do_kanfa", "kanfa");
}

int do_kanfa()
{
  	object me = this_player();
  	object ob = this_object();
    	object weapon;

    	if( !objectp(weapon=query_temp("weapon", me) )
    	 || query("id", weapon) != "futou" )
    	if( !objectp(weapon=query_temp("secondary_weapon", me) )
    	 || query("id", weapon) != "futou" )
        	return notify_fail("你不拿著工具，找到藥材也砍不下來啊！\n");

  	//if( !query("outdoors", environment(me)) )
  	//return notify_fail("你在房間裡能砍到什麼？砍人嗎？\n");

    if( strsrch(query("short", environment(me)),"林")<0
     && strsrch(query("short", environment(me)),"木")<0
         && strsrch(query("short", environment(me)),"樹")<0
              && strsrch(query("long", environment(me)),"林")<0
              && strsrch(query("long", environment(me)),"木")<0
              && strsrch(query("long", environment(me)),"樹")<0 )


  	return notify_fail("只有樹林裡才有可能找到藥用樹木!\n");
  	
	if(me->is_busy())
  	return notify_fail("你現在正忙,等一下再砍吧!\n");

  	if( query("kanfa", environment(me))>time() )
  	return notify_fail("為了環境保護，請不要濫伐樹木!\n");

  	me->start_busy(5);

	me->start_call_out( (: call_other, __FILE__, "finish", me, ob :), 3);
	message_vision( HIB"$N四處張望，看看能不能找到有用的樹木。\n"NOR, this_player());
	return 1;
}

void finish(object me, object ob)
{
  	object mu;

  	if(random(5)>4) 
	{
  		me->start_busy(2);
  		message_vision( HIW"尋找一番之後$N一無所獲，只得失望地嘆了口氣。\n"NOR, this_player());

   	}
  
  	else if ( random(20)<2) 
	{
  		message_vision( HIG"$N好不容易找到一棵有用的樹木，砍了兩下卻發現斧頭崩壞了!\n"NOR, this_player());
  		destruct(ob);
  	}
	else
   	{
addn("neili", -(query("neili", me)/10), 		me);
   addn("qi", -(query("qi", me)/10), 		me);
   addn("jing", -(query("jing", me)/10), 		me);
   set("kanfa", time()+20, 		environment(me));

		mu=new(__DIR__"/yao/mulei");
   		mu->move(me);
  		me->start_busy(2);

   		message_vision(HIR"$N突然發現一棵"+mu->name()+HIR"樹，連忙取出斧頭，費盡全身力氣將其砍伐下來。\n"NOR, this_player());
	}
}

#include <ansi.h>
inherit ITEM;
void create()
{
	set_name(HIY"普通鼎爐"NOR, ({ "putong dinglu", "dinglu" }));
	set_weight(500);
	set_max_encumbrance(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "個");
		set("long", "一個小小圓圓的普通鼎爐，藥房常常用它來煎藥煉丹。\n");
		set("value", 1000000);
             	set("no_get",1);
            	set("no_give",1);
	}
}

int is_container() { return 1; }

void init()
{
    	if (environment()==this_player())
        	add_action("do_liandan", "liandan");
}


int do_liandan()
{  	
	object me = this_player();
	object ob = this_object();
	object *yao;
	int yaoxing, i, lv;

	if( !query("peifang", me) || !query("mubiao", me) )
        	return notify_fail("你還沒拿到配方呢，煉不出來什麼東西。\n");

	yao = all_inventory(ob);
	lv = sizeof(yao);
	if (lv==0)
        	return notify_fail("先把藥材放到鼎爐裏面再煉吧。\n");

	if (me->is_busy())
        	return notify_fail("你現在正忙着呢。\n");

	if( query_temp("fire", me) )
        	return notify_fail("先把上次的丹煉好了在幹別的吧。\n");

    	for(i=0; i<lv; i++) 
	{
        	if( !query("yaoxing", yao[i]) )
        		return notify_fail("怎麼什麼亂七八糟的東西都往爐子裏放？\n");

		yaoxing+=query("yaoxing", yao[i]);
		destruct(yao[i]);
       }

   	message_vision(MAG"$N按照胡青牛給的配方，把藥材放進鼎爐，專心致志地煉製。\n"NOR, this_player());

	me->start_busy(8);
set_temp("fire", 1, 	me);
set_temp("yaoxing", yaoxing, 	me);
set_temp("lv", lv, 	me);

	call_out("fire",8, me);
	return 1;
}

void fire(object me)
{
	int fire;

	if( query("neili", me)<40000 )
	{
		message_vision (HIY"過了一會，爐中的温度似乎有些下降，$N見狀連忙添了幾根柴禾。\n"NOR,me);
	}
	else if( query("neili", me)<200000 )
	{
		message_vision (HIY"過了一會，爐中的温度似乎有些下降，$N見狀連忙催動內力，爐中温度有所回升。\n"NOR,me);
addn("neili", -10000, 		me);
addn_temp("fire", 1, 		me);
	}
	else
	{
		message_vision (HIY"過了一會，爐中的温度似乎有些下降，$N見狀連忙催動內力，鼓動"+HIR+"三味真火"+HIY+"，爐中火焰一下旺了起來。\n"NOR,me);
addn("neili", -50000, 		me);
addn_temp("fire", 2, 		me);
	}
    	me->improve_skill("liandan-shu", me->query_int()*100+random(1000));
    addn("combat_exp", 500+random(500), 	me);
    addn("potential", 100+random(200), 	me);
	tell_object(me,WHT"在煉丹中你的經驗潛能有所增長，煉丹技術也有提高。\n"NOR);

	me->start_busy(5);
    	switch ( random(2) ) 
    	{

    		case 0:
     			call_out("fire",8, me);
		break;

    		case 1:
     			call_out("shoudan",8, me);
		break;

    	}

}

void shoudan(object me)
{

	object dan;

	if( query_temp("yaoxing", me) != query("peifang", me) )
	{
		dan = new(__DIR__"/dan/wumingdan");
		dan->move(me);
   		message_vision(HIW"由於配方不對，$N煉出來一個無名藥品。\n"NOR, this_player());
	}

	else if( random(query_temp("fire", me))<random(query_temp("lv", me)) )
	{
		dan = new(__DIR__"/dan/wumingdan");
		dan->move(me);
   		message_vision(HIW"儘管配方正確，但是由於人品不佳，$N煉出來一個無名藥品。\n"NOR, this_player());
 	}
	else
	{
		dan=new(__DIR__"/dan/"+query("mubiao", me));
		dan->move(me);
   		message_vision(HIR"歷盡千辛萬苦，$N終於煉出一顆珍貴的"+query("name", dan)+HIR"！\n"NOR,this_player());
   		message_vision(HIB"$N連忙把辛苦煉出的丹藥收在懷裏。\n"NOR, this_player());

 	}
delete_temp("yaoxing", 	me);
delete_temp("fire", 	me);
delete_temp("lv", 	me);

delete("peifang", 	me);
delete("mubiao", 	me);
}
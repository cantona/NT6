#include <ansi.h>
#define GIFT_NAME "粽子"
// 本次的禮物發放
#define THIS_GIFT_USER "2013_端午"
// 上次的禮物發放
#define LAST_GIFT_USER "2013_測試禮物5"

inherit ITEM;

void create()
{
	set_name(HIR + GIFT_NAME + NOR, ({"zong zi","zong", "zi"}));
	set_weight(200);
	set("unit", "件");
	set("long",HIG"NT巫師特地為大家制作的端午粽子，看起來很美味的樣子，\n品嘗(eat)一下是什麼味道？\n"NOR);
	set("value", 0);
	set("no_give",1);
	set("no_get",1);
	set("no_put",1);
	set("no_drop",1);
        setup();
}

void init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	object me;
	me = this_player();
	
	if (!id(arg))
		return notify_fail("你要吃什麼？\n");
	
	if (query(THIS_GIFT_USER, me) && query("gift_dw", me) == (CHINESE_D->chinese_time(7, ctime(time()))) )  
	{
		tell_object(me,HIY "端午節使者突然在一陣煙霧中出現，一把抓過你手中的粽子：“你今天已經吃過了吧？可別貪心哦！”說完將粽子收走了。\n"NOR);
		destruct(this_object());	
		return 1;
	}
	
	if ( (CHINESE_D->chinese_time(7, ctime(time()))) != "2013/06/12" &&
		(CHINESE_D->chinese_time(7, ctime(time()))) != "2013/06/13" &&
		(CHINESE_D->chinese_time(7, ctime(time()))) != "2013/06/14" ) { //限定在這3天之間使用有效
		tell_object(me,HIY "端午節使者突然在一陣煙霧中出現，一把抓過你手中的粽子：“你這粽子已經過期了吧？”說完將粽子收走了。\n"NOR);
		destruct(this_object());	
		return 1;
	} else {
		tell_object(me, HIC "你看著美味的粽子，想也不想一口吞進了肚裡！\n" NOR);     	
		delete(LAST_GIFT_USER, me);//刪除上次派禮物生成的參數，增加本次參數，確保每位玩家只能用一次。
		set(THIS_GIFT_USER, 1, me);
		set("gift_dw", (CHINESE_D->chinese_time(7, ctime(time()))), me);
		addn("combat_exp", 10000, me);
		addn("potential", 10000, me);
		addn("max_neili", 100, me);
		addn("max_jingli", 100, me);
		tell_object(me,HIC "你感覺自己身體發生了明顯的變化－－長胖了！\n" NOR);     	
		destruct(this_object());
	}
	return 1;
}

void owner_is_killed() { destruct(this_object()); }

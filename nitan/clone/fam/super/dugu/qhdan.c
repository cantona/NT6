#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIG "千回丹" NOR, ({"qianhuidan"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIC "傳說神農氏曾煉丹千次，終成此丹！\n" + 
        	                "服食(fushi qianhuidan)後，30分鐘內可額外提升研究次數50次。\n" HIR
        	                /*"擁有者：擁有者ID*/"\n" NOR);
                set("unit", "顆");
                set("owner", "擁有者ID"); // 綁定擁有者
	        set("no_drop", 1);set("no_store", 1);set("no_sell", 1);
        }
        setup();
}

/*
void init()
{
        add_action("do_use", "fushi");       
}
*/

int do_use(string arg)
{
	object ob, me;
	
	me = this_player();

	if (! arg || arg != query("id"))
		return notify_fail("你要服食什麼？\n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("你身上沒有這個東西！\n");
/*
	if( query("owner", ob) != query("id", me) )
		return notify_fail(ob->name() + NOR "已經于其他玩家綁定！\n");
*/

	if( !query("add_yanjiu_times50", me) || 
	query("add_yanjiu_times50", me)-time() <= 0 )
set("add_yanjiu_times50", time()+1800, 		me);
	else
	{
addn("add_yanjiu_times50", 1800, 		me);
	}


	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "後，30分鐘內研究次數額外提高50次！\n");
	tell_object(me,HIG"目前該效果還剩余時間："+sprintf("%d",query("add_yanjiu_times50", me))+"秒。\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}

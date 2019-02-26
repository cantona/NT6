#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIR "九轉丹" NOR, ({"jiuzhuandan"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIC "九轉丹乃是神農氏通過九九八十一次煉製而成。\n" + 
        	                "服食(fushi jiuzhuandan)後，15分鐘內可額外提升研究效率3%。\n" HIR
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
		return notify_fail(ob->name() + NOR "已經於其他玩家綁定！\n");
*/

	if( !query("add_yanjiu_xiaolv15", me) || 
	query("add_yanjiu_xiaolv15", me)-time() <= 0 )
set("add_yanjiu_xiaolv15", time()+900, 		me);
	else
	{
addn("add_yanjiu_xiaolv15", 900, 		me);
	}

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "後，15分鐘內研究效率額外提高3%！\n");
	tell_object(me,HIG"目前該效果還剩餘時間："+sprintf("%d",query("add_yanjiu_xiaolv15", me))+"秒。\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}

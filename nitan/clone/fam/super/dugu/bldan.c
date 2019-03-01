#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIG "百龍丹" NOR, ({"bailong dan"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIC "百龍丹乃使用數百條龍血煉化而成！\n" + 
        	                "服食(fushi bailongdan)後可永久提升讀書寫字1級。\n" HIR
        	                /*"擁有者：擁有者ID*/"\n" NOR);
                set("unit", "顆");
                set("owner", "擁有者ID"); // 綁定擁有者
	        set("no_drop", 1);set("no_store", 1);set("no_sell", 1);
        }
        setup();
}

void init()
{
        add_action("do_use", "fushi");       
}

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
   me->add_skill("literate", 1);

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "後，讀書寫字提升1級！\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}
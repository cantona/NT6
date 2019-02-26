#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIC "百魄仙丹" NOR, ({"baipoxiandan"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIC "百魄仙丹乃一百條魂魄聚集而成的內丹！\n" + 
        	                "服食(fushi baipoxiandan)後可永久提升基本輕功1級。\n" HIR
        	                "擁有者：xiaxu\n" NOR);
                set("unit", "顆");
                set("owner", "xiaxu"); // 綁定擁有者
	        set("no_drop", 1);set("no_give", 1);set("no_store", 1);set("no_sell", 1);
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
		
	if (ob->query("owner") != me->query("id"))
		return notify_fail(ob->name() + NOR "已經於其他玩家綁定！\n");
	
	me->set_skill("dodge", me->query_skill("dodge", 1) + 1);
	
	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "後，基本輕功提升1級！\n");
	
	log_file("super/"+ filter_color(query("name")) , me->query("id") + " at " + ctime(time()) + " 使用" + ob->name() + "。\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}
int query_autoload()
{
	return 1;
}
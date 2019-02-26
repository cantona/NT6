#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIG "仙魂草" NOR, ({"xianhuncao"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIG "仙魂草長於崑崙山溶洞之中，傳説吸收了修仙之人的魂魄！\n" + 
        	                "服食(fushi xianhuncao)後可永久提升武學修養1級。\n" HIC
        	                "擁有者：hsdm\n" NOR);
                set("unit", "束");
                set("owner", "hsdm"); // 綁定擁有者
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
	
	me->set_skill("martial-cognize", me->query_skill("martial-cognize", 1) + 1);

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "後，武學修養提升1級！\n");
	
	log_file("super/"+ filter_color(query("name")) , me->query("id") + " at " + ctime(time()) + " 使用" + ob->name() + "。\n");
	
	me->save();
	
	destruct(ob);
	
	return 1;
}

int query_autoload()
{
	return 1;
}
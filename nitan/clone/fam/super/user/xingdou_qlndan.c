#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY "麒麟內丹" NOR, ({"qilinneidan"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {  
        	set("long", HIC "傳說麒麟內丹乃修煉千年火麒麟的內丹，擁有無邊的力量。\n" + 
        	                "服食(fushi qilinneidan 技能id)後可永久提升非知識類技能1級。\n" HIC
        	                "擁有者：xingdou\n" NOR);
                set("unit", "顆");
                set("owner", "xingdou"); // 綁定擁有者
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
	string skid;
	
	me = this_player();

	if (! arg )
		return notify_fail("你要服食什麼？\n");

	if (! sscanf(arg, "qilinneidan %s", skid))
		return notify_fail("指令格式：fuyong qilinneidan 技能ID\n");

	arg = "qilinneidan";

	if (! objectp(ob = present(arg, me)))
		return notify_fail("你身上沒有這個東西！\n");

	if (ob->query("owner") != me->query("id"))
		return notify_fail(ob->name() + NOR "已經于其他玩家綁定！\n");

	if (! me->query_skill(skid, 1))
		return notify_fail("你沒有這個技能，請確認輸入是否正確！\n");
	
	if (skid == "zuoyou-hubo")
		return notify_fail("左右互博不能提升！\n");

	if (("/kungfu/skill/" + skid)->type() == "knowledge")
		return notify_fail("知識類技能不能提升！\n");

	if (("/kungfu/skill/" + skid)->type() != "martial")
		return notify_fail("這項技能未定義類型不能提升！\n");

	me->set_skill(skid, me->query_skill(skid, 1) + 1);

	tell_object(me, HIG "恭喜！你服下" + ob->name() + HIG "後，" + to_chinese(skid) + "提升1級！\n");
	
	log_file("super/"+ filter_color(query("name")) , me->query("id") + " at " + ctime(time()) + " 使用" + ob->name() + 
	                                                "提升技能：" + to_chinese(skid) + "。\n");

	me->save();
	
	destruct(ob);
	
	return 1;
}
int query_autoload()
{
	return 1;
}
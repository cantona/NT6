// Budai.c
// Creator : Numa@Sj 00-6-3

#include <ansi.h>
inherit ITEM;

#define SHU "/d/city/obj/whdmd-book"

void create()
{
        set_name("布袋", ({"bu dai", "dai"}));
        set_weight(2000);
        set_max_encumbrance(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一個破舊的布袋。\n");
                set("unit", "個");
                set("no_get", 1);
                set("no_steal", 1);
                set("no_give", 1);
                set("fill_lime", 1);
        }
        setup();
}

int is_container() { return 1; }

void init()
{
	add_action("do_sa","sa");
	add_action("do_put","put");
}

int do_put(string arg)
{
        string str;

        if (!arg) return 0;
        if (sscanf(arg,"%s in dai",str) == 1 || sscanf(arg,"%s in bu dai",str) == 1) {
                if (str != "shihui")
                        return notify_fail("這樣東西放不進去。\n");
        }
        return 0;
}

int do_sa(string arg)
{
	object me = this_player();
	object ob = this_object();
	object ob1, ob2, ob3;
	string msg;
	
	if (!(ob1 = present("shihui", ob)))
		return notify_fail("袋裏又沒石灰，你撒啥？！\n");

	if (!arg)
		return notify_fail("你想要用石灰粉幹什麼?\n");

	if (arg = "shi song"
	 && ob2 = present("shi song",environment(me))
	 && ob3 = present("mao shiba",environment(me))) {
		if (!me->query_temp("mao18/passed4"))
			return notify_fail("人家打架呢，你瞎攙和啥！\n");
		msg = HIW"$N趁$n不備，從布袋中掏出石灰粉，猛的撒向$n的眼睛！\n"NOR;
		destruct(ob1);
		call_out("do_attack", 1, me, ob2, ob3, msg);
		return 1;
	}
	else
		return notify_fail("石灰粉如何能夠去攻擊人家？！\n");
}

int do_attack(object me, object ob2, object ob3, string msg)
{
          ob2 = present("shi song",environment(me));
	if (random(me->query_str()) > 20 && !me->query("fail")) {
		msg += RED"$n募地白影晃動，無數粉末衝進眼裏，鼻裏，口裏，一時氣為之窒，跟着雙\n"+
			"眼劇痛，猶似萬枚鋼針同時刺一般，待欲張口大叫，滿嘴粉末，連喉頭嗌住了，\n"+
			"再也叫不出聲來。\n"NOR;
		msg += CYN"$N隨手撿起地上單刀，順手插入了$n肚中。\n"NOR;
		message_vision(msg, me, ob2);
		ob2->die();
		me->delete_temp("mao18/passed4");
		me->set("mao18/pass",1);
		remove_call_out("do_finish");
		call_out("do_finish", 2, me, ob3);
		return 1;
	}
	else {
		log_file("quest/wuhu",sprintf("%8s%-18s從茅十八處學得五虎斷門刀，失敗，福：%d。\n",
			me->name(1), "("+capitalize(me->query("id"))+")", me->query("kar") ), me);
		me->set("mao18/fail", 1);
		msg += HIR"誰知卻撒了個空，自己也摔了一交。\n"NOR;
		message_vision(msg, me, ob2);
		return 1;
	}
}

int do_finish(object me, object ob)
{
	object ob1;
	
	tell_object(me,HIY"茅十八道：“你為什麼用石灰撒在那史鬆的眼裏？”聲音嚴厲，神態更是兇惡。\n\n"+
			"    你心中十分害怕，當下茅十八便將撒石灰、下蒙汗藥等這些江湖人所不齒的卑鄙手段\n"+
			"告訴了你。隨後又説：“我這裏有一本我派刀法的祕籍，你拿去自行好好鑽研。只要你能\n"+
			"勤學苦練，將來未始不能練成一身好武藝。咱們後會有期了！”説完轉身離去了。\n"NOR);
	ob1 = new(SHU);
	ob1->move(me);
	ob1->set_temp("mao18/book",me->query("id"));
	log_file("quest/wuhu",sprintf("%8s%-18s從茅十八處學得五虎斷門刀，福：%d。\n",
		me->name(1), "("+capitalize(me->query("id"))+")", me->query("kar") ), me);
	if (ob) destruct(ob);
	return 1;
}

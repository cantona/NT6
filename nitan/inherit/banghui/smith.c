// /banghui/smith.c
// 幫派的鐵匠
// by Find.

#include <ansi.h>
#include <weapon.h>
#include <mine_def.h>
#include <mangle.h>
#include <self.h>
#define WEAPON_VALUE	500	/* 每點殺傷力5兩銀子。*/
#define ARMOR_VALUE	200
#define KEY_VALUE	10000	/* 配家門鑰匙，1 gold 一把 */
#define MIN_FEE		200	/* 修理兵器最低的費用 */
#define MAX_SELL_RATE	80

inherit NPC;
inherit F_SAVE;

string query_save_file()
{
	if(!clonep())
		return 0;
	return base_name("this_object()");
}

protected int sell_rate = 50;	// 默認為半價收購
protected mapping make_weapon_ability = ([]);
protected nosave int do_nothing;
protected nosave object master;
protected nosave string b_id, b_name;
protected nosave string *can_epurate = ({
	IRON_MINE,
	IRON_RES_CU,
	IRON_RES_JING,
	BLACK_IRON,
});
protected nosave mapping res_cost = ([
"axe" : 5,
"blade" : 5,
"dagger" : 1,
"hammer" : 8,
"dhammer" : 6,
"spear" : 6,
"stick" : 6,
"sword" : 5,
"whip" : 6,
]),

res_cost_desc = ([
"axe" : "斧子(Axe) [需 %d 斤原料]\n",
"blade" : "刀(Blade) [需 %d 斤原料]\n",
"dagger" : "匕首(dagger) [需 %d 斤原料]\n",
"hammer" : "雙手錘(hammer) [需 %d 斤原料]\n",
"dhammer" : "單手錘(hammer) [需 %d 斤原料]\n",
"spear" : "槍(spear) [需 %d 斤原料]\n",
"stick" : "棍(stick) [需 %d 斤原料]\n",
"sword" : "劍(sword) [需 %d 斤原料]\n",
"whip" : "鞭(whip) [需 %d 斤原料]\n",
]),

std_self_weapon = ([
"axe" : SELF_W_AXE,
"blade" : SELF_W_BLADE,
"dagger" : SELF_W_DAGGER,
"hammer" : SELF_W_HAMMER,
"dhammer" : SELF_W_DHAMMER,
"spear" : SELF_W_SPEAR,
"stick" : SELF_W_STICK,
"sword" : SELF_W_SWORD,
"whip" : SELF_W_WHIP,
]);

protected void get_self_weapon_unwield_msg(string, object, object);
protected void get_self_weapon_wield_msg(string, object, object);
protected void get_self_weapon_desc(string, object, object, string);
protected void get_self_weapon_id(string, object, object);
protected void get_self_weapon_name(string, object, object);
protected void select_weapon_class(string, object, string);
protected void rong_he(object, object);

int learn_make_weapon_ability(string cls)
{
#ifdef WIZARD_FLAG
	object pob;

	if( ( pob
	&& ( pob->query_wiz_flag()
	|| sscanf(file_name(pob),WIZ_DIR"%*s") ) )
	|| (this_player(1) && wizardp(this_player(1))) )
		return 0;
#endif

	if(!stringp(cls))
		return 0;

	if(!mapp(make_weapon_ability))
		make_weapon_ability = ([]);

	if(!undefinedp(make_weapon_ability[cls]))
		return notify_fail(sprintf("%s已經會打造這種兵器了。\n", name()));

	if(undefinedp(res_cost[cls]))
		return notify_fail(sprintf("%s沒法學會這種兵器的打造方法。\n", name()));

	make_weapon_ability += ([ cls : 5 ]);
	save();

	return 1;
}

int add_make_weapon_ability(string cls)
{
#ifdef WIZARD_FLAG
	object pob;

	if( ( pob
	&& ( pob->query_wiz_flag()
	|| sscanf(file_name(pob),WIZ_DIR"%*s") ) )
	|| (this_player(1) && wizardp(this_player(1))) )
		return 0;
#endif

	if(!stringp(cls))
		return 0;

	if(!mapp(make_weapon_ability) || undefinedp(make_weapon_ability[cls]))
		return notify_fail(sprintf("%s還不會打造這種兵器。\n", name()));

	make_weapon_ability[cls]++;
	save();

	return 1;
}

protected void find_banghui_master()
{
	if(!objectp(master = query_bh_master_ob()))
	{
		init_banghui_data();
		if(!objectp(master = query_bh_master_ob()))
			return;
	}

	if(!(b_id = master->query_banghui_id())
	|| !(b_name = master->query_banghui_name()) )
		master = 0;
}

protected int set_sell_rate(int n)
{
	if(!intp(n) || (n < 0) || (n > MAX_SELL_RATE))
		return 0;

	sell_rate = n;
	return 1;
}

void init()
{
	::init();
	add_action("do_sell", "sell");
	add_action("do_fix",({"fix","xiuli"}));
	add_action("do_epurate", "ti");	// 提煉、精煉礦
	add_action("do_make_self", "dazao");
	add_action("do_ronghe", "ronghe");
}

int do_sell(string arg)
{
	object ob,me = this_player();
	int temp,value,mangle, save_value;
    
	if(!environment() || base_name(environment()) != query("startroom"))
		return 0;
	if(!master)
	{
		find_banghui_master();
		if(!objectp(master))
			return notify_fail("此幫派控制中心出現錯誤，請通知巫師解決。\n");
	}

	if( me->is_busy() )
		return notify_fail(BUSY_MESSAGE);

	if( !arg || ! ob = present(arg, this_player()) )
		return notify_fail( "你要賣什麼物品？\n" );

	if(!ob->is_weapon() && !ob->is_armor())
		return notify_fail(name()+"搖搖頭說道：“這裡只收購兵器和護甲。”\n");

	if(ob->query("no_drop") || ob->query("no_sell"))
		return notify_fail("這樣東西不能賣。\n");

	if(ob->is_weapon())
	{
		temp = ob->query("weapon_prop/damage");

		if(ob->is_self_make_weapon())
			value = ob->query("value");

		else if(temp <= 50) /* 普通兵器，按 value 算價。*/
		{
			if(ob->query("base_value")) /* combined ob */
				value = ob->value();
			else
				value = ob->query("value");
			if( !value )
				return notify_fail("這樣東西不值錢。\n");
			if(value < 10)
				return notify_fail(ob->query("name")+"價值太低，這不收。\n");
		}

		else
			value = temp * WEAPON_VALUE;

		value = value*sell_rate/100;
		save_value = value*(MAX_SELL_RATE - sell_rate)/100;

		mangle = ob->query("weapon_mangle");
		value = value*(W_MAX_MANGLE-mangle)/W_MAX_MANGLE;

		if(value < 10)
			return notify_fail(sprintf("%s說道：“%s已經不值錢了。”\n",
				this_object()->name(),ob->name()));

		if(mangle == W_MAX_MANGLE)
			return notify_fail(sprintf("%s說道：“%s已經破舊的一錢不值了。”\n",
				this_object()->name(),ob->name()));
		else
			write(sprintf("你把%s賣掉，得到%s。\n",ob->name(),chinese_value(value)));

		if(mangle >= W_MAX_MANGLE/2)
			write(sprintf("%s說道：“%s已經破舊的不像樣子了，只能值這幾個錢了。”\n",
				this_object()->name(),ob->name()));
		else if(mangle >= W_MAX_MANGLE/5)
			write(sprintf("%s說道：“%s有一些破舊，所以只能值這些錢。”\n",
				this_object()->name(),ob->name()));
		else if(mangle >0)
			write(sprintf("%s說道：“%s稍微有一點損壞，這個價錢已經不錯了。”\n",
				this_object()->name(),ob->name()));

		pay_player(me, value, ob->query_credit_point_flag()?1:0);
		if(ob->query("equipped"))
			ob->unequip();
		destruct(ob);

		// 差價部分存入幫派金庫
		if(save_value)
			master->save_to_treasury(save_value);

		return 1;
	}

	else if(ob->is_armor())
	{
		temp = ob->query("armor_prop/armor");
		if(temp <= 50) /* 普通護甲，按 value 算價。*/
		{
			value = ob->query("value");
			if( !value )
				return notify_fail("這樣東西不值錢。\n");
			if(value < 10)
				return notify_fail(ob->query("name")+"價值太低，這不收。\n");
		}

		else
			value = temp * ARMOR_VALUE;

		value = value*sell_rate/100;
		save_value = value*(MAX_SELL_RATE - sell_rate)/100;

		mangle = ob->query("armor_mangle");
		value = value*(A_MAX_MANGLE-mangle)/A_MAX_MANGLE;

		if(value < 10)
			return notify_fail(sprintf("%s說道：“%s已經不值錢了。”\n",
				this_object()->name(),ob->name()));

		if(mangle == A_MAX_MANGLE)
			return notify_fail(sprintf("%s說道：“%s已經破舊的一錢不值了。”\n",
				this_object()->name(),ob->name()));
		else
			write(sprintf("你把%s賣掉，得到%s。\n",ob->name(),chinese_value(value)));

		if(mangle >= A_MAX_MANGLE/2)
			write(sprintf("%s說道：“%s已經破舊的不像樣子了，只能值這幾個錢了。”\n",
				this_object()->name(),ob->name()));
		else if(mangle >= A_MAX_MANGLE/5)
			write(sprintf("%s說道：“%s有一些破舊，所以只能值這些錢。”\n",
				this_object()->name(),ob->name()));
		else if(mangle >0)
			write(sprintf("%s說道：“%s稍微有一點損壞，這個價錢已經不錯了。”\n",
				this_object()->name(),ob->name()));

		pay_player(me, value, ob->query_credit_point_flag()?1:0);
		if(ob->query("equipped"))
			ob->unequip();
		destruct(ob);

		if(save_value)
			master->save_to_treasury(save_value);

		return 1;
	}
	return 0;
}

int do_fix(string arg)
{
	object me = this_player(),ob;
	int mangle,value,fee,f;

	if(!master)
	{
		find_banghui_master();
		if(!objectp(master))
			return notify_fail("此幫派控制中心出現錯誤，請通知巫師解決。\n");
	}

	if(!arg || !ob = present(arg,me))
		return notify_fail(this_object()->name()+"看著你說道：“你要修理什麼？”\n");

	if(!ob->is_weapon() && !ob->is_armor())
		return notify_fail(this_object()->name()+"搖搖頭說道：“咱這只修理兵器和護甲。”\n");

	if(ob->query("base_value")) /* combined ob */
		value = ob->value();
	else
		value = ob->query("value");

	if( !value )
		return notify_fail(this_object()->name()+"說道：這東西不值錢還修什麼，扔了算了！\n");
	if(value < 10)
		return notify_fail(this_object()->name()+
			"說道："+ob->name()+"值不了幾個錢，這不修。\n");

	if(ob->is_weapon())
	{
		mangle = ob->query("weapon_mangle");

		if(!mangle)
			return notify_fail(this_object()->name()+"說道：嶄新的"+
				ob->name()+"還修什麼。\n");

		if(me->query_banghui_id() == b_id)
		{
			ob->delete("weapon_mangle");
			write(sprintf("%s點點頭說道：%s修好了，拿著它為我們%s多出力。\n",
				name(), ob->name(), b_name));
			return 1;
		}

		fee = value/W_MAX_MANGLE*mangle;
		if(fee < MIN_FEE)
			fee = MIN_FEE;

		if(!f=player_pay(me,fee) || f == 2)
			return notify_fail(this_object()->name()+"說道：修理這件兵器需要"+
				chinese_value(fee)+"，你身上的錢不夠。\n");

		else
		{
			ob->delete("weapon_mangle");
			write(sprintf("%s說道：“%s修好了，修理費一共%s，看你跑江湖也不容易，這回真便宜你了。”\n",
				this_object()->name(),ob->name(),chinese_value(fee)));
			return 1;
		}
	}

	else
	{
		mangle = ob->query("armor_mangle");

		if(!mangle)
			return notify_fail(this_object()->name()+"說道：嶄新的"+
				ob->name()+"還修什麼。\n");

		if(me->query_banghui_id() == b_id)
		{
			ob->delete("armor_mangle");
			write(sprintf("%s點點頭說道：%s修好了，穿戴著它為我們%s多出力。\n",
				name(), ob->name(), b_name));
			return 1;
		}

		fee = value/A_MAX_MANGLE*mangle;
		if(fee < MIN_FEE)
			fee = MIN_FEE;

		if(!f=player_pay(me,fee) || f == 2)
			return notify_fail(this_object()->name()+"說道：修理這件護具需要"+
				chinese_value(fee)+"，你身上的錢不夠。\n");

		else
		{
			ob->delete("armor_mangle");
			write(sprintf("%s說道：“%s修好了，修理費一共%s，看你跑江湖也不容易，這回真便宜你了。”\n",
				this_object()->name(),ob->name(),chinese_value(fee)));
			return 1;
		}
	}
}

// NEW:
void setup()
{
	mapping inq;

	::setup();

	if(!query("no_kill"))
		set("no_kill",1);

	if(!master)
		find_banghui_master();

	if(!mapp(inq = this_object()->query("inquiry",1)))
		inq = ([ "鑒定" : (: call_other, this_object(), "identify_mine_stone" :) ]);
	else if(undefinedp(inq["鑒定"]))
		inq += ([ "鑒定" : (: call_other, this_object(), "identify_mine_stone" :) ]);
	else
		return;

	this_object()->set("inquiry",inq);
}

string identify_mine_stone(object who)
{
	object *inv;

	if(!who)
		return 0;

	if(!sizeof(inv = filter_array(all_inventory(who), (: $1->is_mine_stone() && !$1->query_check() :))))
		return "你身上沒有需要鑒定的礦石。\n";

	inv->set_check_flag(1);
	return sprintf("都鑒定好了%s。\n",!random(3)?"，沒什麼值錢的東西":"");
}

int do_epurate(string arg)
{
	object tg, ob, me = this_player();
	string mcs, cmcs;
	int ew, value, rtn;

	if(!master)
	{
		find_banghui_master();
		if(!objectp(master))
			return notify_fail("此幫派控制中心出現錯誤，請通知巫師解決。\n");
	}

	if(do_nothing)
		return notify_fail(sprintf("%s說道：等會兒，正忙著呢。\n", name()));

	if(!arg || !objectp(ob = present(arg, me)))
		return notify_fail("你要提煉什麼？\n");

	if(ob->is_mine_stone())		// 提煉礦石
	{
		if(!ob->query_check())
			ob->set_check_flag(1);

		if( !(mcs = ob->query_mine_class())
		|| !(cmcs = MINE_D->chinese_mine_class(mcs))
		|| (member_array(mcs, can_epurate) == -1) )
			return notify_fail(sprintf("%s搖搖頭說道：這裡不含任何礦物成份。\n", name()));

		if( (ew = ob->query_eff_weight()) < 1 )
			return notify_fail(sprintf("%s搖搖頭說道：這裡含的%s太少了，沒法提煉。\n", name(), cmcs));

		if(!objectp(tg = MINE_D->query_mine_class_up_ob(mcs)))
			return notify_fail(sprintf("%s搖搖頭說道：這塊礦石沒法提煉。\n", name()));

		if(me->query_banghui_id() != b_id)
		{
			value = MINE_D->query_mine_class_value(tg->query_mine_class()) * ew * 3 / 10;
			if(value < 1)
				value = 1;

			if(!(rtn=player_pay(me,value)) || (rtn == 2))
			{
				destruct(tg);
				return notify_fail(sprintf("%s說道：提煉這塊礦石裡的%s需要%s。\n",
					name(), cmcs, chinese_value(value)));
			}
		}

		do_nothing = 1;
		message_vision("$N朝著$n點點頭說道：等一會兒。\n", this_object(), me);

		call_out("epurate_it", 1+random(2), me, ob, tg);
		return 1;
	}

	else if(ob->is_iron_class_res())	// 精煉
	{
		int upq;

		if( !(mcs = ob->query_mine_class())
		|| !(cmcs = MINE_D->chinese_mine_class(mcs))
		|| (member_array(mcs, can_epurate) == -1)
		|| !(upq = MINE_D->query_mine_class_up_quantity(mcs)) )
			return notify_fail(sprintf("%s搖搖頭說道：這東西沒法再精煉了。\n", name()));

		if( (ew = ob->query_weight()/100) < upq )
			return notify_fail(sprintf("%s搖搖頭說道：對%s精煉至少需要 %d 兩，這塊%s不夠。\n",
				cmcs, upq, cmcs));

		if(!objectp(tg = MINE_D->query_mine_class_up_ob(mcs)))
			return notify_fail(sprintf("%s搖搖頭說道：我這沒法對%s進行精煉了。\n", name(), cmcs));

		ew /= upq;

		if(me->query_banghui_id() != b_id)
		{
			value = (MINE_D->query_mine_class_value(tg->query_mine_class()) -
				MINE_D->query_mine_class_value(mcs)*upq) * ew/2;

			if(value < 10)
				value = 10;

			if(!(rtn=player_pay(me,value)) || (rtn == 2))
			{
				destruct(tg);
				return notify_fail(sprintf("%s說道：對這塊%s進行精煉需要%s。\n",
					name(), cmcs, chinese_value(value)));
			}
		}

		destruct(ob);
		tg->set_weight(ew*100);
		if(!tg->move(me) && !tg->move(environment()))
		{
			destruct(tg);
			return notify_fail("異常超重，向巫師報告吧。\n");
		}

		rong_he(me, tg);
		write(sprintf("%s點點頭說道：好了，拿去吧。\n", name()));
		return 1;
	}

	else
		return notify_fail(sprintf("%s搖搖頭說道：這東西沒法提煉。\n", name()));
}

protected void epurate_it(object me, object ob, object tg)
{
	int ew;

	if(!ob || !me || !tg || (environment(me) != environment()))
	{
		if(tg)
			destruct(tg);
		do_nothing = 0;
		return;
	}

	ew = ob->query_eff_weight()*9/10;
	if(ew < 1)
		ew = 1;

	if(ob->query_mine_class() == BLACK_IRON)
		tg->set_sum(ew);
	else
		tg->set_weight(ew*100);

	destruct(ob);
	if(!tg->move(me) && !tg->move(environment()))
		destruct(tg);

	rong_he(me, tg);
	do_nothing = 0;
	message_vision("$N朝著$n點點頭說道：提煉好了，拿去吧。\n", this_object(), me);
}

int do_ronghe(string arg)
{
	object me = this_player(), ob;

	if(!stringp(arg)
	|| !sizeof(arg)
	|| !objectp(ob = present(arg, me))
	|| !ob->is_iron_class_res() )
		return notify_fail("你要熔合什麼？\n");

	rong_he(me, ob);
	write(sprintf("%s點點頭說道：好了。\n", name()));
	return 1;
}

protected void rong_he(object me, object ob)
{
	object *inv;
	string cms;
	int wt;

	if(!objectp(me)
	|| !objectp(ob)
	|| !ob->is_iron_class_res()
	|| !(cms = ob->query_mine_class()) )
		return;

	if( !sizeof(inv = filter_array(all_inventory(me), (: ($1->is_iron_class_res())
		&& ($1->query_mine_class() == $(cms))
		&& ($1 != $(ob)) :))) )
		return;

	if(cms == BLACK_IRON)
	{
		foreach(object tmp in inv)
		{
			wt += tmp->query_sum();
			destruct(tmp);
		}

		ob->add_sum(wt);
		return;
	}

	foreach(object tmp in inv)
	{
		wt += tmp->query_weight();
		destruct(tmp);
	}

	wt += ob->query_weight();
	ob->set_weight(wt);
}

nomask int do_make_self(string arg)
{
	object me = this_player(1), *inv, ob;
	int vl;

	if(!master)
	{
		find_banghui_master();
		if(!objectp(master))
			return notify_fail("此幫派控制中心出現錯誤，請通知巫師解決。\n");
	}

	if(me->query_banghui_id() != b_id)
		return notify_fail(sprintf("%s搖搖頭說道：你不是我們%s的人。\n", name(), b_name));

#ifdef WIZARD_FLAG
	if(wizardp(me))
		return notify_fail("巫師不允許打造兵器。\n");
	if(query_wiz_flag() && !wizardp(me))
		return notify_fail(sprintf("%s搖搖頭說道：我不能為玩家打造兵器。\n", name()));
#endif

	if(!arg)	// 初始打造兵器
	{
		string out, *can;

		if(!make_weapon_ability || !sizeof(make_weapon_ability))
			return notify_fail(sprintf("%s搖搖頭說道：我不會打造兵器。\n", name()));

		if(!sizeof(inv = filter_array(all_inventory(me), (: is_money :))))
			return notify_fail("打造兵器需要 5 兩白銀，你身上沒錢。\n");

		foreach(object tmp in inv)
			vl += tmp->value();

		if(vl < 500)
			return notify_fail("打造兵器需要 5 兩白銀，你身上錢不夠。\n");

		can = keys(make_weapon_ability);
		out = "可打造的兵器種類：\n";
		for(int i=0; i<sizeof(can); i++)
			out += sprintf((string)i+1+". "+res_cost_desc[can[i]],
				res_cost[can[i]]);
		out += sprintf("請選擇你要打造的兵器類型[1-%d, q退出]：\n", sizeof(can));
		write(out);
		input_to( (: select_weapon_class :), me, out);
		return 1;
	}

	else
	{
		int damage, amount, pay, n, cost;

		if(!objectp(ob = present(arg, me)) || !ob->is_self_make_weapon())
			return notify_fail("你要鍛造哪件兵器？\n");

		damage = ob->query("weapon_prop/damage") - ob->query_base_damage() + 1;

		vl = damage*damage;

		if(!n = sizeof(inv = filter_array(all_inventory(me),
			(: $1->is_iron_class_res() && ($1->query_mine_class() == BLACK_IRON) :))))
			return notify_fail(sprintf("鍛造%s需要用 %d 錢玄鐵，你身上沒有。\n", ob->name(), vl));

		foreach(object tmp in inv)
			amount += tmp->query_sum();

		if(amount < vl)
			return notify_fail(sprintf("鍛造%s需要用 %d 錢玄鐵，你身上不夠。\n", ob->name(), vl));

		cost = vl*70/100;
		if(cost < 1)
			cost = 1;

		if(!(pay = player_pay(me, cost*100)) || (pay == 2) )
			return notify_fail(sprintf("鍛造%s需要花費 %d 兩白銀。\n", ob->name(), vl));

		for(int i=0; i<n; i++)
		{
			amount = inv[i]->query_sum();

			if(amount == vl)
			{
				destruct(inv[i]);
				break;
			}

			if(amount > vl)
			{
				inv[i]->add_sum(-vl);
				break;
			}

			else
			{
				vl -= amount;
				destruct(inv[i]);
			}
		}

		ob->add("weapon_prop/damage", 1);
		ob->set_weapon_weight();
		ob->set_weapon_value();
		write(sprintf("%s點點頭說道：鍛造好了，歡迎下次再光顧。\n", name()));
		return 1;
	}
}

protected void select_weapon_class(string str, object me, string out)
{
	object ob, *inv;
	int cost, wt, n, i, black;

	if(!me || (environment(me) != environment()) )
		return;

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(me, out);
		input_to( (: select_weapon_class :), me, out);
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(me, "ok.\n");
		return;
	}

	if(!sscanf(str, "%d", i) || (i<1) || (i>sizeof(make_weapon_ability)))
	{
		tell_object(me, out);
		input_to( (: select_weapon_class :), me, out);
		return;
	}

	ob = new(std_self_weapon[make_weapon_ability[i-1]]);
	cost = res_cost[make_weapon_ability[i-1]];

	if(!ob)
	{
		tell_object(me, "打造兵器出現錯誤，請通知巫師處理。\n");
		return;
	}

	if(!n = sizeof(inv = filter_array(all_inventory(me),
		(: $1->is_iron_class_res() && ($1->query_mine_class() == STEEL_RES) :))))
	{
		black = 1;
		if(!n = sizeof(inv = filter_array(all_inventory(me),
			(: $1->is_iron_class_res() && ($1->query_mine_class() == BLACK_IRON) :))))
			{
				destruct(ob);
				tell_object(me, sprintf("打造這件兵器需要 %d 斤原料，你身上沒有。\n", cost));
				return;
			}
	}

	if(black)
	{
		for(i=0; i<n; i++)
		{
			wt += inv[i]->query_sum();
			if(wt >= cost*10000)
				break;
		}

		if(wt < cost*10000)
		{
			destruct(ob);
			tell_object(me, sprintf("打造這件兵器需要 %d 斤原料，你身上不夠。\n", cost));
			return;
		}

		ob->set("material", BLACK_IRON);
	}

	else
	{
		for(i=0; i<n; i++)
		{
			wt += inv[i]->query_weight();
			if(wt >= cost*1000)
				break;
		}

		if(wt < cost*1000)
		{
			destruct(ob);
			tell_object(me, sprintf("打造這件兵器需要 %d 斤原料，你身上不夠。\n", cost));
			return;
		}

		ob->set("material", STEEL_RES);
	}

	ob->set_require_res(cost*1000);

	tell_object(me, "
如要名稱中使用顏色，可以用以下控制符：
注意：控制符字母要大寫。

$RED$ - 紅色		$HIR$ - 亮紅色
$GRN$ - 綠色		$HIG$ - 亮綠色
$YEL$ - 土黃色		$HIY$ - 黃色
$BLU$ - 深藍色		$HIB$ - 藍色
$MAG$ - 淺紫色		$HIM$ - 粉紅色
$CYN$ - 藍綠色		$HIC$ - 天青色
$WHT$ - 淺灰色		$HIW$ - 白色

設定兵器的名稱[1-6個漢字, q退出]：\n");
	input_to( (: get_self_weapon_name :), me, ob);
}

protected void get_self_weapon_name(string str, object me, object ob)
{
	int i;
	string tmp;

	if(!me || !ob || (environment(me) != environment()))
	{
		if(ob)
			destruct(ob);
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(me, "
如要名稱中使用顏色，可以用以下控制符：
注意：控制符字母要大寫。

$RED$ - 紅色		$HIR$ - 亮紅色
$GRN$ - 綠色		$HIG$ - 亮綠色
$YEL$ - 土黃色		$HIY$ - 黃色
$BLU$ - 深藍色		$HIB$ - 藍色
$MAG$ - 淺紫色		$HIM$ - 粉紅色
$CYN$ - 藍綠色		$HIC$ - 天青色
$WHT$ - 淺灰色		$HIW$ - 白色

設定兵器的名稱[1-6個漢字, q退出]：\n");
		input_to( (: get_self_weapon_name :), me, ob);
		return;
	}

	if( (str[0] == 'q') || (str[0] == 'Q') )
	{
		destruct(ob);
		tell_object(me, "ok.\n");
		return;
	}

	str = clr_ansi(str);
	str = replace_string(str, "$RED$", RED);
	str = replace_string(str, "$GRN$", GRN);
	str = replace_string(str, "$YEL$", YEL);
	str = replace_string(str, "$BLU$", BLU);
	str = replace_string(str, "$MAG$", MAG);
	str = replace_string(str, "$CYN$", CYN);
	str = replace_string(str, "$WHT$", WHT);
	str = replace_string(str, "$HIR$", HIR);
	str = replace_string(str, "$HIG$", HIG);
	str = replace_string(str, "$HIY$", HIY);
	str = replace_string(str, "$HIB$", HIB);
	str = replace_string(str, "$HIM$", HIM);
	str = replace_string(str, "$HIC$", HIC);
	str = replace_string(str, "$HIW$", HIW);
	str = replace_string(str, "$NOR$", NOR);
	str += NOR;

	tmp = clr_ansi(str);

	if(((i = sizeof(tmp)) < 2) || (i > 12))
	{
		tell_object(me, "[兵器名稱必須使用 1-6 個漢字]\n設定兵器的名稱[1-6個漢字, q退出]：\n");
		input_to( (: get_self_weapon_name :), me, ob);
		return;
	}

	while(i--)
	{
		int section;

                if( tmp[i]<128 )
		{
			tell_object(me, "[兵器名稱必須使用漢字]\n設定兵器的名稱[1-6個漢字, q退出]：\n");
			input_to( (: get_self_weapon_name :), me, ob);
			return;
                }

		if( i%2==0 )
		{
			section = tmp[i] - 160;

			if( (section < 16)
			|| (section > 87) )
			{
				tell_object(me, "[兵器名稱必須使用常用漢字]\n設定兵器的名稱[1-6個漢字, q退出]：\n");
				input_to( (: get_self_weapon_name :), me, ob);
				return;
			}
		}
	}

	ob->set("name", str);
	tell_object(me, "
設定兵器的 ID
  兵器的 ID 最多可使用 4 個單詞
  每個單詞最多 7 個英文字母組成
請設定兵器的 ID [q退出]：\n");
	input_to( (: get_self_weapon_id :), me, ob);
}

protected void get_self_weapon_id(string str, object me, object ob)
{
	string *words;
	int n;

	if(!me || !ob || (environment(me) != environment()))
	{
		if(ob)
			destruct(ob);
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(me, "
設定兵器的 ID
  兵器的 ID 最多可使用 4 個單詞
  每個單詞最多 7 個英文字母組成
請設定兵器的 ID [q退出]：\n");
		input_to( (: get_self_weapon_id :), me, ob);
		return;
	}

	if( (sizeof(str) == 1) && ((str[0] == 'q') || (str[0] == 'Q')) )
	{
		destruct(ob);
		tell_object(me, "ok.\n");
		return;
	}

	if( !(n = sizeof(words = explode(str, " ") - ({ "" }))) || (n > 4) )
	{
		tell_object(me, "
  兵器的 ID 最多只能使用 4 個英文單詞
                         ~~~~
  每個單詞最多 7 個英文字母組成
設定兵器的 ID [q退出]：\n");
		input_to( (: get_self_weapon_id :), me, ob);
		return;
	}

	foreach(string tmp in words)
	{
		if(sizeof(tmp) > 7)
		{
			tell_object(me, "
  兵器的 ID 最多只能使用 4 個英文單詞
  每個單詞最多 7 個英文字母組成
               ~~~~
設定兵器的 ID [q退出]：\n");
			input_to( (: get_self_weapon_id :), me, ob);
			return;
		}

		if(!regexp(tmp, "^[a-zA-Z]+$"))
		{
			tell_object(me, "
  兵器的 ID 最多只能使用 4 個英文單詞
  每個單詞最多 7 個英文字母組成
                   ~~~~~~~~
設定兵器的 ID [q退出]：\n");
			input_to( (: get_self_weapon_id :), me, ob);
			return;
		}
	}

	str = lower_case(str);

	ob->set_name(ob->query("name"), ({ str }) );

	tell_object(me, "請設定兵器的描述：\n﹒描述內容不能超過三行\n﹒每行不超過20個漢字
請輸入('.'結束輸入，'q'退出)：\n------------------------------------------------------\n");
	input_to((: get_self_weapon_desc :), me, ob, "");
}

protected void get_self_weapon_desc(string str, object me, object ob, string desc)
{
	if(!me || !ob || (environment(me) != environment()))
	{
		if(ob)
			destruct(ob);
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		input_to((: get_self_weapon_desc :), me, ob, desc);
		return;
	}

	if( (str[0] == 'q') || (str[0] == 'Q') )
	{
		destruct(ob);
		tell_object(me, "ok.\n");
		return;
	}

	if(str[0] == '.')	// 結束輸入
	{
		if( !sizeof(desc) )
		{
			ob->set("long", 0);
			tell_object(me, "
設定裝佩此兵器時的信息
 $N 為裝佩此兵器的人
 $n 為此兵器
例如：
  裝佩信息設定為：$N拿出一把$n握在手中當作武器。
  裝佩兵器別人就會看到：張三拿出一把天邪短劍握在手中當作武器。

請設定此兵器的裝佩信息[最長不超過25個漢字, q 退出]：
");
			input_to((: get_self_weapon_wield_msg :), me, ob);
			return;
		}

		if( sizeof(explode(desc, "\n")) > 3)
		{
			tell_object(me, HBCYN HIG"﹒兵器的描述內容不能超過三行，請重新設定兵器描述。
﹒描述內容不能超過三行\n﹒每行不超過20個漢字
請輸入('.'結束輸入，'q'退出)：\n------------------------------------------------------\n"NOR);
			input_to((: get_self_weapon_desc :), me, ob, "");
			return;
		}

		if(desc[<1] != '\n')
			desc += "\n";
		ob->set("long", desc);
		tell_object(me, "
設定裝佩此兵器時的信息
 $N 為裝佩此兵器的人
 $n 為此兵器
例如：
  裝佩信息設定為：$N拿出一把$n握在手中當作武器。
  裝佩兵器別人就會看到：張三拿出一把天邪短劍握在手中當作武器。

請設定此兵器的裝佩信息[最長不超過25個漢字, q 退出]：
");
		input_to((: get_self_weapon_wield_msg :), me, ob);
		return;
	}

	if(strsrch(str, '\n'))
	{
		int n;
		string *tmp;

		n = sizeof(tmp = explode(str, "\n"));
		for(int i=0; i<n; i++)
			if(strlen(tmp[i]) > 40)
			{
				tell_object(me, HBCYN HIG"每一行不能超過二十個中文字，請重新輸入剛才輸入的內容：\n");
				input_to((: get_self_weapon_desc :), me, ob, desc);
				return;
			}

			if( sizeof(explode(desc, "\n")) > 3)
			{
				tell_object(me, HBCYN HIG"﹒兵器的描述內容不能超過三行，請重新設定兵器描述。
﹒描述內容不能超過三行\n﹒每行不超過20個漢字
請輸入('.'結束輸入，'q'退出)：\n------------------------------------------------------\n"NOR);
				input_to((: get_self_weapon_desc :), me, ob, "");
				return;
			}
	}

	else
	{
		if(strlen(str) > 40)
		{
			tell_object(me, HBCYN HIG"每一行不能超過二十個中文字，請重新輸入剛才輸入的內容：\n");
			input_to((: get_self_weapon_desc :), me, ob, desc);
			return;
		}

		if( sizeof(explode(desc, "\n")) > 2)
		{
			tell_object(me, HBCYN HIG"﹒兵器的描述內容不能超過三行，請重新設定兵器描述。
﹒描述內容不能超過三行\n﹒每行不超過20個漢字
請輸入('.'結束輸入，'q'退出)：\n------------------------------------------------------\n"NOR);
			input_to((: get_self_weapon_desc :), me, ob, "");
			return;
		}
	}

	desc += str + "\n";
	input_to((: get_self_weapon_desc :), me, ob, desc);
}

protected void get_self_weapon_wield_msg(string str, object me, object ob)
{
	if(!me || !ob || (environment(me) != environment()))
	{
		if(ob)
			destruct(ob);
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(me, "
設定裝佩此兵器時的信息
 $N 為裝佩此兵器的人
 $n 為此兵器
例如：
  裝佩信息設定為：$N拿出一把$n握在手中當作武器。
  裝佩兵器別人就會看到：張三拿出一把天邪短劍握在手中當作武器。

請設定此兵器的裝佩信息[最長不超過25個漢字, q 退出]：
");
		input_to((: get_self_weapon_wield_msg :), me, ob);
		return;
	}

	if( (str[0] == 'q') || (str[0] == 'Q') )
	{
		destruct(ob);
		tell_object(me, "ok.\n");
		return;
	}

	if(sizeof(str) > 50)
	{
		tell_object(me, "
** 信息最長不超過25個漢字 **

設定裝佩此兵器時的信息
 $N 為裝佩此兵器的人
 $n 為此兵器

請設定此兵器的裝佩信息[最長不超過25個漢字, q 退出]：
");
		input_to((: get_self_weapon_wield_msg :), me, ob);
		return;
	}

	if(str[<1] != '\n')
		str += "\n";

	ob->set("wield_msg", str);

	tell_object(me, "
設定放下此兵器時的信息
 $N 為放下此兵器的人
 $n 為此兵器
例如：
  信息設定為：$N將手中的$n插入腰間的劍鞘。
  放下此兵器別人就會看到：張三將手中的天邪短劍插入腰間的劍鞘。

請設定放下此兵器的信息[最長不超過25個漢字, q 退出]：
");
	input_to((: get_self_weapon_unwield_msg :), me, ob);
}

protected void get_self_weapon_unwield_msg(string str, object me, object ob)
{
	object *inv;
	int n, cost, pay, wt, black;
	string cls;

	if(!me || !ob || (environment(me) != environment()))
	{
		if(ob)
			destruct(ob);
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(me, "
設定放下此兵器時的信息
 $N 為放下此兵器的人
 $n 為此兵器
例如：
  信息設定為：$N將手中的$n插入腰間的劍鞘。
  放下此兵器別人就會看到：張三將手中的天邪短劍插入腰間的劍鞘。

請設定放下此兵器的信息[最長不超過25個漢字, q 退出]：
");
		input_to((: get_self_weapon_unwield_msg :), me, ob);
		return;
	}

	if( (str[0] == 'q') || (str[0] == 'Q') )
	{
		destruct(ob);
		tell_object(me, "ok.\n");
		return;
	}

	if(sizeof(str) > 50)
	{
		tell_object(me, "
** 信息最長不超過25個漢字 **

設定放下此兵器時的信息
 $N 為放下此兵器的人
 $n 為此兵器

請設定放下此兵器的信息[最長不超過25個漢字, q 退出]：
");
		input_to((: get_self_weapon_unwield_msg :), me, ob);
		return;
	}

	if(str[<1] != '\n')
		str += "\n";

	ob->set("unwield_msg", str);

	if(!(pay = player_pay(me, 500)) || (pay == 2) )
	{
		tell_object(me, sprintf("打造此兵器需要花費 5 兩白銀，你身上的錢不夠。\n"));
		destruct(ob);
		return;
	}

	cost = ob->query_require_res();

	if(!n = sizeof(inv = filter_array(all_inventory(me),
		(: $1->is_iron_class_res() && ($1->query_mine_class() == STEEL_RES) :))))
	{
		black = 1;
		if(!n = sizeof(inv = filter_array(all_inventory(me),
			(: $1->is_iron_class_res() && ($1->query_mine_class() == BLACK_IRON) :))))
			{
				destruct(ob);
				tell_object(me, sprintf("打造這件兵器需要 %d 斤原料，你身上沒有。\n", cost/10000));
				return;
			}
	}

	if(black)
	{
		for(int i=0; i<n; i++)
		{
			wt += inv[i]->query_sum();
			if(wt >= cost)
				break;
		}

		if(wt < cost)
		{
			destruct(ob);
			tell_object(me, sprintf("打造這件兵器需要 %d 斤原料，你身上不夠。\n", cost/10000));
			return;
		}

		for(int i=0; i<n; i++)
		{
			wt = inv[i]->query_sum();

			if(wt == cost)
			{
				destruct(inv[i]);
				break;
			}

			if(wt > cost)
			{
				inv[i]->set_sum(wt - cost);
				break;
			}

			else
			{
				cost -= wt;
				destruct(inv[i]);
			}
		}
	}

	else
	{
		for(int i=0; i<n; i++)
		{
			wt += inv[i]->query_weight();
			if(wt >= cost)
				break;
		}

		if(wt < cost)
		{
			destruct(ob);
			tell_object(me, sprintf("打造這件兵器需要 %d 斤原料，你身上不夠。\n", cost/1000));
			return;
		}

		for(int i=0; i<n; i++)
		{
			wt = inv[i]->query_weight();

			if(wt == cost)
			{
				destruct(inv[i]);
				break;
			}

			if(wt > cost)
			{
				inv[i]->set_weight(wt - cost);
				break;
			}

			else
			{
				cost -= wt;
				destruct(inv[i]);
			}
		}
	}

	cls = ob->query("skill_type");
	if( (cls == "hammer") && (ob->query("flag") & SECONDARY) )
		cls = "dhammer";

	n = make_weapon_ability[cls] * 1.2;
	n = random(n*0.6) + n*0.7;
	if(n > 0)
		ob->add("weapon_prop/damage", n);

	ob->set_weapon_weight();
	ob->set_weapon_value();

	if( !ob->move(me) && !ob->move(environment()) )
	{
		tell_object(me, sprintf("%s說道：你拿不了你的%s了，沒辦法。\n", name(), ob->name()));
		destruct(ob);
		return;
	}

	tell_object(me, sprintf("%s說道：%s打造好了，看看滿意不滿意。\n", name(), ob->name()));
}

// YUJ@SJ 2001-11-02
// Modified by LOOKLOVE@SJ 引入乘冪計算，大大優化。
// 2002/4/29
// 改為玩家自行修改屬性

// Exp在 100K 以上可以修改屬性。
#define MIN_EXP 100000
// 剩餘EXP比率等於100%減去每點扣除比率
// 當前修改每點屬性，扣除exp比率為5%
#define RATE 0.9500

#include <ansi.h>

int help();

nosave mapping gift_desc = ([
	"str":"膂力",
	"con":"根骨",
	"dex":"身法",
	"int":"悟性"
]);

nosave string *gift = keys(gift_desc);

// 統一過濾 by Lklv
string check(object me)
{
	string msg;

	if (me->query("registered") < 3)
		msg = "抱歉：只有貴賓玩家才有這個機會。\n";
	if ((int)me->query("combat_exp") < MIN_EXP)
		msg = "抱歉：你的經驗不夠 "+MIN_EXP+" ，無法修改屬性。\n";
	if (me->is_ghost())
		msg = "抱歉：你的狀態不穩定，現在無法修改屬性。\n";
	return msg;
}

// yuj 新公式，利用循環算法。
int check_exp(int exp, int num)
{
        while (num--) exp -= exp / 20;
        return exp;
}

int do_change(string arg)
{
	string msg, from, to;
	int exp, num, newexp, tmpexp;
	object me = this_player();

	if (!me) return 0;
	if (!arg) return help();

	if ( stringp(msg = check(me)) )
		return notify_fail(msg);

	if (sscanf(arg, "%d %s to %s", num, from, to) == 3){
		if ( num < 1 || num > 20)
			return notify_fail("輸入數字無效，請重新輸入。\n");

		exp = me->query("combat_exp");
		newexp = check_exp(exp,num);
		tmpexp = exp - newexp;

		if (member_array(from, gift) < 0)
			return notify_fail("你要扣除什麼天賦？\n");

		if (member_array(to, gift) < 0)
			return notify_fail("你要增加什麼天賦？\n");

		if (from == to)
			return notify_fail("檢查一下，輸入錯誤，可能眼花。\n");

		if (me->query(from) <= 10)
			return notify_fail("你的"+gift_desc[from]+"不能再減少了。\n");

		if ( ((int)me->query(from) - num) < 10)
			return notify_fail("你的"+gift_desc[from]+"減少"+num+"點後將少於10點，不能修改。\n");

		if (me->query(to) >= 30 )
			return notify_fail("你的"+gift_desc[to]+"已經大於30點，不能再增加了。\n");

		if ( ((int)me->query(to) + num) > 30)
			return notify_fail("你的"+gift_desc[to]+"增加"+num+"點後將超過30點，不能修改。\n");

		if ( newexp < 95000 )
			return notify_fail("抱歉：修改"+num+"點屬性後經驗將不夠 "+MIN_EXP+" ，建議你一次少修改幾點屬性。\n");

		switch (me->query("family/family_name")) {
			case "明教":
				if (from == "int" && ( me->query("int") <= 20 || ((int)me->query("int") - num) < 20 ) )
					return notify_fail("明教弟子悟性要求至少 20。\n");
				break;
			case "大輪寺":
				if (from == "str" && ( me->query("str") <= 20 || ((int)me->query("str") - num) < 20) )
					return notify_fail("大輪寺弟子膂力要求至少 20。\n");
				if (from == "con" && ( me->query("con") <= 20 || ((int)me->query("con") - num) < 20) )
					return notify_fail("大輪寺弟子根骨要求至少 20。\n");
				break;
		}

		if (! me->query("confirm_passwd"))
			return notify_fail("您沒有設置確認密碼(help passwd)，無法修改屬性。\n");

		write(HIR"請輸入確認密碼：\n"NOR);
		input_to("confirm_passwd", me, from, to, num);
		return 1;
	}

	if (sscanf(arg, "check %d", num) == 1){
		if ( num < 1 || num > 80 )
			return notify_fail("輸入的數值超過了你的隱藏屬性合。\n");

		exp = me->query("combat_exp");
		newexp = check_exp(exp,num);
		tmpexp = exp - newexp;

		msg = HIG"提示：如果要修改 "+num+" 點屬性，你大約要扣除 "+tmpexp+" 點EXP，還剩 "+newexp+" 點EXP。\n"NOR;

		if ( newexp < 95000 )
			msg += HIR"抱歉：修改"+num+"點屬性後經驗將不夠 "+MIN_EXP+" ，建議你一次少修改幾點屬性。\n"NOR;

		if (me->query_skill("jinshe-zhangfa",1) || me->query_skill("jinshe-jianfa",1))
			msg += HIR"注意：如果修改臂力高於20，金蛇劍法和金蛇掌法將被刪除。\n"NOR;

		if (me->query("double_attack") && me->query("zhou"))
			msg += HIR"注意：如果修改悟性高於25，左右互搏將被刪除。\n"NOR;

		if (me->query("dali") && me->query_skill("lingbo-weibu", 1))
			msg += HIR"注意：如果修改悟性低於22，凌波微步將被刪除。\n"NOR;

		if ( me->query("quest/qianzhu/pass") )
			msg += HIR"注意：如果修改根骨低於15或悟性低於20，千蛛萬毒手將被刪除。\n"NOR;

		if ( me->query("quest/pixie/pass") )
			msg += HIR"注意：如果修改身法低於15或悟性低於20，葵花神功將被刪除。\n"NOR;

		if ( me->query("quest/ningxue/pass") )
			msg += HIR"注意：如果修改身法低於15或根骨低於15，凝血神爪將被刪除。\n"NOR;

		write(msg);
		return 1;
	}
	return help();
}

private void confirm_passwd(string pass, object me, string from, string to, int num)
{
	int exp, newexp, tmpexp;
	string confirm_pass;
	confirm_pass = me->query("confirm_passwd");

	if ( confirm_pass && crypt(pass, confirm_pass) != confirm_pass) {
		write("確認密碼錯誤！\n");
		return;
	}
	// 計算扣除exp
	exp = me->query("combat_exp", 1);
	newexp = check_exp(exp,num);
	tmpexp = exp - newexp;

	me->start_busy(1);

	me->add(from, -num);
	me->add(to, num);
	me->add("combat_exp", -tmpexp);

	// 膂力限制金蛇祕籍
	if ( me->query("str") > 20) {
		me->delete_skill("jinshe-zhangfa");
		me->delete_skill("jinshe-jianfa");
	}

	// 悟性限制讀書寫字
	if (me->query_skill("literate", 1) > me->query("int") * 10)
		me->set_skill("literate", me->query("int") * 10);

	// 雙手互搏要求悟性 <= 25
	if (me->query("int") > 25 ){
		me->delete("double_attack");
		me->delete("zhou/hubo");
	}

	// 凌波微步要求悟性 >= 22
	if ( me->query("int") < 22 ){
		me->delete("dali/pass");
		me->delete("dali/meet_dy1");
		me->delete_skill("lingbo-weibu", 1);
	}

	// 千蛛萬毒手要求悟性 >=20 且根骨 >=15
	if ( me->query("int") < 20 || me->query("con") < 15 ) {
		me->delete("quest/qianzhu/pass");
		me->delete_skill("qianzhu-wandushou", 1);
	}

	// 葵花神功要求悟性 >=20 且根骨 >=15
	if ( me->query("int") < 20 || me->query("dex") < 15 ) {
		me->delete("quest/pixie/pass");
		me->delete_skill("pixie-jian", 1);
		me->delete_skill("kuihua-shengong", 1);
	}

	// 凝血神爪要求根骨 >=15 且身法 >=15
	if ( me->query("dex") < 15 || me->query("con") < 15 ) {
		me->delete("quest/ningxue/pass");
		me->delete_skill("ningxue-shenzhua", 1);
	}

	me->setup();
	me->save();
	write(HIY"你將"+num+"點"+gift_desc[from]+"調整到"+gift_desc[to]+"上。\n"NOR, me);
	log_file("nosave/ADJUST",
		me->query("name")+"("+capitalize(geteuid(me))+")"
		+"調整"+num+"點"+gift_desc[from]
		+"到"+gift_desc[to]+"上，扣除 "+tmpexp+" 點經驗，剩餘"+newexp+"\n",
		me,
		({ me })
	);
	return;
}

int help()
{
	write(HIR"修改先天屬性，每點屬性修改將扣除 5% 經驗值。\n"NOR);
	write("EXP不足"+MIN_EXP+"不能修改屬性。\n");
	write("\n");
	write("指令格式：\n");
	write("    計算扣除損失：cgift check <要修改的點數>\n");
	write("    修改屬性：cgift <點數> <要扣除的天賦> to <要增加的天賦>\n");
	write("\n");
	write("可使用的屬性參數：\n");
	write("    膂力  str           根骨  con\n");
	write("    身法  dex           悟性  int\n");
	write("\n");
	write(HIR"請慎重使用，操作失誤後果自負，改錯不補。\n"NOR);
	return 1;
}

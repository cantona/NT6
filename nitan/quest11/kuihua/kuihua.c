// kuihua.c 葵花寶典
// By River@SJ 2003.1.11

inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIW"葵花寶典"NOR, ({ "kuihua baodian", "baodian", "book"}));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "這就是武林第一秘籍「葵花寶典」，相傳是一位宮中太監所作。\n");
		set("value", 5000);
		set("unique", 1);
		set("no_give", 1);
		set("treasure",1);
		set("material", "paper");
		set("no_get", "這樣東西不能離開那兒。\n");
	}
	setup();
}

void init()
{
	if (environment() == this_player())
		add_action("do_du", "read");
}

int do_du(string arg)
{
	object me = this_player();
	object ob = this_object();
	mapping skills = me->query_skills();
	string *sk;
	int i;

	if (!(arg=="pixie-jian" || arg=="kuihua-shengong"))
		return notify_fail("你要讀什麼？\n");
if (arg=="pixie-jian") {
	if ( me->is_busy() || me->is_fighting())
		return notify_fail("你正忙著呢。\n");

	if ( !me->query("quest/pixie/pass") || me->query("gender") == "女性" )
		return notify_fail("你是怎麼得到「葵花寶典」的啊？\n");

	if ( query("owner") != me && !wizardp(me))
		return notify_fail("你是怎麼得到「葵花寶典」的啊？\n");

	if ( me->query("neili") < 1500 )
		return notify_fail("你的真氣不夠。\n");

	if ( me->query_skill("pixie-jian", 1) < 150 )
		return notify_fail("你的辟邪劍法等級太低，無法研讀「葵花寶典」。\n");

	if (environment(me)->query("pigging"))
		return notify_fail("你還是專心拱豬吧！\n");

	if (environment(me)->query("pending"))
		return notify_fail("此地不宜研習「葵花寶典」！\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("臥室不宜修練，會影響別人休息。\n");
 
	if (environment(me)->query("no_fight"))
		return notify_fail("此地不宜研習「葵花寶典」！\n");

	if ( me->query("gender") == "男性" ) {

		if ( me->query("marry"))
			return notify_fail("你已結婚，恐怕不適合研習「葵花寶典」。\n");

		if ( ! skills )
			return notify_fail("你這也太。。。。\n");

		sk = keys(skills);
		i = sizeof(sk);
		while (i--) {
			if (sk[i] == "dulong-dafa"
			|| sk[i] == "guiyuan-tunafa"
			|| sk[i] == "hanbing-zhenqi"
			|| sk[i] == "huagong-dafa"
			|| sk[i] == "kuihua-shengong" 
			|| sk[i] == "jiuyin-zhengong" ) continue;

			if ( SKILL_D(sk[i])->valid_enable("force"))
				return notify_fail("你不散掉"+to_chinese(sk[i])+"，無法修習辟邪劍法。\n");
		}
		tell_object(me, HIW"\n欲練神功，引刀自宮！\n\n"NOR);
		tell_object(me, HIR"你是否願意引刀自宮，確定嗎？[Y|N]"NOR);
		input_to("cut_jj", me );
	}
	else {
		if ( me->query("jing") < 40 )
			return notify_fail("你的精太少了，不夠研讀「葵花寶典」。\n");

		if ((!objectp(ob = present("needle", me)) ) || (!ob->query("equipped") ))
			return notify_fail("你沒用繡花針，感到無法理解這種陰柔靈活的武功。\n");

		if ( me->query_skill("pixie-jian", 1) > 240 )
			return notify_fail("你研讀了一會兒，但是發現上面所說的對你而言都太淺了，沒有學到任何東西。\n");

		me->receive_damage("jing", 30 );
		me->add("neili", - 50);
		me->improve_skill("pixie-jian", me->query_int());
		if (!random(8))
			message("vision", me->name() + "仔細研讀著「葵花寶典」的精妙之處。\n", environment(me), me); 
		tell_object(me, "你仔細研讀著「葵花寶典」的精妙之處。\n");
	}
	return 1;
  }
  if (arg=="kuihua-shengong") {
	if ( me->is_busy() || me->is_fighting())
		return notify_fail("你正忙著呢。\n");

	if ( !me->query("quest/pixie/pass") || me->query("gender") == "女性" )
		return notify_fail("你是怎麼得到「葵花寶典」的啊？\n");

	if ( query("owner") != me && !wizardp(me))
		return notify_fail("你是怎麼得到「葵花寶典」的啊？\n");

	if ( me->query("neili") < 1500 )
		return notify_fail("你的真氣不夠。\n");

	if ( me->query_skill("pixie-jian", 1) < 150 )
		return notify_fail("你的辟邪劍法等級太低，無法研讀「葵花寶典」。\n");

	if (environment(me)->query("pigging"))
		return notify_fail("你還是專心拱豬吧！\n");

	if (environment(me)->query("pending"))
		return notify_fail("此地不宜研習「葵花寶典」！\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("臥室不宜修練，會影響別人休息。\n");
 
	if (environment(me)->query("no_fight"))
		return notify_fail("此地不宜研習「葵花寶典」！\n");

	if ( me->query("gender") == "男性" ) {

		if ( me->query("marry"))
			return notify_fail("你已結婚，恐怕不適合研習「葵花寶典」。\n");

		if ( ! skills )
			return notify_fail("你這也太。。。。\n");

		sk = keys(skills);
		i = sizeof(sk);
		while (i--) {
			if (sk[i] == "dulong-dafa"
			|| sk[i] == "guiyuan-tunafa"
			|| sk[i] == "hanbing-zhenqi"
			|| sk[i] == "huagong-dafa"
			|| sk[i] == "kuihua-shengong" 
			|| sk[i] == "jiuyin-zhengong" ) continue;

			if ( SKILL_D(sk[i])->valid_enable("force"))
				return notify_fail("你不散掉"+to_chinese(sk[i])+"，無法修習辟邪劍法。\n");
		}
		tell_object(me, HIW"\n欲練神功，引刀自宮！\n\n"NOR);
		tell_object(me, HIR"你是否願意引刀自宮，確定嗎？[Y|N]"NOR);
		input_to("cut_jj", me );
	}
	else {
		if ( me->query("jing") < 40 )
			return notify_fail("你的精太少了，不夠研讀「葵花寶典」。\n");

		if ((!objectp(ob = present("needle", me)) ) || (!ob->query("equipped") ))
			return notify_fail("你沒用繡花針，感到無法理解這種陰柔靈活的武功。\n");

		if ( me->query_skill("kuihua-shengong", 1) > 220 )
			return notify_fail("你研讀了一會兒，但是發現上面所說的對你而言都太淺了，沒有學到任何東西。\n");

		me->receive_damage("jing", 30 );
		me->set("quest/pixie/pass","pass");
		me->add("neili", - 50);
		me->improve_skill("kuihua-shengong", me->query_int());
		if (!random(8))
			message("vision", me->name() + "仔細研讀著「葵花寶典」的精妙之處。\n", environment(me), me); 
		tell_object(me, "你仔細研讀著「葵花寶典」的精妙之處。\n");
	}
	return 1;
  }
}

private void cut_jj(string arg, object me)
{
	if( arg[0]=='y' || arg[0]=='Y' ) {
		me->set("gender", "無性");
		me->set("class", "eunuch");
		CHANNEL_D->do_channel( this_object(), "rumor", sprintf("聽說%s為了修練"HIR"辟邪劍法"HIM"而引刀自宮了！"NOR, me->name(1)));
		log_file("quest/pixie",sprintf(HIR"%-18s為研讀「葵花寶典」，而引刀自宮。"NOR, me->name(1)+"("+capitalize(getuid(me))+")", ), me);
		tell_object(me, HIR"你只覺得兩腿間一陣劇痛，鮮血激噴而出……\n"NOR);
		me->receive_wound("qi", 4000, "引刀自宮不慎，失血過多而");
	}
	else write("你心想還是再考慮下吧。\n");
}

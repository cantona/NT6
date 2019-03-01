// dongfang.c 東方不敗
// By River@SJ For kuihua-baodian Quest 2003.1.11

inherit NPC;

inherit F_MASTER;

#include <ansi.h>

string ask_me();
void create()
{
	object ob;
	set_name("東方不敗", ({ "dongfang bubai", "dongfang", "bubai"}));
	set("long", "他就是武林之中一位驚天動地，威震當世的怪傑。\n"+
		"此刻他剃光了胡須，臉上竟然施了脂粉，身上那件衣衫式樣男不男，女不女，\n"+
		"顏色之妖，便穿在少女身上，也顯得太嬌艷、太刺眼了些。\n");

	set("title",HIY"日月神教教主"NOR);         
	set("nickname", HIR"日出東方 唯我不敗"NOR);
	set("gender", "無性");
	set("age", 54);
	set("attitude", "friendly");
	set("str", 35);
	set("int", 45);
	set("con", 45);
	set("dex", 45);
	set("per", 28);
	set("class", "eunuch");
	set("unique", 1);

	set("max_qi", 15000);
	set("max_jing", 10500);
	set("eff_jingli", 8000);
	set("max_neili", 23000);
	set("neili", 23000);
	set("jiali", 200);
	set("combat_exp", 5600000);
	set("shen", -50000);

	set_skill("sword", 380); 
	set_skill("parry", 380);
	set_skill("dodge", 380);
	set_skill("claw", 380);
	set_skill("force", 380);
	set_skill("pixie-jian", 380);        
	set_skill("youming-zhao", 380);
	set_skill("literate", 280);
	set_skill("kuihua-shengong", 380);

	map_skill("sword", "pixie-jian");
	map_skill("parry", "pixie-jian");
	map_skill("dodge", "pixie-jian");
	map_skill("claw", "youming-zhao");
	map_skill("force", "kuihua-shengong");
	prepare_skill("claw", "youming-zhao");

	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
//		(: exert_function, "yinyun" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.jue" :),
		(: perform_action, "sword.feiying" :),
	}));

	set_temp("apply/damage", 50);
	set_temp("apply/dodge", 120);
	set_temp("apply/attack", 80);
	set_temp("apply/armor", 170);
	set_temp("幽冥", 1);

	set("inquiry", ([
		"葵花寶典": (: ask_me :),
	]));

	setup();

	if (clonep()) {
		ob = unew(BOOK_D("kuihua"));
		if (!ob) ob = new("/clone/money/gold");
		ob->move(this_object());
		carry_object(BINGQI_D("xiuhua"))->wield();
		carry_object(ARMOR_D("xiupao2"))->wear();
	}
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BOOK_D("kuihua"))))
		ob->move(this_object());
}

string ask_me()
{
	object ob, me = this_player();
	mapping quest;
	int i, time;

	if ( is_busy() || is_fighting())
	 	return "你沒看到我正忙著麼？";

	if ( me->query("gender") == "女性")
		return "倘若我和你一樣，生為女兒身，那就好了。";

	if ( me->query("int") < 20 )
		return "你的靈性不夠，「葵花寶典」不適合你練習。";

	if ( me->query("dex") < 15 )
		return "「葵花寶典」講究的是騰挪之法，你的身法實在太低了。";

	if ( me->query("combat_exp", 1) < 5000000)
		return "你的實戰經驗還不夠，「葵花寶典」還不適合你修煉。";

	if ( present("kuihua baodian", me))
		return "咦？「葵花寶典」不是在你身上麼？還問我作甚？";

	ob = present("kuihua baodian", this_object());

	if ( ! ob)
		return "耶？「葵花寶典」給我放到那裡去了？";

	time = time() - me->query("quest/pixie/pxj_time");
	if ( me->query("quest/pixie/pxj_time") && time < 86400 && !wizardp(me))
	 	return "我現在很忙，沒興趣和你多羅嗦。";

	quest = me->query("quest/pixie");

	if ( ! quest || ! quest["pxj_passwd"])
		return "你從哪裡聽說到「葵花寶典」的？";

	if ( quest["pass"] ) {
		if ( ob ) {
			ob->set("owner", me);
			ob->move(me);
			return "好吧，這本「葵花寶典」你拿回去好好研究研究。";
		}
		else
			return "你要的「葵花寶典」已經給別人拿走了。";
	}

	i = me->query("combat_exp", 1) - 4500000;
	i /= 500000;

        if ( me->query("registered")< 3 && quest["fail"] >= i)
	 	return "我現在很忙，沒興趣和你多羅嗦！";
        if ( quest["fail"] >= i && !me->query("cw_exp") )
	 	return "我現在很忙，沒興趣和你多羅嗦！";
	me->set_temp("pxj_quest", 1);
	kill_ob(me);
	me->kill_ob(this_object());
	return "就憑你這"+RANK_D->query_rude(me)+"也敢來窺視我的「葵花寶典」！";
}

void die()
{
	object me = query_temp("last_damage_from");
	object ob = present("kuihua baodian", this_object());

	if ( ob ) {
		if ( 

                 objectp(me) 
                && me->query("kar") < 31 
                && random(me->query_int(1)) > 30
                &&random(me->query_dex(1)) > 35
                && random(me->query_con()) > 35
                && random(me->query("kar")) > 25
  && random(20) == 4
                      )
                {
			message_vision("\n", me);
			command("say 哈哈，你我也算是有緣之人，這本「葵花寶典」就交給你吧。");
			log_file("quest/pixie",
				sprintf(HIR"%-18s失敗%-2d次後，獲得「葵花寶典」，悟：%d，身：%d，福：%d。"NOR,
					me->name(1)+"("+capitalize(getuid(me))+")", 
					me->query("quest/pixie/fail"),
					me->query_int(1), 
					me->query_dex(1), 
					me->query_kar()
				), me
			);
			me->set("quest/pixie/pass", 1);
			me->delete("quest/pixie/pxj_time");
			me->delete_temp("pxj_quest");
			ob->set("owner", me);
			ob->move(me);
		}
		else {
			message_vision(CYN"\n$N怒叫道：「即使我死了，你等也休想得到「葵花寶典」，哈哈哈哈……」\n"NOR, this_object());
			message_vision("$N將那「葵花寶典」放在雙掌中一搓，功力到處，一本原已十分陳舊的冊頁登時化作碎片。\n\n", this_object());
			if ( objectp(me) && me->query_temp("pxj_quest")) {
				me->add("quest/pixie/fail", 1);
				me->set("quest/pixie/pxj_time", time());
				me->delete_temp("pxj_quest");
				log_file("quest/pixie", 
					sprintf("%-18s試圖獲得「葵花寶典」，失敗%-2d次，悟：%d，身：%d，福：%d。\n",
						me->name(1)+"("+capitalize(getuid(me))+")", 
						me->query("quest/pixie/fail"),
						me->query_int(1), 
						me->query_dex(1), 
						me->query_kar()
					), me
				);
			}
			ob->set("name", HIW"葵花寶典的碎片"NOR);
			ob->move(environment(this_object()));
		}
	}
	::die();
}

void unconcious()
{
	die();
}
                                                                                              

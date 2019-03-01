// fusigui.c
// Modify By River 98/12
// Modify by Lklv 2001.10.23
// make him job_npc
// Modify by tangfeng@SJ 2004

#include <ansi.h>
inherit NPC;

#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"
#define QUESTDIR3 "quest/天龍八部/蕭峰身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"

string ask_join();
string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();

void create()
{
	set_name("傅思歸", ({ "fu sigui", "fu", "sigui" }));
	set("title", "大理國鎮南王府家將");
	set("gender", "男性");
	set("age", 33);
	set("str", 25);
	set("unique", 1);
	set("dex", 25);
	set("long", "這人身穿軍服，三十來歲，虎背熊腰，手持一根熟銅棍。\n");
	set("combat_exp", 400000);
	set("shen_type", 1);
	set("attitude", "friendly");
	set("no_ansuan", 1);
	set("no_bark", 1);
	
	set("job_npc",1);

	set_skill("strike", 60);
	set_skill("club",90);
	set_skill("qiantian-yiyang", 100);
	set_skill("tianlong-xiang", 100);
	set_skill("qingyan-zhang", 80);
	set_skill("force", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("weituo-gun", 100);
	set_temp("apply/defense", 70);
	set_temp("apply/armor", 70);

	map_skill("force", "qiantian-yiyang");
	map_skill("strike", "qingyan-zhang");
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "qingyan-zhang");
	map_skill("club", "weituo-gun");
	prepare_skill("strike","qingyan-zhang");

	set("max_qi", 900);
	set("neili", 900);
	set("max_neili", 900);
	set("jiali", 20);
	set("inquiry",([
		"入官府" : (: ask_join :),
		"join" : (: ask_join :),
		"段譽" : (: askduanyu :),
		"大理" : "這裡便是大理。",
		"天龍寺" : "天龍寺是我段家武學的最高之地。",
		"天龍有難" : (: tianlonghelp :),
		"營救" : (: asksave :),
		"搭救" : (: asksave :),
		"蕭峰" : "江湖人稱南慕容、北蕭峰，端得一條好漢。",
		"營救段譽" : (: asksave :),
		"營救蕭峰" : (: askxiaofeng :),
		"慕容復" : "江湖人稱南慕容、北蕭峰，聽說慕容公子年級輕輕，卻無所不精。",
		"慕容博" : "我聽說是，姑蘇慕容不出的傑才，可惜英年早逝。",
		"鳩摩智" : (: askjiumozhi :),
		"六脈神劍" : "傳說的我天龍寺最高絕學，我估計這輩子也未能見到。",
	]));
	set("chat_chance", 3);
	set("chat_msg", ({
		CYN"傅思歸說道：「鎮南王廣招天下豪傑，誠心相待。作姦犯科，行為不軌的小人我們可不想招納。 」\n"NOR,
	}));

	setup();
	carry_object("/d/dali/wangfu/npc/obj/tonggun")->wield();
	carry_object("/d/dali/npc/obj/zipao")->wear();
}
string askjiumozhi()
{
	object me;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "聽說，大輪寺第一高僧鳩摩智將來我天龍寺佛法交流，真是我大理之幸啊。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "這魔僧竟然如此欺負我大理無人，什麼吐蕃國第一佛法高僧，狗P狗P。";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "鳩摩智妄為西域第一佛法高僧，所謂口生蓮花，全是一派胡言。";
  }
  command("nod");
	return "大輪明王鳩摩智是吐蕃國的護國法王，但聽說他具大智慧，精通佛法，想來武功也是驚人。";
}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("hoho");
  		return "江湖人稱南慕容、北蕭峰，端得一條好漢，何來援救之說。";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽說這件事情，只是涉及到大遼與大宋之爭，不知道主公怎麼處理。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
                  return "蕭峰，難不是你所迫出中原，今日所謂搭救不知什麼意思。假惺惺！";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽說這件事情，只是涉及到大遼與大宋之爭，不知道主公怎麼處理。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "蕭峰是我小王子的義兄，自然要救。這位"+RANK_D->query_respect(me) +"可先行一步，隨後我和我加小王子一起援到。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "這一戰真是痛快，"+me->query("name")+"更是威震武林，端得厲害啊。";
  }
  command("hoho");
	return "江湖人稱南慕容、北蕭峰，端得一條好漢，何來援救之說。";
}
string asksave()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start") &&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "小王子素來不喜武學，只愛佛法易經，平易近人，何來援救之說？";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽說，前段時間小王子和鎮南王又是吵架一番，至今未有回家，不知"+RANK_D->query_respect(me) +"可否幫助打聽一下。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "剛有探報，小王子被萬劫谷所盤留，只等主公的命令了，平了狗日的萬劫谷。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多謝"+RANK_D->query_respect(me) +"搭救小王子，只是自從萬劫谷回來，小王子精神恍惚，不知所中何毒還是受何種內傷。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小王子自萬劫谷回來，總是氣血不定，內力怪異，才被送往天龍求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "竟然惹出鳩摩智這等高手，但願王子吉人天相啊。";
  }
  command("hoho");
	return "小王子素來不喜武學，只愛佛法易經，平易近人，何來援救之說？";
}
string askduanyu()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "小王子素來不喜武學，只愛佛法易經。";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽說，前段時間小王子和鎮南王又是吵架一番，至今未有回家。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "剛有探報，小王子被萬劫谷所盤留，萬劫谷什麼地方啊。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多謝"+RANK_D->query_respect(me) +"搭救我家小王子。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小王子自萬劫谷回來，總是氣血不定，內力怪異，才被送往天龍求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "竟然惹出鳩摩智這等高手，但願王子吉人天相啊。";
  }
  command("hoho");
	return "段譽正是鎮南王之子。";
}
string tianlonghelp()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"over"))
  {
  	  command("haha");
  		return "天龍寺是我段家武學的最高之地，高手眾雲，請不要危言聳聽。";
  }
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "聽說，大輪寺高僧鳩摩智不日將來我天龍寺，不知是喜是禍。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
		  return "這魔僧竟然如此欺負我大理無人，什麼吐蕃國第一佛法高僧，狗P。";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "多謝"+RANK_D->query_respect(me) +"化解這場天龍危機，還將我大理小王子得以解救。";
  }
  command("hoho");
	return "天龍寺是我段家武學的最高之地，高手眾雲，請不要危言聳聽。";
}
string ask_join()
{
	object ob = this_player();

	if (ob->query("combat_exp")<3000)
		return ("你的武功太差，什麼也做不了的。\n");
	if (ob->query_temp("dali_join"))
		return RANK_D->query_respect(ob) + "已經是本王府隨從了，何故還要開這種玩笑？";
	if (ob->name() != ob->name(1)) {
		command("hmm " + ob->query("id"));
		return RANK_D->query_respect(ob) + "不肯以真面目示人，還是另謀高就吧！";
	}
	ob->set_temp("dali_join",1);
	command("look "+ob->query("id"));
	return "好，不錯，這位"+RANK_D->query_respect(ob)+"可以為本王府工作了。";
}

void kill_ob(object ob)
{
	mixed *local;
	object me = this_object();

	local = localtime(time() * 60);

	if ( local[2] >= 5 && local[2] < 20) {
		command("say 本官有要責在身，沒功夫陪你玩！"); 
		me->remove_enemy(ob);
		ob->remove_killer(me);
		return;
	}
}

int accept_fight(object ob)
{
	mixed *local;
	local = localtime(time() * 60);

	if ( local[2] >= 5 && local[2] < 20) {
		command("say 本官有要責在身，沒功夫陪你玩！");
		return 0;
	}
}

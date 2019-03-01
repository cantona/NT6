// king.c 段正明
// added by tangfeng@sj 2004

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"
#define QUESTDIR3 "quest/天龍八部/蕭峰身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"

string enter();
string qinwang(object ob);
string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();

void create()
{
	set_name("段正明", ({ "duan zhengming", "duan", "master" }) );
	set("nickname", HIW"保定帝"NOR);
	set("title","大理皇帝");
	set("gender", "男性" );

	set("age", 48);
	set("str", 28);
	set("con", 28);
	set("dex", 28);
	set("int", 28);
	set("per", 26);

	set("max_qi", 4000);
	set("max_jing", 3000);
	set("eff_jingli", 3000);
	set("neili", 4000);
	set("qi", 4000);
	set("jingli", 3000);
	set("max_neili", 4000);
	set("jiali", 80);

	set("rank_info/respect", "殿下");
	create_family("天龍寺", 13, "俗家弟子");
	set("long", "他看上去平易近人又頗有風度，氣宇軒昂，眉目之間透著一股逼人的英氣。\n");
	set("combat_exp", 1600000);
	set("score", 20000);

	set_skill("parry", 200);
	set_skill("dodge", 180);
	set_skill("qingyan-zhang", 180);
	set_skill("strike", 180);
	set_skill("buddhism",200);
	set_skill("force", 200);
	set_skill("literate", 150);
	set_skill("sword", 180);
	set_skill("duanjia-jianfa", 180);
	set_skill("cuff", 200);
	set_skill("duanjia-quan", 200);
	set_skill("yiyang-zhi", 200);
	set_skill("finger", 200);
	set_skill("qiantian-yiyang", 200);
	set_skill("tianlong-xiang", 200);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "duanjia-jianfa");
	map_skill("sword", "duanjia-jianfa");
	map_skill("force", "qiantian-yiyang");
	map_skill("cuff", "duanjia-quan");
	map_skill("strike", "qingyan-zhang");
	map_skill("finger","yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");
	set("inquiry", ([
		"入後宮" : (: enter :),
		"親王" : (: qinwang :),
		"name": "朕就是保定帝段正明。",
		"here": "這裡便是大理皇宮。",
		"段譽" : (: askduanyu :),
		"大理" : "這裡便是大理。",
		"天龍寺" : "天龍寺是我段家武學的最高之地，不過，想拜天龍寺可不是那麼容易的.",
		"天龍有難" : (: tianlonghelp :),
		"營救" : (: asksave :),
		"搭救" : (: asksave :),
		"蕭峰" : "江湖人稱南慕容、北蕭峰，端得一條好漢。",
		"營救段譽" : (: asksave :),
		"營救蕭峰" : (: askxiaofeng :),
		"慕容復" : "江湖人稱南慕容、北蕭峰，聽說慕容公子年級輕輕，卻無所不精。",
		"慕容博" : "姑蘇慕容不出的傑才，可惜英年早逝。",
		"鳩摩智" : (: askjiumozhi :),
		"六脈神劍" : "傳說的我天龍寺最高絕學，朕也未能得見。",
	]));

	setup();
	carry_object("/d/dali/npc/obj/huangpao")->wear();
	carry_object("/clone/weapon/gangjian")->wield();
}

void init()
{
	object ob,me;
	me=this_object();
	ob = this_player();
	::init();
	if (interactive(ob = this_player()) 
	 && living(this_object())
	 && (int)ob->query_temp("killqueen")) {
		command ("say 你竟敢殺我的皇後，納命來！\n");
		me->set_leader(ob);
		remove_call_out("kill_ob");
		call_out("kill_ob", 0, ob);
	}
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
		  return "這魔僧竟然如此欺負我大理無人，妄為吐蕃國第一佛法高僧，所謂口生蓮花，全是一派胡言。";
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
		  return "聽說這件事情，只是涉及到大遼與大宋之爭，實在不好插手。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
	  return "蕭峰，難不是你所迫出中原，今日所謂搭救不知何意。";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽說這件事情，只是涉及到大遼與大宋之爭，實在不好插手。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "蕭峰乃小侄之義兄，自然要救。這位"+RANK_D->query_respect(me) +"可先行一步，大理段家弟子隨後援到。";
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
  		return "段譽素來不喜武學，只愛佛法易經，平易近人，何來援救之說？";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽說，前段時間和鎮南王又是吵架一番，至今未有回家，不知"+RANK_D->query_respect(me) +"可否幫助打聽一下。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "剛有探報，小侄被萬劫谷所盤留，此事還請"+RANK_D->query_respect(me) +"速速前往萬劫谷一趟。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多謝"+RANK_D->query_respect(me) +"搭救小侄，只是自從萬劫谷回來，小侄精神恍惚，不知所中何毒還是受何種內傷。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "段譽自萬劫谷回來，總是氣血不定，內力怪異，才被送往天龍求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "竟然惹出鳩摩智這等高手，但願段譽吉人天相啊。";
  }
  command("hoho");
	return "段譽素來不喜武學，只愛佛法易經，平易近人，何來援救之說？";
}
string askduanyu()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "段譽正是朕之小侄，素來不喜武學，只愛佛法易經。";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽說，前段時間和鎮南王又是吵架一番，至今未有回家。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "剛有探報，小侄被萬劫谷所盤留，不得已只怕要走一次了。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多謝"+RANK_D->query_respect(me) +"搭救小侄。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "段譽自萬劫谷回來，總是氣血不定，內力怪異，才被送往天龍求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "竟然惹出鳩摩智這等高手，但願段譽吉人天相啊。";
  }
  command("hoho");
	return "段譽正是朕之小侄、鎮南王之子。";
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
		  return "這魔僧竟然如此欺負我大理無人，妄為吐蕃國第一佛法高僧。";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "多謝"+RANK_D->query_respect(me) +"化解這場天龍危機，還將我侄子得以解救。";
  }
  command("hoho");
	return "天龍寺是我段家武學的最高之地，高手眾雲，請不要危言聳聽。";
}
string enter()
{
	object ob;
	string target;
	ob = this_player();
	if ( ob->query("combat_exp") < 100000)
		return "你想進後宮幹嗎？";
	if ( ob->query_temp("fan")){
		string book;
		book=ob->query_temp("book_target");
		return("讓你去找"+book+CYN"，還不快去。"NOR);
	}
	switch  (random(8)){
		case 0: target = HIW"天神篇"NOR; break;
		case 1: target = HIW"龍神篇"NOR; break;
		case 2: target = HIW"夜叉篇"NOR; break;
		case 3: target = HIW"乾達婆篇"NOR; break;
		case 4: target = HIW"阿修羅篇"NOR; break;
		case 5: target = HIW"迦樓羅篇"NOR; break;
		case 6: target = HIW"緊那羅篇"NOR; break;
		case 7: target = HIW"摩呼羅迦篇"NOR; break;
	}
	ob->set_temp("fan",1);
	ob->set_temp("book_target",target);
	return "想入後宮，先幫我把天龍八部的"+target+CYN"找來。"NOR;
}

string qinwang(object ob)
{
	string new_title,title,*title1,*title2;
	mapping fam;
	ob=this_player();
	fam = ob->query("family");
	title1 =({ "承","平","定","乾","滇" });
	title2 =({ "東","南","西","北" });
	if ((!fam)||(fam["family_name"] != "天龍寺"))
		return RANK_D->query_respect(ob)+"與本國素無來往，不知此話從何談起？";
	if (ob->query("tls") || ob->query("class")=="bone")
		return RANK_D->query_respect(ob) + "已經貴為天龍寺高僧，這個親王顯然是不適合你的。";
	if (ob->query("job_time/大理") < 3000 && ob->query_skill("qiantian-yiyang",1) < 160)
		return RANK_D->query_respect(ob) + "為大理做的還不夠，就想成為王爺了？";
	if (stringp(ob->query("qinwang")))
		return RANK_D->query_respect(ob) + "已經是我朝親王了，怎麼還來打聽？";
	title= title1[random(sizeof(title1))]+title2[random(sizeof(title2))]+"王";
	new_title= "大理國"+title;
	ob->set("title",HIW + new_title + NOR);
	ob->set("qinwang", title);
	command("chat 哈哈哈，即日起朕封" + ob->query("name")+"為我"+new_title+"。");
	return "好吧，看你勞苦功高，朕就封你為"+ new_title +"。";
}

void attempt_apprentice(object ob)
{
	string name, new_name, *prename;
	prename = ({ "段", "段" });
	if (ob->query("tls")&&ob->query("class")=="bone") {
		command ("say 你已經是天龍寺出家弟子了，我不能再收你了！");
		return;
	}
	if( (int)ob->query_skill("qiantian-yiyang",1) < 140 ){
		command ("hmm");
		command ("say 你乾天一陽功如此之差，我可不收你！");
		return;
	}
	if(ob->query_int() < 33){
		command("say 武學之道必須悟性高，依我看" + RANK_D->query_respect(ob) + "的資質似乎不夠？");
		return;
	}
	if(ob->query("shen") < 0){
		command("say 大理乃堂堂皇室，而這位" + RANK_D->query_respect(ob) + "眼露兇光，我看不適合在我大理呆下去了。");
		return;
	}
	command("smile");
	command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
	name = ob->query("name");
	new_name = prename[random(sizeof(prename))] + name[<4..<1];
	command("say 入我段家，從今以後你的名字就叫做" + new_name + "。");
	ob->set("name", new_name);
	command("recruit " + ob->query("id") );
	if (!ob->query("qinwang")) ob->set("title","大理國御前侍衛");
}

void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	ob->set("class", "officer");
}

int accept_object(object who, object ob)
{
	string bookname;
	bookname=ob->query("name");
	if ((bookname!=HIW"天神篇"NOR)
	 &&(bookname!=HIW"龍神篇"NOR)
	 &&(bookname!=HIW"夜叉篇"NOR)
	 &&(bookname!=HIW"乾達婆篇"NOR)
	 &&(bookname!=HIW"阿修羅篇"NOR)
	 &&(bookname!=HIW"迦樓羅篇"NOR)
	 &&(bookname!=HIW"緊那羅篇"NOR)
	 &&(bookname!=HIW"摩呼羅迦篇"NOR))
		return notify_fail("段正明對你搖頭道：我要這東西沒用啊。\n");
	if ( bookname==this_player()->query_temp("book_target")){
		if ( ob->query_temp("find") == who->query("id")){
			command("smile");
			command("say 很好，你可以進後宮了。");
			who->set_temp("enter",1);
			who->delete_temp("book");
			call_out("destroying", 1, ob);
			return 1;
		}
		command("hmm");
		command("say 這好象不是你找到的吧。");
		call_out("destroying", 1, ob);
		return 1;
	}
	else {
		command("hmm");
		command("say 這不是我要的書，你再去找。");
		call_out("destroying", 1, ob);
		return 1;
	}
}

void destroying(object ob)
{
	destruct(ob);
	return;
}

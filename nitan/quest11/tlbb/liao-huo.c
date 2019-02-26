//added by tangfeng@SJ 2004


inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR "quest/天龍八部/"
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"
#define QUESTDIR3 "quest/天龍八部/蕭峯身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"
#define QUESTDIR6 "quest/天龍八部/武功/"

string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();
string ask_for_join();

void create()
{
        set_name("了惑禪師", ({ "liaohuo chanshi","liaohuo","chanshi"}) );
        set("nickname", "漏盡尊者");
        set("long", "了惑禪師是本因方丈的第五位弟子，他年約四十，
紅光滿面。現掌理寺中待客迎賓之職，別看他笑容可
鞠，行事卻最是穩重、沉着。\n");
        set("gender", "男性" );
        set("class", "bonze");
        set("attitude", "friendly");
        set("age", 41);
        set("shen_type", 1);
        set("str", 22);
        set("int", 22);
        set("con", 23);
        set("dex", 22);
        create_family("天龍寺", 14, "弟子");
        set("unique", 1);
        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 1400);
        set("max_neili", 1400);
        set("jiali", 50);
        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 80);
        set_skill("qiantian-yiyang", 90);
        set_skill("dodge", 80);
        set_skill("tianlong-xiang", 80);
        set_skill("parry", 80);
        set_skill("duanjia-jianfa", 80);
        set_skill("strike", 80);
        set_skill("sword", 80);
        set_skill("buddhism", 80);
        set_skill("literate", 80);
        set_skill("qingyan-zhang", 80);
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "qingyan-zhang");
        map_skill("sword", "duanjia-jianfa");
        map_skill("strike", "qingyan-zhang");
        prepare_skill("strike","qingyan-zhang");                
        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
            		"段譽" : (: askduanyu :),
		            "大理" : "這裏便是大理。",
		            "天龍寺" : "這裏正是天龍寺，大理段家武學的最高之地。",
		            "天龍有難" : (: tianlonghelp :),
		            "營救" : (: asksave :),
		            "搭救" : (: asksave :),
		            "蕭峯" : "江湖人稱南慕容、北蕭峯，端得一條好漢。",
		            "營救段譽" : (: asksave :),
		            "營救蕭峯" : (: askxiaofeng :),
		            "慕容復" : "江湖人稱南慕容、北蕭峯，聽説慕容公子年級輕輕，卻無所不精。",
		            "慕容博" : "我聽説是，姑蘇慕容不出的傑才，可惜英年早逝。",
		            "鳩摩智" : (: askjiumozhi :),
		            "六脈神劍" : "傳説的我天龍寺最高絕學，我估計這輩子也未能見到。",
	]));
        setup();
        carry_object(BINGQI_D("changjian"))->wield(); 
        carry_object("/d/tls/obj/jiasha1")->wear(); 
        carry_object("/d/tls/obj/sengxie")->wear();
}
#include "liao.h";
void init()
{
	object me;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
	 	if(me->query(QUESTDIR2+"start")&& !me->query(QUESTDIR2+"over"))
    {
    	command("look "+me->query("id"));
    	command("touch "+me->query("id"));
    	command("say 有這位大俠幫忙，本寺當可高枕無憂了。"); 
    }
	} 
}
string askjiumozhi()
{
	object me;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "聽説，大輪寺第一高僧鳩摩智將來我天龍寺佛法交流，真是我大理之幸啊。";
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
  /*
  大輪明王鳩摩智是吐蕃國的護國法王，但只聽説他具大智慧，精通佛法，每隔五年，開壇講經説法，西域天竺各地的高僧大德，
  雲集大雪山大輪寺，執經問難，研討內典，聞法既畢，無不歡喜讚歎而去。
  */
  command("nod");
	return "大輪明王鳩摩智是吐蕃國的護國法王，但聽説他具大智慧，精通佛法，想來武功也是驚人。";
}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("hoho");
  		return "江湖人稱南慕容、北蕭峯，端得一條好漢，何來援救之説。";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽説這件事情，只是天龍寺向來不涉及武林之爭。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
		  return "喬峯，難不是你所迫出中原，今日所謂搭救不知什麼意思。假惺惺！";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽説這件事情，只是天龍寺向來不涉及武林之爭。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "聽説這件事情，只是天龍寺向來不涉及武林之爭。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "聽説那一戰，"+me->query("name")+"更是威震武林，端得厲害啊。";
  }
  command("hoho");
	return "江湖人稱南慕容、北蕭峯，端得一條好漢，何來援救之説。";
}
string asksave()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start") &&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "小王子素來不喜武學，只愛佛法易經，平易近人，何來援救之説？";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽説，前段時間小王子和鎮南王又是吵架一番，至今未有回家，不知大俠可否幫助打聽一下。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽説這件事情，只是天龍寺向來不涉及武林之爭。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "只是自從萬劫谷回來，小王子精神恍惚，不知所中何毒還是受何種內傷。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小王子自萬劫谷回來，總是氣血不定，內力怪異，才被送往我天龍寺求救來了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "竟然惹出鳩摩智這等高手，但願王子吉人天相啊。";
  }
  command("hoho");
	return "小王子素來不喜武學，只愛佛法易經，平易近人，何來援救之説？";
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
		  return "聽説，前段時間小王子和鎮南王又是吵架一番，至今未有回家。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽説這件事情，只是天龍寺向來不涉及武林之爭。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多謝大俠搭救小王子。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小王子自萬劫谷回來，總是氣血不定，內力怪異，才被送往天龍求救來了。";
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
		  return "聽説，大輪寺高僧鳩摩智不日將來我天龍寺，不知是喜是禍。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
		  return "這魔僧竟然如此欺負我大理無人，什麼吐蕃國第一佛法高僧，狗P。";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "多謝大俠化解這場天龍危機，還將我大理小王子得以解救。";
  }
  command("hoho");
	return "天龍寺是我段家武學的最高之地，高手眾雲，請不要危言聳聽。";
}
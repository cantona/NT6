//tangfeng@SJ 2004
#include <ansi.h>
inherit NPC;

#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"
#define QUESTDIR3 "quest/天龍八部/蕭峯身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"

string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();
string huanggong();

void create()
{
        set_name("范曄", ({ "fan ye", "fan"}));
        set("title", "大理國司馬");
        set("gender", "男性");
        set("age", 40);
        set("str", 28);
        set("dex", 20);
        set("long", "此人中等身材，身着錦緞官服，目光如炬，顯是
精明人物，尤擅謀略，居大理為官多年功勛赫赫。\n");
        set("max_qi", 2500);
        set("max_jing", 1000);
        set("neili", 2500);
        set("max_neili", 2500);        
        set("eff_jingli",1000);
        set("jiali",50);
        set("combat_exp", 700000);
        set("shen_type", 1);
        set("attitude", "peaceful");
//      create_family("大理", 3 , "弟子");
         
        set_skill("force",120);
        set_skill("sword",135);
        set_skill("strike",130);
        set_skill("qingyan-zhang",130);
        set_skill("dodge",100);
        set_skill("tianlong-xiang",100);
        set_skill("parry",120);
        set_skill("qiantian-yiyang",120);
        set_skill("duanjia-jianfa",135);
        map_skill("parry", "duanjia-jianfa");
        map_skill("dodge", "tianlong-xiang");
        map_skill("strike","qingyan-zhang");
        map_skill("force", "qiantian-yiyang");
        map_skill("sword", "duanjia-jianfa");
        prepare_skill("strike","qingyan-zhang");
	set("inquiry",([
		"段譽" : (: askduanyu :),
		"大理" : "這裏便是大理。",
		"天龍寺" : "天龍寺是我段家武學的最高之地。",
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
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/damage", 20);        
        
        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/d/dali/npc/obj/zipao")->wear();
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
		  return "聽説這件事情，只是涉及到大遼與大宋之爭，不知道主公怎麼處理。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
                  return "蕭峯，難不是你所迫出中原，今日所謂搭救不知什麼意思。假惺惺！";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "聽説這件事情，只是涉及到大遼與大宋之爭，不知道主公怎麼處理。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "蕭峯是我小王子的義兄，自然要救。這位"+RANK_D->query_respect(me) +"可先行一步，隨後我和我加小王子一起援到。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "這一戰真是痛快，"+me->query("name")+"更是威震武林，端得厲害啊。";
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
		  return "聽説，前段時間小王子和鎮南王又是吵架一番，至今未有回家，不知"+RANK_D->query_respect(me) +"可否幫助打聽一下。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "我知道了，我馬上就去，一會叫上華赫艮。";
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
		  return "多謝"+RANK_D->query_respect(me) +"化解這場天龍危機，還將我大理小王子得以解救。";
  }
  command("hoho");
	return "天龍寺是我段家武學的最高之地，高手眾雲，請不要危言聳聽。";
}

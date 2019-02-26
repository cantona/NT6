//update by cool 98.2.18
//added by tangfeng 2004
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

int ask_xingyue(object who);
//string ask_liumai1();
string ask_liumai2();
int ask_dudan(object who);   

void create()
{
	object ob;
        set_name("枯榮長老", ({ "kurong zhanglao","kurong","zhanglao"}) );
        set("nickname", "天龍寺長老");
	set("long", 
" 枯榮長老面容奇特之極，左邊的一半臉色紅潤，
皮光肉滑，有如嬰兒，右邊的一半卻如枯骨，除了
一張焦黃的麪皮之外全無肌肉，骨頭突了出來，宛
然便是半個骷髏骨頭。他在天龍寺中輩份最高，在
這裏獨參枯禪已數十年，天龍寺諸僧眾，誰也沒見
過他真面目。\n");
        set("gender", "男性" );
        set("class","bonze");   
        set("unique", 1);
        set("age", 99);
        set("str", 30);
        set("cor", 27);
        set("cps", 32);
        set("int", 35);
        set("per",23);

        set("max_jing",5000);
        set("eff_jingli", 6500);
        set("max_qi", 9500);
        set("jiali",100);
        set("neili",17000);
        set("max_neili",17000); 
        set("rank_info/respect", "高僧");
        create_family("天龍寺", 12, "僧侶");
        set("combat_exp", 4350000);
        set("score", 0);

        set("chat_chance_combat", 80);
        set("chat_msg_combat",({ 
                (: exert_function, "ku" :),
                (: perform_action, "finger.sanmai" :),
                (: perform_action, "finger.sandie" :),
        }));
        set_skill("parry", 340);
        set_skill("dodge", 340);
        set_skill("force", 360);
        set_skill("finger", 350);
        set_skill("whip", 320);
        set_skill("liumai-jianzhen",200);
        set_skill("cihang-bian", 320);
        set_skill("duanjia-jianfa", 300);
        set_skill("sword", 300);
        set_skill("strike", 340);
        set_skill("buddhism", 200);
        set_skill("literate", 200);
        set_skill("qiantian-yiyang", 220);
        set_skill("liumai-shenjian", 40);
        set_skill("kurong-changong", 360);
        set_skill("qingyan-zhang", 280);
        set_skill("yiyang-zhi", 340);
        set_skill("tianlong-xiang", 340);

        map_skill("whip", "cihang-bian");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "kurong-changong");
        map_skill("finger", "yiyang-zhi");
        map_skill("strike","kurong-changong");
        map_skill("force", "kurong-changong");
        prepare_skill("finger","yiyang-zhi"); 

        set_temp("apply/armor", 60);
        set_temp("apply/attack", 60);
        set_temp("apply/damage", 60);

        set("inquiry", ([
		"name": "貧僧就是枯榮",
		"菩提" : (: ask_xingyue :),
		"毒丹" : (: ask_dudan :),
		"普雲洞" : (: ask_liumai2 :),
		//"段譽" : (: ask_liumai1 :),
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
		            "六脈神劍" : "傳説的我天龍寺最高絕學，需要極深內力才能運用。",
	]));

        set("env/一陽指", 3);
        setup();
        
        if (clonep(this_object())) {
		if (ob = carry_object("/clone/weapon/xingyue"))
		ob->wield(); 
	}
	carry_object("/d/tls/obj/jiasha")->wear();
	carry_object("/d/tls/obj/sengxie")->wear();
}

void reset()
{
	object ob;
	if (clonep() && (ob = unew(BINGQI_D("xingyue")))) {
		ob->move(this_object());
		command("wield xingyue puti");
        }
}

#include "kurong.h"

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
		  return "這魔僧竟然如此欺負我大理無人，妄為吐蕃國第一佛法高僧。";
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
		  return "喬峯，難不是你所迫出中原，今日所謂搭救不知何意！";
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
		  return "聽説，前段時間小王子和鎮南王又是吵架一番，至今未有回家，不知"+RANK_D->query_respect(me) +"可否幫助打聽一下。";
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
		  return "我佛慈悲。只是自從萬劫谷回來，小王子精神恍惚，不知所中何毒還是受何種內傷。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。小王子自萬劫谷回來，總是氣血不定，內力怪異，才被送往我天龍寺求救來了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。竟然惹出鳩摩智這等高手，但願王子吉人天相啊。";
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
  		return "你問譽兒啊，他是鎮南王正淳的公子，聽説天資聰明，生性淳厚，只是素來不喜武學，只愛佛法易經。";
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
		  return "我佛慈悲。多謝"+RANK_D->query_respect(me) +"搭救小王子。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。小王子自萬劫谷回來，總是氣血不定，內力怪異，才被送往天龍求救來了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。竟然惹出鳩摩智這等高手，但願王子吉人天相啊。";
  }
  command("hoho");
	return "你問譽兒啊，他是鎮南王正淳的公子，聽説天資聰明，生性淳厚。";
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
  	  command("heng");
		  return "我佛慈悲。這魔僧竟然如此欺負我大理無人，妄為吐蕃國第一佛法高僧。";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "我佛慈悲。多謝"+RANK_D->query_respect(me) +"化解這場天龍危機，還將我大理小王子得以解救。";
  }
  command("hoho");
	return "我佛慈悲。天龍寺是我段家武學的最高之地，高手眾雲，請不要危言聳聽。";
}
/*
string ask_liumai1()
{
        object ob;
        ob=this_player();

	if( ob->query("dali/meet_dy1")||ob->query("liumai_update")){
		ob->set_temp("liumai/update",1);
		return "唉，求佛祖保佑,譽兒前日被大雪山大輪明王鳩摩智給抓走了，\n"+
			"譽兒生性淳厚，定能逢凶化吉。阿彌陀佛! \n";
	}
	else if( ob->query("dali/meet_dy2")){
		return "聽説譽兒已經被人搭救回來了，真是萬幸啊！阿彌陀佛！ \n";
	}
	return "你問譽兒啊，他是鎮南王正淳的公子，聽説天資聰明，生性淳厚。 \n";
}
*/
// cool 980310
// duan1.c
// Modify By River 98/11
//COOL@SJ,990828
// tangfeng@SJ 2004

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

#define QUESTDIR "quest/天龍八部/"
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"
#define QUESTDIR3 "quest/天龍八部/蕭峰身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"
#define QUESTDIR6 "quest/天龍八部/武功/"

string ask_join();
string ask_duan();
string strike();
string fenglu();
string ask_save();
string tianlonghelp();
string askxiaofeng();
string askjiumozhi();

void create()
{
	set_name("段正淳", ({ "duan zhengchun", "duan", "master" }) );
	set("title", "鎮南王");
	set("nickname","風流王爺");
	set("gender", "男性" );
	set("age", 44);
	set("str", 22);
	set("con", 23);
	set("dex", 23);
	set("int", 25);
	set("per", 28);
	set("attitude", "friendly");


	set("max_qi", 3000);
	set("max_jing", 1800);
	set("eff_jingli", 1800);
	set("neili", 3000);
	set("qi", 3000);
	set("jingli", 1800);
	set("max_neili", 3000);
	set("jiali", 50);

	set("rank_info/respect", "風流王爺");
	create_family("天龍寺", 13, "俗家弟子");

	set("long",
	"段正淳是個相當高大的中年儒生，若不是跟隨在他左右的鐵甲衛士成群，\n"
	"你大概猜不到眼前這個溫文儒雅的中年人竟是大理王爺。\n");

	set("combat_exp", 1100000);
	set("score", 50000);

	set("chat_chance_combat", 30);
	set("chat_msg_combat",({
		(: perform_action, "sword.fenglei" :),
		(: exert_function, "qi" :)
	}));

	set_skill("parry", 150);
	set_skill("dodge", 150);
	set_skill("force", 150);
	set_skill("cuff", 150);
	set_skill("literate", 120);
	set_skill("sword", 160);
	set_skill("duanjia-jianfa", 160);
	set_skill("strike", 150);
	set_skill("qingyan-zhang", 150);
	set_skill("qiantian-yiyang", 150);
	set_skill("duanjia-quan", 150);
	set_skill("tianlong-xiang", 150);
	set_skill("finger", 150);
	set_skill("yiyang-zhi", 160);
	set_skill("buddhism", 100);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "qingyan-zhang");
	map_skill("sword", "duanjia-jianfa");
	map_skill("cuff", "duanjia-quan");
	map_skill("force", "qiantian-yiyang");
	map_skill("strike", "qingyan-zhang");
	map_skill("finger", "yiyang-zhi");
	prepare_skill("strike","qingyan-zhang");
	prepare_skill("cuff","duanjia-quan");

	set("inquiry", ([
		"段譽" : (: ask_duan :),
		"name": "你問這幹嘛，我就是段正淳，難道你又是我情人生的孩子？",
		"here": "這裡便是鎮南王府。",
		"天龍寺" : "天龍寺是我段家武學的最高之地，不過，想拜天龍寺可不是那麼容易的.",
		"拜天龍" : (: ask_join :),
		"拜天龍寺" : (: ask_join :),
		"掌法訣要" : (: strike :),
		"練掌法" : (: strike :),
	//	"俸祿" :  (: fenglu :),
		"營救" : (: ask_save :),
		"解救" : (: ask_save :),
		"援救" : (: ask_save :),
		"救援" : (: ask_save :),
		"save" : (: ask_save :),
		"搭救" : (: ask_save :),		
		"大理" : "這裡便是大理。",
		"天龍寺" : "天龍寺是我段家武學的最高之地，不過，想拜天龍寺可不是那麼容易的.",
		"天龍有難" : (: tianlonghelp :),
		"蕭峰" : "江湖人稱南慕容、北蕭峰，端得一條好漢。",
		"營救段譽" : (: ask_save :),
		"救援段譽" : (: ask_save :),
		"援救段譽" : (: ask_save :),
		"救援蕭峰" : (: askxiaofeng :),
		"援救蕭峰" : (: askxiaofeng :),
		"解救蕭峰" : (: askxiaofeng :),
		"營救蕭峰" : (: askxiaofeng :),
		"慕容復" : "江湖人稱南慕容、北蕭峰，聽說慕容公子年級輕輕，卻無所不精。",
		"慕容博" : "姑蘇慕容不出的傑才，可惜英年早逝。",
		"鳩摩智" : (: askjiumozhi :),
         "六脈神劍" : "傳說的我天龍寺最高絕學，我也未能得見。",          
	]));

	setup();
	carry_object("/d/dali/npc/obj/huangpao")->wear();
	carry_object("/clone/weapon/gangjian")->wield();
}
void init()
{
	object ob,me;
	ob =this_object();
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
		if(this_player()->query("quest/dali"))
		{
			tell_object(me,HIY"\n鑒于新Quest，系統自動轉換標志搜索：\n"NOR);
			if(this_player()->query("quest/dali/fail"))
			{
				this_player()->set(QUESTDIR6+"fail",this_player()->query("quest/dali/fail"));
				tell_object(me,HIY"原有"+chinese_number(this_player()->query("quest/dali/fail"))+"次失敗紀錄轉換成功！\n"NOR); 
				this_player()->delete("quest/dali/fail");
			}
			if(this_player()->query("quest/dali/time"))
			{
				this_player()->set(QUESTDIR+"time",this_player()->query("quest/dali/time"));
				tell_object(me,HIY"上次解密時間標志轉換成功！\n"NOR);  
				this_player()->delete("quest/dali/time");
			}
			if(this_player()->query("quest/dali/shanlu"))
			{
				this_player()->set(QUESTDIR1+"pass_shanlu",1);
				tell_object(me,HIY"成功通過荊棘林標志轉換成功！\n"NOR);  
				this_player()->delete("quest/dali/shanlu");
			}
			if(this_player()->query("quest/dali/yuxiang"))
			{
				this_player()->set(QUESTDIR6+"yuxiang",1);
				tell_object(me,HIY"磕頭玉像標志轉換成功！\n"NOR);
				this_player()->delete("quest/dali/yuxiang");
			}
			if(this_player()->query("quest/dali/pass"))
			{
				this_player()->set(QUESTDIR6+"pass",1);
				this_player()->set(QUESTDIR6+"yuxiang",1);
				tell_object(me,HIY"凌波微步標志轉換成功！\n\n"NOR);
				this_player()->delete("quest/dali/pass");
			}
			this_player()->delete("quest/dali");
			tell_object(me,HIY"\n新舊系統自動轉換結束！\n\n"NOR);
		}
		if(this_player()->query(QUESTDIR6+"pass") && !this_player()->query(QUESTDIR1+"wuliangover"))
					this_player()->set(QUESTDIR6+"yuxiang",1);
		if(me->query(QUESTDIR1+"over"))
			command("thank "+me->query("id"));
		if(!me->query_condition("killer")&& me->query_temp(QUESTDIR1+"see_duanyu1")&&!me->query(QUESTDIR1+"wuliangover"))
		{
			command("look "+me->query("id"));
			tell_object(me,HIY"\n你上前告訴"+ob->name()+"，說在無量山發現段譽，大可放心！\n"NOR);
			command("oh");
			command("jump "+me->query("id"));
			message_vision(HIC"$n向$N表示真誠的感謝。\n", me, this_object());
			command("touch "+me->query("id"));
			command("say 那我也完全放心了，想來這幾天犬子就會回來的。"); 
			me->delete_temp("quest/busy");//任務系統沖突標志
			me->delete_temp("quest/天龍八部");   
			me->set(QUESTDIR1+"wuliangover",1);   
			//設定標志
			me->set(QUESTDIR+"time",time());
			me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		}
	} 
}

string ask_duan()
{
	object me;
	object *obj;
	int x;
	me = this_player();
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
           return "小兒和中原官府應該沒有半點關系，"+RANK_D->query_respect(me) +"還是自我小心通緝！";
	}
  if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
  { 
      message_vision(HIC"$N臉上露出氣憤的神色。\n", this_object());
  	  command("heng");
	  obj = users();
	  x = sizeof(obj);
	  while(x--) {
		  if ( (obj[x]->query_temp(QUESTDIR1+"jianying")
                          ||obj[x]->query_temp(QUESTDIR1+"start"))
			  && obj[x]!=me) 
			  return "不過，"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已經在幫我了，"+RANK_D->query_respect(me) +"不用那麼著急！";		  
	  }
  	  //設定標志
  	  me->set(QUESTDIR+"time",time());
  	  me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
  	  me->set(QUESTDIR1+"start",1);
      me->set_temp(QUESTDIR1+"start",1);
	  me->set_temp("quest/busy",1);//與任務系統沖突標志
	  log_file("quest/TLBB", sprintf("%s(%s) 開始天龍八部第一部分。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	  return "小兒不愛學武，和我吵了幾句就離家出走了，唉......家門不幸啊！";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
	  message_vision(HIC"$N臉上露出氣憤的神色。\n", this_object());
  	  command("sigh");
  	  command("shrug "+me->query("id"));
	  return "前段時間有人說在無量山附近看到小兒，不知道現在身在何處。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
 
  	  command("sigh");
  	  message_vision(HIC"$N臉上露出擔心的神色。\n", this_object());
  	  //時間一天
  	  if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
	  {
		  if(random(2)) return "今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
		  else return "譽兒這幾天就可能回來了，"+RANK_D->query_respect(me) +"先行休息去吧！";
	  }
	  me->set_temp(QUESTDIR1+"2_start",1);
	  return "小兒日前被四大惡人的南海鱷神擄走了，我們正在設法營救他，有來報目前就在無量山附近的一座石屋內。";
	}
	if (me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"2_start") && !me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  message_vision(HIC"$N臉上露出擔心的神色。\n", this_object());
  	  command("shrug "+me->query("id"));
	  return "剛有探報，小兒確實就在無量山附近的一座石屋內，不得已只怕要走一次了。";
  }
  if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("look "+me->query("id"));
  	  command("nod "+me->query("id"));
  	  message_vision(HIC"$n向$N表示真誠的感謝。\n", me, this_object());
	  return "剛有探報，小兒確實就在無量山附近的一座石屋內，不過，有"+RANK_D->query_respect(me) +"相助，料無大礙。";
  }
  if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
  	  message_vision(HIC"$n向$N表示真誠的感謝。\n", me, this_object());
	  return "多謝"+RANK_D->query_respect(me) +"搭救小兒，只是這萬劫谷之後，身體一直不調，才被送往天龍寺求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小兒自萬劫谷回來，總是氣血不定，內力怪異，才被送往天龍求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
		  return "竟然惹出鳩摩智這等高手，但願小兒吉人天相啊。";
  }
  command("nod "+me->query("id"));
	return "段譽正是犬子，不知道找他何事。";
}

string ask_save()
{
	object me;
	object *obj;
	int i,j,x;
	i=random(5)+2;
	j=random(4)+3;
	me=this_player();

  if(!me->query(QUESTDIR1+"start" ))
  {
  	  command("?");
  		return "小兒向來只愛佛法已經，平易近人，援救之說何來之說？";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("shrug "+me->query("id"));
		  return "前段時間有人說在無量山附近看到小兒，這等貪玩，就讓他去吧。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"wuliangover")&& !me->query_temp(QUESTDIR1+"2_start")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
		  return "小兒最近收了個莫名其妙的弟子，好像叫什麼南海鱷魚？我總是擔心啊，千萬不要出什麼亂子。";
  }
	if (me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"2_start") && !me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
		if ( me->query("shen") < 0)
		           return ("我看" + RANK_D->query_respect(me) +"面帶陰邪之氣，恐怕是四大惡人一伙的姦細。");
    	if ( me->query("combat_exp") < 1500000)
		           return ("四大惡人都是絕頂高手,"+RANK_D->query_respect(me) +"似乎武功不夠，和四大惡人相鬥會有性命之憂。");
  		me->set_temp(QUESTDIR1+"step",i);
	  	me->set_temp(QUESTDIR1+"steps",j);
  	  command("look "+me->query("id"));
   	  //增加時間和經驗間隔限制
  	  //時間一天
  	  if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
	  {
		  if(random(2)) return "今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
		  else return "譽兒被那四大惡人擒走，這件事還需從長計議，"+RANK_D->query_respect(me) +"千萬不得魯莽。";
	  }
	  //考慮很多限制，這裡經驗差距變得少一點
	  if(me->query(QUESTDIR+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<100000)
		  return "以"+RANK_D->query_respect(me) +"目前的經驗就算目前有情況，也幫不上什麼忙，還是抓緊練功吧！";

	  obj = users();
	  x = sizeof(obj);
	  while(x--) {
		  if ( obj[x]->query_temp(QUESTDIR1+"yingjiu")&& obj[x]!=me) 
			  return ""+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已經在幫我了，"+RANK_D->query_respect(me) +"還是抓緊練功吧！";		  
	  }

  	  //設定標志
  	  me->set(QUESTDIR+"time",time());
  	  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
  	  command("touch "+me->query("id"));
  	  me->set_temp(QUESTDIR1+"yingjiu",1);
	  me->set_temp("quest/busy",1);//與任務系統沖突標志
	  log_file("quest/TLBB", sprintf("%s(%s) 開始準備營救段譽（第一章）。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	  return ("既然"+ RANK_D->query_respect(me) +"有意相助，定會如虎添翼。居我得知，譽兒被四大惡人之首\n"+
			"段延慶囚在正在無量山附近的一座石屋內，只是路上十分險惡，之前為了探明路線，\n"+
			"我已損失好幾名手下。你先去大理北面去無量山路上的一個小溪那裡，向北行五裡，\n"+
			"再向西行"+chinese_number(j)+"裡，再向北行"+chinese_number(i)+"裡，然後會到一座高山，再往後就要見機行事了。\n\n"+
			"段正淳說道：好了，準備一下，為了不驚動對方，切記要在晚上行動，路上小心。");
  }
  if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("look "+me->query("id"));
  	  command("touch "+me->query("id"));
                  return "有"+RANK_D->query_respect(me) +"相助，料無大礙。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多謝"+RANK_D->query_respect(me) +"搭救小兒，只是這萬劫谷之後，身體一直不調，才被送往天龍寺求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小兒自萬劫谷回來，總是氣血不定，內力怪異，才被送往天龍求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
  	  command("look "+me->query("id"));
		  return "竟然惹出鳩摩智這等高手，但願小兒吉人天相啊。";
  }
  command("nod "+me->query("id"));
	return "小兒向來只愛佛法已經，平易近人，援救之說何來之說？";
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
		  return "蕭峰乃小兒之義兄，自然要救。這位"+RANK_D->query_respect(me) +"可先行一步，大理段家弟子隨後援到。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "這一戰真是痛快，"+me->query("name")+"更是威震武林，端得厲害啊。";
  }
	return "江湖人稱南慕容、北蕭峰，端得一條好漢，何來援救之說。";
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
string strike()
{
	mapping fam = this_player()->query("family");
	object ob;
	if(!fam || fam["family_name"] != "天龍寺")
		return RANK_D->query_respect(this_player())+"與本派素無來往，不知此話從何談起？";
	if(this_player()->query_skill("strike",1) > 30)
		return "你的掌法已經有一定基礎了，這本書對你沒什麼用，還是留給別的弟子吧";
	ob = unew("/d/dali/obj/book-strike");
	if(!clonep(ob))
		return "你來晚了，本派的「掌法訣要」不在此處。";
	if(clonep(ob) && ob->violate_unique()){
		destruct(ob);
		return "你來晚了，本派的「掌法訣要」不在此處。";
	}
	ob->move(this_player());
	return "好吧，這本「掌法訣要」你拿回去好好鑽研。";
}

string ask_join()
{
	object me;
	object ob;
	ob=this_player();
	me=this_object();
	if (ob->query("tls"))
		return "你已經是天龍寺出家弟子了，何故還要問此事？";

//	if (ob->query("combat_exp") > 100000)
//		return "大理段氏在大理還需要你這樣的人才，就不要去天龍寺出家吧。";

	if(ob->query_temp("tls_app"))
		return "我不是已經推薦你去天龍寺了嗎？怎麼還不去啊？";

	if((string)ob->query("gender") == "女性" )
		return "天龍寺武功需要純陽之體，小姑娘可不收啊! ";

	if((int)ob->query_skill("qiantian-yiyang",1) < 120  )
		return RANK_D->query_respect(ob) +"，你乾天一陽功太差,不能學習高等級的功夫!";

	if ( ob->query("job_time/大理") + ob->query("job_time/送信")  < 50)
		return "我看你為鎮南王府做事做的還不夠啊，努力做吧！";

	if ( ob->query_int() < 30 )
		return "天龍寺武學深奧，我看你的悟性似乎不夠，恐怕無法領會這麼高的功夫!";

	if( ob->query("marry"))
		return "你都已經結婚了，要去出家，叫你夫人怎麼辦？";

	ob->set_temp("tls_app",1);
	command ("say 哈哈！好樣的！這位兄弟既然為我大理段氏做了這麼多事,今天就推薦你去天龍寺！");
	return "我即刻修書一封，快馬送到天龍寺了惑禪師那裡，你速速趕去吧!";
}

string fenglu()
{
	object ob=this_player();
	mapping fam = ob->query("family");
	int gold = 0, fenglu;

	if (!fam || fam["family_name"] != "天龍寺")
		return "這位"+ RANK_D->query_respect(ob) +"不是我大理國的臣民，難道也想來拿大理的俸祿？";

	if( ob->query("tls"))
		return "這位"+ RANK_D->query_respect(ob) +"已經出家了，還要這俸祿做甚？";

	switch (fam["generation"]) {
		case 13:
			gold += 500;
		case 14:
			gold += 800;
			break;
		default:
			return "這位"+ RANK_D->query_respect(ob) +"在大理時間還太短，等過段時間才來拿吧。";
	}
	fenglu = ob->query("age") * 12 + ob->query("month");
	if (ob->query("fenglu") >= fenglu)
		return "這位"+RANK_D->query_respect(ob) +"本月不是已經拿過俸祿了，怎麼還想來拿？";
	gold *= ob->query_skill("qiantian-yiyang", 1);
        if (ob->query_skill("force", 1) < 216)  return "你這個月沒有俸祿。";
	ob->set("fenglu", fenglu);
	command ("pat " + ob->query("id"));
	message_vision("$N給了$n"+MONEY_D->money_str(gold)+"。\n", this_object(), ob);
	MONEY_D->pay_player(ob, gold);
	return "這是你本月的俸祿，這位"+ RANK_D->query_respect(ob) +"好好幹啊！";
}

void attempt_apprentice(object ob)
{
	object me=this_object();
	mapping fam = ob->query("family");
	if( (string)ob->query("gender") == "女性" ){
		command ("say 我天龍寺武功需要純陽之體，小姑娘我可不收啊!");
		return;
	}
	if (ob->query("tls")){
		command ("say 你已經是天龍寺出家弟子了，我不能再收你了！\n");
		return;
	}
	if( (int)ob->query_skill("qiantian-yiyang",1) < 80  ){
		command ("hmm");
		command ("say 你乾天一陽功如此之差，我可不收你?");
		return;
	}
	if(ob->query_int() < 30){
		command("say 學一陽指之人必須悟性奇高，依我看" + RANK_D->query_respect(ob) + "的資質似乎不夠？");
		return;
	}
	if(fam["master_name"] == "段正明"){
		command("haha");
		command("say "+RANK_D->query_respect(ob)+"已是兄長身前的侍衛，"+RANK_D->query_self(me)+"怎能再收你為徒？");
		return;
	}
	command("smile");
	command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
	command("recruit " + ob->query("id") );
	if (!ob->query("qinwang")) {
		this_object()->set("title",HIC "大理國鎮南王府家將" NOR);}
	else
		{
		this_object()->set("title", HIW "大理國"+ ob->query("qinwang")+NOR);}
}

void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	 ob->set("class", "officer");
}

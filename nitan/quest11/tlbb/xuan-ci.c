// Npc: /kungfu/class/shaolin/xuan-ci.c
// add by tangfeng@SJ 2004


inherit NPC;
inherit F_MASTER;
#include <ansi.h>

int ask_job();
int ask_times();
int ask1();
int ask2();
int ask3();
int ask_xiaofeng();
int ask_yeerniang();
int ask_zhangxing();
int ask_xuzhu();
void zhangxing(object me,object ob);
int ask_zuinie();

#define QUESTDIR "quest/天龍八部/"
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"
#define QUESTDIR3 "quest/天龍八部/蕭峯身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"

void create()
{
	set_name("玄慈大師", ({
		"xuanci dashi",
		"xuanci",
		"dashi",
	}));
	set("long", "他是一位白鬚白眉的老僧，身穿一襲金絲繡紅袈裟。\n"
		"他身材略顯佝僂，但卻滿面紅光，目藴慈笑，顯得神完氣足。\n"
	);

	set("nickname", "少林寺方丈");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");
	set("unique", 1);
	set("no_bark",1);

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 2000);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 180);
	set("combat_exp", 1200000);
	set("score", 0);

	set_skill("force", 160);
	set_skill("yijin-jing",160);
	set_skill("dodge", 160);
	set_skill("shaolin-shenfa", 160);
	set_skill("finger", 160);
	set_skill("strike", 160);
	set_skill("hand", 160);
	set_skill("claw", 160);
	set_skill("parry", 160);
	set_skill("nianhua-zhi", 160);
	set_skill("sanhua-zhang", 160);
	set_skill("fengyun-shou", 160);
	set_skill("longzhua-gong", 160);
	set_skill("buddhism", 160);
	set_skill("literate", 160);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "nianhua-zhi");
	map_skill("strike", "sanhua-zhang");
	map_skill("hand", "fengyun-shou");
	map_skill("claw", "longzhua-gong");
	map_skill("parry", "nianhua-zhi");

	prepare_skill("finger", "nianhua-zhi");
	prepare_skill("strike", "sanhua-zhang");

	create_family("少林派", 36, "弟子");

	set("inquiry", ([
		"job" : (: ask_job :),
		"貢獻": (: ask_times :),
//		"蕭遠山":  (: ask1 :),
//		"殺孽":  (: ask2 :),
//		"捨身消業": (: ask3 :),
		"少林" : "我彌陀佛，老衲就是少林主持。不知道施主上我少林所謂何事。\n",
		"主持" : "我彌陀佛，老衲就是少林主持。",
		"蕭峯" : "他就是丐幫幫主，一身武功自不用説，其膽識智慧也是江湖一流。只是......",
		"蕭遠山" : "當年一場往事，都已經過去，蕭施主現在神僧那裏。",
		"無名神僧" : "神僧，他老人家，當稱達摩轉世，佛法超羣。",
		"神僧" : "神僧，他老人家，當稱達摩轉世，佛法超羣。",
		"虛竹" : (: ask_xuzhu :),
		
		"罪孽" : (: ask_zuinie :),
		"恥辱" : (: ask_zuinie :),
		"敗類" : (: ask_zuinie :),

		"救援蕭峯" : (: ask_xiaofeng :),
		"解救蕭峯" : (: ask_xiaofeng :),
		"援救蕭峯" : (: ask_xiaofeng :),
		"救援" : (: ask_xiaofeng :),
		"解救" : (: ask_xiaofeng :),
		"援救" : (: ask_xiaofeng :),
		"葉二孃" : (: ask_yeerniang :),
		"私生子" : (: ask_yeerniang :),
		"懲罰" : (: ask_zhangxing :),
		"杖刑" : (: ask_zhangxing :),
		"受罰" : (: ask_zhangxing :),
	]));

	setup();

	carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void attempt_apprentice(object ob)
{
	object me;
	mapping ob_fam, my_fam;
	string name;

	me = this_object();
	my_fam  = me->query("family");

	name = ob->query("name");

	if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "少林派") {
		command("say " + RANK_D->query_respect(ob) + "與本派素無來往，不知此話從何談起？");
		return;
	}

	if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "少林派") {
		command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能在寺內學藝。");
		return;
	}

	if ( ob_fam["generation"] <= my_fam["generation"] ) {
		command("say " + RANK_D->query_respect(ob) + "，貧僧哪裏敢當 !");
		return;
	}

	if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..1] == "澄") {
		command("say " + ob_fam["master_name"] + "的徒弟怎麼跑到我這兒來了，哈哈哈 !");
		command("recruit " + ob->query("id"));
	}
	else {
		command("say " + RANK_D->query_respect(ob) + "，你輩份不合，不能越級拜師。");
	}
}

int accept_object(object apper, object ob)
{
	int lvl;
	object me = this_object();

	message_vision(sprintf("$N給$n一%s%s。\n", ob->query("unit"), ob->name()), apper, me);
	if( ob->query("id") != "muou" || userp(ob)){
		command("say 這東西我要來沒用。");
		return 0;
	}

	notify_fail("");
	if (!apper->query_temp("lh_teacher")
	 || !apper->query_condition("lh_job")){
		message_vision("$N一把奪過木偶，怒道：你從哪裏偷來的?\n", me);
		destruct(ob);
		return 0;
	}
	command("touch "+apper->query("id"));
	message_vision("$N感動得熱淚盈眶，説道：老衲終於重見我少林重寶了！\n", me);
	command("thank "+apper->query("id"));
	lvl = 200 + random(50);
	apper->add("combat_exp", lvl);
	if (apper->add("potential", lvl/5+random(lvl/10)) >= apper->query("max_pot"))
		apper->set("potential", apper->query("max_pot"));
	apper->improve_skill("yijin-jing",random((int)apper->query("int"))* 2);

	log_file("job/muou", sprintf("%8s%-10s得到木偶，交給玄慈，得到獎勵：%3d，現經驗：%d。\n",
		apper->query("name"), "("+apper->query("id")+")", lvl, apper->query("combat_exp") ),apper);

	destruct(ob);
	return 0;
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;

	if(ob->query_temp("job_name")!="服侍玄慈方丈") return;
	command("pat "+ob->query("id"));
	command("say " + RANK_D->query_respect(ob)+ "你就給我按摩一下吧(massage 方丈)呵呵呵。\n");
}

int ask_job()
{
	object me = this_player(), ob = this_object(),ob1;
	int lvl,exp;
	object *team, maxplayer, minplayer;
	int totalexp=0, maxexp, minexp;
	int size,i;
	int index;
	int y;

	string* file= ({ "/d/shaolin/lhtang", "/d/shaolin/brtang",
		"/d/shaolin/smdian", "/d/shaolin/zhlou7", "/d/shaolin/gulou7",
		"/d/shaolin/houdian", "/d/shaolin/zdyuan", "/d/shaolin/pingtai",
		"/d/shaolin/putiyuan", "/d/shaolin/yaowang", "/d/shaolin/xumidian",
		"/d/shaolin/liuzu","/d/shaolin/jnlwang","/d/shaolin/lxting",
		"/d/shaolin/qfdian","/d/shaolin/czan","/d/shaolin/bydian",
		"/d/shaolin/dzdian","/d/shaolin/xcping"
	});
	string* name= ({ "羅漢堂","般若堂","山門殿","鐘樓","鼓樓","後殿",
                        "證道院","平台","菩提院","藥王院","須彌殿",
                        "六祖殿","緊那羅王殿","立雪亭","千佛殿","初祖庵",
                        "白衣殿","地藏殿","心禪坪"});
	string *name1=({ "方正大師","空見大師","空聞大師","空智大師","空性大師", });
	string *long=({
                "他是一位身材矮小的老年僧人，容顏瘦削，神色慈和，也瞧不出有多少年紀。\n",
                "他是一個身材瘦小的老年僧人，穿一身洗得發白的月白僧衣。\n",
                "他白眉下垂，直覆到眼上，便似長眉羅漢一般。\n",
                "他身軀雄偉，貌相威武。\n",
                "他一臉的苦相，嘴角下垂。\n",
	});
	int teams;
	string addr;

	if( me->query_condition("job_busy")
	|| me->query_condition("sljob")
	|| me->query_condition("sl_job_busy")
	|| me->query("job_name") == "恆山救援"){
		command("say 我這裏現在沒有什麼任務給你。" );
		return 1;
	}

	if(me->query_temp("quest/busy")) //added by tangfeng 與quest衝突
	{
		command("say 現在我這裏沒有給你的任務，你還是先處理好你其他事情再説吧。" );
		return 1;
	}

	if( me->query_temp("sljob/asked")
	 || me->query_temp("sljob/join")){
		command("say 你剛才不是已經問過了嗎？" );
		return 1;
	}

	if(!wizardp(me)&& me->query("combat_exp") >= me->query("slexp") && me->query("combat_exp") <= me->query("slexp") + 500){
		command("say 你武功精進也太慢了，老衲怎麼放心讓你去幹啊。");
		return 1;
	}

	y = sizeof(children(__DIR__"fang-zheng"));

	if( y > 2) {
		command("say 嗯，已經有人在幫我了，你還是去忙點別的什麼吧。");
		return 1;
	}

	if( me->query("shen") < 1 ){
		command("heng");
		command("say 這位" + RANK_D->query_respect(me)+"眼露兇光，我少林名門正派，可不敢勞你大架。");
		return 1;
	}

	index = ob->query("index");

	command("say 我接到本派弟子通報，魔教教主任我行親率數萬教眾，\n"
             + "欲血洗恆山派。雖定靜師太並未向我少林求援，但少林不能坐視恆山\n"
             + "覆滅，我已請"+ name1[index]+ "親率羅漢堂和般若堂弟子前去救援。");

	//if (sizeof(me->query_team()) < 2 && me->  )
	if (sizeof(me->query_team()) < 2 && (me->query("family/family_name") != "少林派" || me->query("wxz"))) {
		command("say 以" + RANK_D->query_respect(me)+ "的武功修為，似乎尚無力單獨完成這個任務。" );
		return 1;
	}
	else {
		team = me->query_team();
		if (!sizeof(team)) team = ({ me });
		if(sizeof(team) > 4) {
			command("say 此去恆山路途危險，單靠人多是沒用的。");
			return 1;
		}
		for (i=0;i<sizeof(team);i++){
			if (!team[i]) {
				command("say 你的隊伍出現了問題，請解散並重新組建。");
				return 1;
			}
			if (team[i] == me) continue;
			if (!present(team[i], environment(me))){
				command("say 咦？怎麼好像人不全啊？"+team[i]->query("name")+"怎麼沒來？");
				return 1;
			}
			if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
				command("say 你還是將"+team[i]->query("name")+"換成其他人吧。");
				return 1;
			}
		}
		maxexp=minexp=team[0]->query("combat_exp");
        	maxplayer=team[0];
		minplayer=team[0];
		for (i=0;i<sizeof(team);i++){
			if (team[i]->query("combat_exp") < 1000000) {
				command("say 此去恆山路途危險，我看這位"+RANK_D->query_respect(me)
					+"需要一個好搭檔！");
				return 1;
			}
			if( team[i]->query_condition("job_busy")
			|| team[i]->query_condition("sljob")
			|| team[i]->query_condition("sl_job_busy")
			|| team[i]->query("job_name") == "恆山救援"){
				command("say 你隊伍中的"+team[i]->query("name")+"正在做其它任務呢。");
				return 1;
			}
			if( team[i]->query("combat_exp") - 500 <= team[i]->query("slexp")
			&& team[i]->query("sldeath")==team[i]->query("death_count")){
				command("say 你隊伍中的"+team[i]->query("name")+"武功精進太慢，這個搭檔是否應該再選一個啊。");
				return 1;
			}
			if (team[i]->query("shen") < 0) {
				command("whisper "+ me->query("id")+" 此去恆山乃我正派中事，看你隊伍中的"+team[i]->query("name")+
					"眼露兇光，不會是那任老賊派來的奸細吧？");
				return 1;
			}
			totalexp += team[i]->query("combat_exp");
			if(team[i]->query("combat_exp") > maxexp ){
				maxexp=team[i]->query("combat_exp");
				maxplayer=team[i];
			}
			else if(team[i]->query("combat_exp") < minexp){
				minexp=team[i]->query("combat_exp");
				minplayer=team[i];
			}
		}
		if (totalexp < 2000000 || maxexp-minexp > 1000000) {
	        	command("say 此去恆山路途危險，我看諸位似乎無此能力？");
			return 1;
		}
		if (sizeof(team) != 0 && (team[0] != me)){
			command("say 只有隊伍首領才能申請任務。");
			return 1;
		}
		for (i=0;i<sizeof(team);i++){
			team[i]->delete_temp("sljob");
			team[i]->set_temp("sljob/join", 1);
			team[i]->set("slexp", team[i]->query("combat_exp"));
			team[i]->apply_condition("sljob",40);
			team[i]->apply_condition("job_busy",40);
			team[i]->set("sldeath",team[i]->query("death_count"));
	        }
	        teams=sizeof(team);
	}

	ob->set("index", (ob->query("index")+1)%5);
	size=sizeof(file);
	i=random(size);
	addr=file[i];

	command("say 就請各位隨同"+name1[index]+"前去恆山，一路小心。");
	command("say "+name1[index]+"現在"+name[i]+"。\n");
	log_file("job/husong", sprintf("%8s%-10s救援，%d人\n",
		me->query("name"),"("+me->query("id")+")", teams ),me);
	ob1=new(__DIR__"fang-zheng");
	ob1->move( file[i] );
	ob1->set("name",name1[index]);
	ob1->set("long",long[index]);
	ob1->set_temp("teams",teams);
	if(teams>3)
		ob1->set_temp("team4",team[3]);
	if(teams>2)
		ob1->set_temp("team3",team[2]);
	if(teams>1)
		ob1->set_temp("team2",team[1]);
	if(teams>0){
		if( me->query_team() )
			ob1->set_temp("team1",team[0]);
		else
			ob1->set_temp("team1",me);
	}

	if( maxplayer->query("max_pot")-20 > minplayer->query("max_pot"))
		lvl = minplayer->query("max_pot")-100-10;
	else
		lvl = maxplayer->query("max_pot")-100-30;

	exp = minplayer->query("combat_exp");
	ob1->set("combat_exp",exp);
	ob1->set("max_qi",5000+exp/1200);
	ob1->set("qi",ob1->query("max_qi"));
	ob1->set("eff_qi",ob1->query("max_qi"));
	ob1->set("jing",4000);
	ob1->set("max_neili",4000+exp/1500);
	ob1->set("neili",ob1->query("max_neili"));
	ob1->set("eff_jingli",3500);
	ob1->set_temp("lvl",lvl);
	ob1->set_skill("dodge",lvl);
	ob1->set_skill("force", lvl);
	ob1->set_skill("yijin-jing", lvl);
	ob1->set_skill("shaolin-shenfa", lvl);
	ob1->set_skill("parry", lvl);
	ob1->set_skill("finger",lvl);
	ob1->set_skill("yizhi-chan",lvl);
	ob1->set_skill("medicine",150);
	ob1->set_skill("buddhism", 200);
	ob1->set_skill("literate", 200);
	ob1->map_skill("force", "yijin-jing");
	ob1->map_skill("dodge", "shaolin-shenfa");
	ob1->map_skill("finger", "yizhi-chan");
	ob1->map_skill("parry", "yizhi-chan");
	ob1->set("jobleader",me);
	ob1->set("xuanci",ob);
	ob1->set("teams",teams);
	ob1->set("lvl",maxplayer->query("max_pot")-100);
	ob1->set_name(ob1->query("name"), ({ me->query("id")+"'s dashi" }));
	tell_room(environment(ob1), ob1->name() + "輕誦佛號，慢慢地走了過來。\n", ({ ob1 }));

	me->set_temp("sljob/asked",1);
	me->apply_condition("sljob",40);
	me->apply_condition("job_busy",40);
	return 1;
}

int ask_times()
{
	object me=this_player();
	command("say 你已經為少林做了"
		+ CHINESE_D->chinese_number( me->query("job_time/少林救援") )
		+ "次貢獻。");
	command("addoil "+me->query("id"));
	return 1;
}

int ask1()
{
	object me;

	me=this_player();

	if( me->query("family/family_name")!="少林派" )
		return 0;
	if( me->query("family/generation")>36 )
		return 0;

	command( "say 老衲當年誤信人言，率眾於雁門關外截殺蕭施主全家，\n"
                + "造下無窮殺孽，今日想來，追悔末及。" );
	command( "sigh" );
	me->set_temp("sl/pks",1);
	return 1;
}

int ask2()
{
	object me = this_player();

	if( me->query_temp("sl/pks") < 1 )
		return 0;
	command( "say 老衲得知事情真相後心灰意冷，幸得本門一位高僧點化，以無上\n"
		+"佛法捨身消業，方使心情振奮，但也不免大誤禪修。" );
	me->set_temp("sl/pks",2);
	return 1;
}

int ask3()
{
	object me = this_player();

	if( me->query_temp("sl/pks") < 2 )
		return 0;
	command( "whisper " + me->query("id") +
		" 大師既有此心，可去藏經閣找一位掃地的無名老僧。" );
	command( "buddhi dashi" );
	me->set_temp("sl/pks",3);
	return 1;
}

//以下是quest部分
int ask_xuzhu()
{
	object me = this_player();
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& (me->query_temp(QUESTDIR5+"son")||me->query(QUESTDIR5+"over")))
	{
	  message_vision(HIY"$N面露悲痛之色，良久沒有説話，只是歎息一聲。\n"NOR,this_object());
	  if(random(2)) command("sigh");
	  else command("say");
	  return 1;
	}	
	command("? "+me->query("id"));
	command("say 虛竹，好像是少林第三十九代弟子之一。不知道施主找他何事？");
	return 1;
}

int ask_yeerniang()
{
	object me = this_player();
 	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   command("say "+RANK_D->query_respect(me) +"還是小心通緝吧！");
	   return 1;
	}	
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& !me->query_temp(QUESTDIR5+"yeerniang")&& !me->query(QUESTDIR5+"over"))
	{
		command("? "+me->query("id"));
	  message_vision(HIC"$N對$n哼了一聲，道：不要假裝不明白的樣子，二十年前，你難道你真的什麼都不記得了......\n"NOR,me,this_object());
	  command("consider");
	  message_vision(HIY"$N大聲道：“20年前你勾引葉家莊葉二姑娘，本來好端端的姑娘，美貌貞淑。可是被你所引誘，失身於你，\n"
	                    "還為你生下一個孩子，但是你只顧到自己的聲名前程，全不顧念你一個年紀輕輕的姑娘，未嫁生子，處境是\n"
	                    "何等的悽慘。二十年來你可知道，當年的葉二姑娘就是現在的四大惡人葉二孃！”\n\n"NOR,me);
	  command("oh");
	  message_vision(HIG"\n$N搖搖頭道：當年之事誰對誰錯很難説清，就算我錯，當時我也無力照顧，至於孩子，我當真不知。\n"NOR,this_object());
	  command("dunno "+me->query("id"));
		command("say 我真的沒有料到葉二孃就是當年葉家莊的葉二姑娘。罪孽罪孽。");
		me->set_temp(QUESTDIR5+"yeerniang",1);
		return 1;
	}	
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& (me->query_temp(QUESTDIR5+"yeerniang")||me->query(QUESTDIR5+"over")))
	{
		command("sigh");
		command("say 我真的沒有料到葉二孃就是當年葉家莊的葉二姑娘。罪孽罪孽。");
		return 1;
	}	
	command("say 可是四大惡人的葉二孃？");
	command("dunno "+me->query("id"));
	return 1;
}
int ask_zuinie()
{
	object me = this_player();
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& me->query_temp(QUESTDIR5+"yeerniang")
	   && !me->query_temp(QUESTDIR5+"zuinie")&& !me->query(QUESTDIR5+"over"))
	{
	  message_vision(HIY"$N哈哈笑道：你自當掩飾自己，可是作為少林主持，難道不感到羞愧。少林號稱佛門聖地，確有私生子的怪事。\n"NOR,me);
	  message_vision(HIG"$N緩緩道了聲佛號，良久沒有説話，只是歎息一聲。\n"NOR,this_object());
		command("sigh");
		me->set_temp(QUESTDIR5+"zuinie",1);
		return 1;
	}	
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& (me->query_temp(QUESTDIR5+"yeerniang")||me->query(QUESTDIR5+"over")))
	{
		command("sigh");
		command("say 我真的沒有料到葉二孃就是當年葉家莊的葉二姑娘。罪孽罪孽。");
		return 1;
	}	
	command("say 我彌陀佛！我佛慈悲！");
	return 1;
}
int ask_zhangxing()
{
	object obj,me = this_player();
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& me->query_temp(QUESTDIR5+"yeerniang")&& me->query_temp(QUESTDIR5+"zuinie")&& !me->query_temp(QUESTDIR5+"zhangxing")&& !me->query(QUESTDIR5+"over"))
	{
	  message_vision(HIC"$N哼了一聲，道：家法何在，寺規何在。想不到百年少林竟然出現這等事情，還妄稱佛門善地。\n"NOR,me);
		command("sigh "+me->query("id"));
		command("nod "+me->query("id"));
		
	  message_vision(HIY"\n$N朗聲説道：“不錯，老衲犯了佛門大戒，有傷鸛林清譽。國有國法，家有家規。自來任何門派\n"
	                    "幫會，宗族寺院，都難免有不肖弟子。清名令譽之保全，不在求永遠無人犯規，在求事事按律懲處，不\n"
	                    "稍假借。依本寺戒律，玄慈犯了淫戒，且身為方丈，罪刑加倍。執法僧重重責打玄慈二百棍。少林寺清\n"
	                    "譽攸關，不得循私舞弊。”説着跪伏在地，遙遙對着佛像，自行捋起了僧袍，露出背脊。\n"NOR,this_object());
	  command("sneer "+me->query("id"));
	  obj=new("/d/shaolin/npc/zjseng.c");
	  obj->move(environment(me));
    message_vision(WHT"$N匆匆了走了過來。\n"NOR,obj);
	message_vision(HIY"$N向$n施禮，道了聲佛號，就侍立在一邊。\n"NOR,obj,this_object());
	  obj->command("bow "+this_object()->query("id"));
	  obj=new("/d/shaolin/npc/zjseng.c");
	  obj->move(environment(me));
    message_vision(WHT"$N匆匆了走了過來。\n"NOR,obj);
	message_vision(HIY"$N向$n施禮，道了聲佛號，就侍立在一邊。\n"NOR,obj,this_object());
	  obj->command("bow "+this_object()->query("id"));
	  command("nod "+obj->query("id"));
	  message_vision(HIG"\n$N厲聲道：“我少林寺千年清譽，豈可壞於我手？執法僧，用刑。”\n"NOR,this_object());
    remove_call_out("zhangxing");
    call_out("zhangxing",5,me,this_object());
		return 1;
	}	
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& (me->query_temp(QUESTDIR5+"zhangxing")||me->query(QUESTDIR5+"over")))
	{
	  message_vision(HIY"$N道了聲佛號，面露悲痛之色。\n"NOR,this_object());
		command("say 老衲確實罪孽。我彌陀佛。");
		return 1;
	}	
	command("? "+me->query("id"));
	return 1;
}
void zhangxing(object me,object ob)
{
  if(!me) return;
  if(!ob) return;
  if(environment(me)!=environment(ob))
  {
  	ob->command("sigh");
  	message_vision(HIY"$N似乎猶豫了一下，還是站了起來，背過身去，不再言語。\n"NOR,ob);
  	tell_object(me,HIY"這等時候竟然走開，復興慕容天下的任務如何完成？\n"NOR);
   	me->delete(QUESTDIR5+"start");
   	me->delete_temp("quest/天龍八部");
	me->delete_temp("quest/busy");//任務衝突標誌取消
  	return;
  }
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& me->query_temp(QUESTDIR5+"yeerniang")&& !me->query_temp(QUESTDIR5+"zhangxing")&& !me->query(QUESTDIR5+"over"))
	{
	  message_vision(HIC"二僧知道方丈受刑，最難受的還是當眾受辱，不在皮肉之苦，倘若手下容情，給旁人瞧了出來落下話柄，\n"
	                    "那麼方丈這番受辱反而成為毫無結果了，是以一棍棍打將下去，拍拍有聲，片刻間便將玄慈背上、股上打\n"
	                    "得滿是杖痕，血濺僧侶。堪堪又打了一百餘杖，$N支持不住，撐在地下的雙手一軟，臉孔觸到塵土。\n"NOR,this_object());
    message_vision(WHT"\n$N哈哈大笑起來，“我不殺你，少林自此名譽一敗塗地。這餘下五十杖不打也罷。”\n"NOR,me);
		me->set_temp(QUESTDIR5+"zhangxing",1);
	if(me->query("family"))
	  command("chat "+me->query("family/master_name")+"也算是一代宗師，沒有料到其弟子"+me->name()+"竟然行事如此惡毒！");
	else command("faint "+me->query("id"));
	command("inn "+me->query("id"));
    message_vision(WHT"\n$N一時間氣急攻心，竟然昏了過去。\n"NOR,this_object());
	command("faint");
	tell_object(me,HIY"\n你哈哈大笑，終於完成任務，只是......返回慕容的路上，恐怕更加危險重重。\n"NOR);
	this_object()->unconcious();
   }
   return;
}
		
int ask_xiaofeng()
{
	object room,me = this_player();
	object *obj;
	int x;
	if(me->query(QUESTDIR3+"bad") )
  {
  	command("heng");
  	command("say 難道不是當年強迫蕭峯走出中原，叫我如何相信你？");
  	return 1;
  }
  	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   command("say "+RANK_D->query_respect(me) +"還是小心通緝吧！");
	   return 1;
	}
	if(me->query(QUESTDIR3+"good") &&!me->query_temp(QUESTDIR4+"shaolinzhen")&& !me->query(QUESTDIR4+"start"))
	{	  
		if(!me->query_temp(QUESTDIR4+"askxuanci"))
		{
			message_vision(HIC"你急聲道：江湖傳言，蕭峯為避免南征之戰，拒絕可汗命令，現被投入鐵牢之中。\n"NOR,me);
			command("ah "+me->query("id"));
		}	
		//增加時間和經驗間隔限制
		//時間一天，經驗500K
        if(!me->query_temp(QUESTDIR4+"dagouzhen") && me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
		{
			command("say 今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！");
			return 1;
		}
        if(!me->query_temp(QUESTDIR4+"dagouzhen") && me->query(QUESTDIR+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000)
		{
			command("say 以"+RANK_D->query_respect(me) +"目前的經驗就算目前有情況，也幫不上什麼忙，還是抓緊練功吧！");
			return 1;
		}
	//只能一個人做
	obj = users();
	x = sizeof(obj);
	while(x--) {
		  if ( obj[x]->query_temp(QUESTDIR4+"askxuanci") && obj[x]!=me) 
		  {
			  command("nod "+me->query("id"));
			  command("say 我也聽説這事情，已經有"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"前往大遼營救去了，"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"武功高強，料想也無大礙！");	
			  return 1;
		  }
	  }
  	
	if(!me->query_temp(QUESTDIR4+"askxuanci"))
	{
		command("whisper "+me->query("id")+" 如果當真，少林自當盡力，當年少林與蕭家誤會頗多，這也是我中原武林贖罪的一次良機。\n"NOR);
		command("whisper "+me->query("id")+" 只是，你又如何得知這一消息？"NOR);
		message_vision(HIY"$N朗聲説道：“我剛從大遼歸來，也罷，依照江湖規矩，還是武功上考量一下吧。”。\n"NOR,me);
		command("nod "+me->query("id"));
	}
    else command("whisper "+me->query("id")+" 可是失敗了，也罷，再給你一次機會。\n"NOR);
	command("whisper "+me->query("id")+" 你且隨我進這少林陣法之中。");
	if (!(room = find_object("/d/shaolin/shaolinzhen")))
		room = load_object("/d/shaolin/shaolinzhen");
	if(!room)
	{ 
      	tell_object(me,HIR"\n趕快找wiz吧，竟然房間不存在!!!\n");
        log_file("quest/TLBB", sprintf("%s(%s)營救蕭峯篇少林陣法文件缺少！\n", me->name(1),me->query("id")) );
    }
    else
    {
      tell_room(environment(me),HIC""+me->query("name")+"隨玄慈主持匆匆出去了。\n"NOR, ({ me }));        
		  tell_object(me,HIR"你隨玄慈主持來到一個小屋之中，卻見四端分別站着一個少林弟子。\n");
		  //設定標誌
		  me->set(QUESTDIR+"time",time());
		  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		  me->move(room);
		  this_object()->move(room);
		  tell_object(me,HIY"\n玄慈主持向你揮了揮手，退了出去。\n"NOR);
		  this_object()->move("/d/shaolin/fzjs2");

		  tell_room(environment(this_object()),HIC"玄慈主持匆匆回來了，神色很是慌張。\n"NOR, ({ this_object()}));    
		  log_file("quest/TLBB", sprintf("%s(%s)營救蕭峯篇進入少林陣法。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );                  
		  me->set_temp(QUESTDIR5+"askxuanci",1);
		  me->set_temp("quest/busy",1);//與任務系統衝突標誌
    }
    return 1;
	}	
	if(me->query(QUESTDIR3+"good")&& !me->query(QUESTDIR4+"over") &&(me->query(QUESTDIR4+"start")|| me->query_temp(QUESTDIR5+"dagouzhen")))
	{
		command("addoil "+me->query("id"));
		command("say "+RANK_D->query_respect(me) +"卻是了得。老衲佩服。還請"+RANK_D->query_respect(me) +"主持大局。");
		return 1;
	}	
	if(me->query(QUESTDIR3+"good") &&me->query(QUESTDIR4+"over"))
	{
		command("admire "+me->query("id"));
		return 1;
	}	
	if(random(2)) command("@@ "+me->query("id"));
	else command("laugh "+me->query("id"));
	return 1;
}

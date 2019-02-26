// xiaofeng.c
// Add by tangfeng 2004

inherit F_MASTER;
#include <ansi.h>
inherit NPC;

#define QUESTDIR "quest/天龍八部/"
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"
#define QUESTDIR3 "quest/天龍八部/蕭峯身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"

int ask_truth();
int ask_yintui();
int ask_father();
int ask_skills();
int ask_save();
void greeting(object me);
void xiaofeng_guiyin(object me);

void create()
{
	set_name("蕭峯", ({"xiao feng", "xiao", "feng"}));
	set("gender", "男性");
	set("nickname",HIB"奇俠"NOR);
	set("title",HIY"前丐幫幫主"NOR);
	set("age", 58);
	set("long", 
		"他就是丐幫前任幫主蕭峯。\n"
		"他身高六尺有餘，體格十分魁梧，長有一張線條粗曠、十\n"
		"分男性化的臉龐，雙目如電，炯炯有神。\n");
	set("attitude", "peaceful");
	
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("qi", 40000);
	set("max_qi", 40000);
	set("jing", 15000);
	set("max_jing", 15000);
	set("eff_jing", 15000);
	set("neili", 30000);
	set("max_neili", 20000);
	set("jiali", 200);
  set("max_jingli", 15000);
  set("jingli", 15000);
	set("eff_jingli", 15000);
  set("combat_exp", 6000000);	 
	set_skill("force", 400);   
	set_skill("bangjue", 200);
	set_skill("literate", 200);        
	set_skill("medicine", 200);        
	set_skill("huntian-qigong", 420);
	set_skill("yijin-jing", 200);     
	set_skill("strike", 400);           
	set_skill("jingang-quan", 400);     
	set_skill("xianglong-zhang", 400);     
	set_skill("dodge", 400);      	     
	set_skill("xiaoyaoyou", 400);   
	set_skill("parry", 400);          
	set_skill("stick", 400);          
	set_skill("dagou-bang", 400);          
	set_skill("cuff", 400);          
	map_skill("cuff", "jingang-quan");
	map_skill("force", "huntian-qigong");
	map_skill("strike", "xianglong-zhang");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "xianglong-zhang");
	map_skill("stick", "dagou-bang");
	set("doule_attack",1);
	prepare_skill("strike","xianglong-zhang");
  set("chat_chance_combat", 99);
  set("chat_msg_combat", ({
          (: exert_function, "huntian" :),
          (: exert_function, "shentong" :),
          (: perform_action, "strike.paiyun" :),
          (: perform_action, "strike.xiao" :),
  }));
  set("inquiry", ([
		"段譽" : random(2)?"那是我二弟。":"我二弟一身內力震古爍今，六脈神劍更是天下無雙。",
		"虛竹" : random(2)?"那是我三弟。":"我三弟現為縹緲宮宮主，只怕現在更是西夏國的駙馬爺了。",
		"真相" : (: ask_truth :),
		"當年" : (: ask_truth :),
		"為什麼" : (: ask_truth :),
		"原因" : (: ask_truth :),
		//太祖拳增加絕技
		"太祖拳" : (: ask_skills :),
		"拳理" : (: ask_skills :),

		"save" : (: ask_save :),
		"help" : (: ask_save :),
		"解救" : (: ask_save :),
		"搭救" : (: ask_save :),
		"救援" : (: ask_save :),
		"救命" : (: ask_save :),

		"蕭遠山" : (: ask_father :),
		"拜師" : "嗯....，我註定一聲漂泊，還是算了吧。",
		"丐幫" : "丐幫是我家，我家在丐幫。",
		"少林" : "我一身武功出自少林，也算是半個少林弟子。",
		"天龍寺" : "天龍寺是大理段家武學的最高之地。",
		"洪七公" : "恩，聽説下一輩中也是他為人最為俠義，武功最高。",
		"阿朱" : "......怕是這一生我唯一的牽掛了。",
		"阿紫" : "恩，不提也罷，丁老怪的弟子，那個不是心狠手辣。",
		"阿碧" : "阿朱的妹妹，聽説和慕容公子在一起。",
		"天龍寺" : "天龍寺是大理段家武學的最高之地。",
		"降龍十八掌" : "這是我行走江湖的吃飯的東西，哈哈。",
		"排雲雙掌" : "這是我最得意的一招，也是最兇猛的一招。",
		"打狗棒" : "丐幫幫主之外不傳之武功，確實精妙無比。",
		"歸隱" : (: ask_yintui :),
		"隱退" : (: ask_yintui :),
		"洗手" : (: ask_yintui :),
		"隱退江湖" : (: ask_yintui :),
		"歸隱江湖" : (: ask_yintui :),
		"喝酒" : "哈哈，一日不可無酒。等空閒時分，我們一同喝酒去！",
		"慕容復" : "慕容公子確是其江南文采，詩琴書畫無所不精，武功更是冠絕天下。",
		"慕容博" : "我聽説是，姑蘇慕容不出的傑才，可惜英年早逝。",
		"六脈神劍" : "天龍寺最高絕學。恐怕天下唯我二弟這身內力才能使得。",
    ]));

	setup();
  carry_object(ARMOR_D("changshan"))->wear();
  carry_object(ARMOR_D("shoes"))->wear();
}

void init()
{
	object me;
	//object room;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
		if(!me->query_condition("killer")&&me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"lookcliff")&& !me->query_temp(QUESTDIR3+"over") && !me->query(QUESTDIR3+"over"))
		{
			this_object()->set("qi", this_object()->query("max_qi"));
			this_object()->set("eff_qi", this_object()->query("max_qi"));
			this_object()->set("neili", this_object()->query("max_neili")*2);
			message_vision(HIY"\n只聽一聲嘯聲，一個身影已經竄上峭壁，$n定眼一看，正是$N。\n"NOR,this_object(),me); 
			command("nod "+me->query("id")); 
			message_vision(HIR"$N微一凝神，運起「混天」神功，全身骨節發出一陣爆豆般的聲響。\n\n"NOR,this_object());   
			tell_object(me,CYN"你驚訝地「啊！」了一聲。\n"NOR);    
			message_vision(HIW"$N長長地舒了一口氣，傷勢看來基本全部恢復了。"NOR,this_object());                    
			tell_object(me,HIC"\n你沒有料道，蕭峯竟然恢復如此之迅速，果然是功夫了得。\n"NOR);  
			log_file("quest/TLBB", sprintf("%s(%s)蕭峯來到頌摩崖，特此紀錄。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) ); 
			me->set_temp(QUESTDIR3+"over",1);
			command("pat "+me->query("id")); 
			command("thank "+me->query("id"));
			remove_call_out("greeting");
			call_out("greeting",4,me);
			call_out("dest", 600,this_object());
		}
		if(!me->query_condition("killer")&& me->query(QUESTDIR4+"start") && me->query_temp(QUESTDIR4+"breakmen")&&!me->query_temp(QUESTDIR4+"helpstart") &&!me->query_temp(QUESTDIR4+"follow")&& !me->query(QUESTDIR4+"over"))
		{
			command("ah "+me->query("id"));
			message_vision(HIY"$n進來時，$N靠在鐵籠的欄杆上，神色倒是正常。\n看暗室一旁酒罈堆積，感覺$N這裏的日子竟也是好酒好飯，禮數不缺。\n"NOR,this_object(),me);   		
			command("say 沒想到，又是"+RANK_D->query_respect(me) +"捨命相救。"); 
			command("touch "+me->query("id"));
			command("thank "+me->query("id"));
			me->start_busy(2);
			me->set_temp(QUESTDIR4+"helpstart",1);
			call_out("dest", 600,this_object());
		}
	} 
}

void greeting(object me)
{
	object ob=this_object();
	int i;
	if(!me)
	{
		message_vision(HIW"$N急急忙忙地離開這裏。\n"NOR,ob);
		destruct(ob);
		return;
	}
	if(environment(this_object())!=environment(me)) 
	{
		command("chat "+me->name()+"怎麼如此邋遢，竟然無端走開？");
		command("chat* heng "+me->query("id"));
		tell_object(me,HIG"\n你這種情況竟然臨陣逃脱，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
		me->delete_temp("quest/天龍八部");
		me->delete_temp("quest/busy");//任務衝突標誌取消
		me->delete(QUESTDIR3+"start");
		me->add("mana",-200);
		if(me->query("mana")<0) me->set("mana",0);
		return;
	}
	if(me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"lookcliff")&& me->query_temp(QUESTDIR3+"over") && !me->query(QUESTDIR3+"over"))
	{
		message_vision(HIW"$N對$n表示衷心的感謝。\n"NOR,this_object(),me);
		tell_object(me,HIG"\n\n你走過去看了看蕭峯，還是將你看到的告訴了蕭峯：“智光大師所道的山壁上如今正中一大片盡是斧鑿的印痕，\n"
			"顯而易見，是有人故意將留下的字跡削去了。”\n"NOR);
		tell_room(environment(me),HIG"\n"+me->name()+"走到蕭峯跟前，低聲説了些什麼。\n"NOR, ({ me }));

		command("oh");

		me->set(QUESTDIR3+"over",1);
		me->delete_temp("quest/天龍八部");
		me->delete_temp("quest/busy");//任務衝突標誌取消
		me->start_busy(3);
		i=20+random(10);
		me->add("max_neili",i);
		me->add("combat_exp",me->query_skill("force")/2);
		me->add("mana",me->query_skill("force")/5);
        me->set(QUESTDIR+"time",time());
        me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
        tell_object(me,HIY"\n你於"+NATURE_D->game_time()+"終於幫助蕭峯確定身世之謎，獲得"+i+"點最大內力、"+me->query_skill("force")/2+"點經驗和"+(int)me->query_skill("force")/5+"點聲望。\n\n"NOR);
        log_file("quest/TLBB", sprintf("%s(%s) 蕭峯身世確定。玩家結局選擇中。獎勵：%d點最大內力，%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), i,(me->query_skill("force")/2),me->query_skill("force")/5) );


		command("consider");
		message_vision(HIW"\n\n$N突然悲笑起來，四顧茫然，喃喃道：“看來我真是契丹人，我真的不是漢人。”\n"NOR,this_object());
		command("say");
		message_vision(HIC"$N神色漸漸有些不正常，似乎已經有些發狂。\n"NOR,this_object());
		command("crazy");
		tell_object(me,HIW"\n突然之間，你腦子閃過兩個念頭。一個因為這蕭峯已確是契丹人，他若公開反對大宋，只怕朝廷不知多少人因此\n"
			"喪命，而且此時你趁他意亂傷神之際，正是揚你威名的大好時機；可是一個俠義之心告訴你，如此確似小人行為\n"
			"一般不堪，這契丹人中也有好人壞人，也可以行俠仗義，何必執著於身份。\n\n"NOR);
		remove_call_out("check_answer");
		call_out("check_answer",3,me,1);
	}
}
void check_answer(object me,int i)
{
	object ob=this_object();
	if(!ob) return;
	if(!me) 
	{
		message_vision(HIW"$N急急忙忙地離開這裏。\n"NOR,ob);
		destruct(ob);
		return;
	}
	if(environment(ob)!=environment(me)) 
	{
		command("say "+me->name()+"什麼時候走了？我也該走了。");
		message_vision(HIC"\n$N飛身跳下山崖，一瞬間已經蹤影全無。\n"NOR,ob);
		destruct(ob);
		return;
	}
	if(me->is_fighting(ob)||ob->is_fighting(me)) 
	{
		remove_call_out("check_answer");
		ob->set("kill_id",me->query("id"));
		message_vision(HIW"$N對$n冷笑一聲，竟然趁我之危！如此小看於我。\n"NOR,ob,me);
		me->set(QUESTDIR3+"bad",1);//這裏只要下kill就認為選擇惡人
		                           //但是獎勵需要殺完才給
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		ob->kill_ob(me);
		command("perform strike.xiao");
		command("yun huntian");
		command("yun shentong");
		return;
	}
	if(me->query(QUESTDIR3+"over"))
	{
		if(random(2)) command("haha");
		else command("smile");
		command("cry");
		if(random(2)) command("say");
		message_vision(HIC"$N越發得有些癲狂。\n"NOR,ob);
		if(random(2)) command("crazy");

		if(i>=10)
		{
			message_vision(HIC"$n正遲疑間，只見$N猛一陣癲狂，飛身跳下山崖，等$n看時，已經蹤影全無。\n"NOR,ob,me);
			log_file("quest/TLBB", sprintf("%s(%s)竟然讓蕭峯離開，以後可沒機會的。\n", me->name(1),me->query("id")) );                  
			destruct(ob);
		}
		else
		{    	
			i++;
			if(i<2)  tell_object(me,HIR"一時間，你是勸其歸隱（ask xiao about 歸隱），還是為武林除害（kill xiao）？你一時委實難以決定。\n"NOR);
			else 
			{
				if(random(2)) tell_object(me,HIR"是勸其歸隱（ask xiao about 歸隱），還是為武林除害（kill xiao），瞬間的決定掌握在你手中。\n"NOR);
				else if(random(2))  tell_object(me,HIR"（ask xiao about 歸隱）（kill xiao）兩個命令都很簡單。\n"NOR);
				else tell_object(me,HIR"你還有一個選擇，不去理睬。何必理會這煩人的江湖瑣事呢。\n"NOR);
			}
			tell_object(me,HIC"你還有"+(88-i*8)+"秒決定。\n"NOR);
			remove_call_out("check_answer");
			call_out("check_answer",8,me,i);
		}
	}
}
int ask_save()
{
    object me;
    me=this_player();
    if(me->query(QUESTDIR4+"over"))
    {
    	command("thank "+me->query("id"));
		return 1;
	}
	if(!me->query_condition("killer")&& me->query(QUESTDIR4+"start") 
		&& me->query_temp(QUESTDIR4+"breakmen")
		&& me->query_temp(QUESTDIR4+"helpstart") 
		&&!me->query_temp(QUESTDIR4+"follow")
		&& !me->query(QUESTDIR4+"over"))
	{
		tell_object(me,HIC"\n你上前説道，“我們還是趕快離開此地，只怕這次為了營救你，江湖中人已全部出動，無論丐幫、少林、大理、\n"
			"還是遠在西域的縹緲七十二宮。”\n"NOR);
		command("nod");
    	command("pat "+me->query("id"));
		command("say 好，我們這就趕快一起闖出去。");
		log_file("quest/TLBB", sprintf("%s(%s)準備衝出大遼，特此紀錄。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) ); 
		me->set_temp(QUESTDIR4+"follow",1);
		this_object()->set("daliao",me->query("id"));
		this_object()->set("qi", this_object()->query("max_qi"));
		this_object()->set("eff_qi", this_object()->query("max_qi"));
		this_object()->set("neili", this_object()->query("max_neili")*2);
		command("follow "+me->query("id"));
		message_vision(HIR"$N微一凝神，運起「混天」神功，全身骨節發出一陣爆豆般的聲響。\n\n"NOR,this_object());   
		remove_call_out("check_me_where");
		call_out("check_me_where",1,me);
		return 1;
	}
	command("@@ "+me->query("id"));
	command("haha "+me->query("id"));
	command("pat "+me->query("id"));
	command("addoil "+me->query("id"));
	return 1;
}
void check_me_where(object me)
{
	object ob;
    int i;
	ob=this_object();
	remove_call_out("check_me_where");
	if(!ob->query("daliao")) return;
	if(!me || me->is_ghost()) 
	{
		ob->unconcious();
		return;
	}
	if(environment(ob)!=environment(me)) 
	{
		if(wizardp(me)) tell_object(me,HIR"\n尋找玩家!\n"NOR);
		message_vision(HIW"$N急急忙忙地離開這裏。\n"NOR,ob);
		ob->set("qi", ob->query("max_qi"));
		ob->set("eff_qi", ob->query("max_qi"));
		ob->set("neili", ob->query("max_neili")*2);
		ob->move(environment(me));
		message_vision(HIW"$N匆匆地走了過來。\n"NOR,ob);
		message_vision("$N深深吸了幾口氣，臉色看起來好多了。\n", ob);
		message_vision("$N深深吸了幾口氣，精神看起來好多了。\n", ob);
	}

	command("kill liao bing");
	command("kill liao bing 2");
	if((string)file_name(environment(me))!="/d/xingxiu/daliao/shulin")
		call_out("check_me_where",1,me);
	else
	{
		me->start_busy(1);
        tell_object(me,HIG"\n你們邊打邊退，一路奔波，連續走過好幾個地方，才來到一個一片樹林邊。\n"NOR);
		command("touch "+me->query("id"));
        message_vision(HIW"$N長長地舒了一口氣。\n"NOR,ob);
		message_vision(HIW"$N長長地舒了一口氣。\n"NOR,me);
		command("pat "+me->query("id"));
		command("shrug "+me->query("id"));
		command("whisper "+me->query("id")+" 穿過這片樹林，一直南行，應該就可以回來中原了。");
		message_vision(HIW"$N突然高聲而唱：“亡我祁連山，使我六畜不蕃息。亡我焉支山，使我婦女無顏色。”\n"NOR,ob);
		command("say 當年漢武帝大伐匈奴，搶奪了大片地方，匈奴人慘傷困苦。其實無論契丹、匈奴還是大宋，凡是戰爭，受苦的肯定是百姓。");
		message_vision(HIW"$N喟然吟道：“烽火燃不息，征戰無已時。野戰格鬥死，敗馬號鳴向天悲。鳥鳶啄人腸，衝飛上掛枯枝樹。士卒塗草莽，將軍空爾為。”\n"NOR,ob);
		command("whisper "+me->query("id")+" 兵器乃兇器，聖人不得已而用之。也罷，我與中原武林之間的恩恩怨怨也一筆勾銷。");
		command("wave "+me->query("id"));
		command("bye "+me->query("id"));

		i=20+random(10);
		if(!me->query(QUESTDIR4+"over")) 
		{
			me->add("max_neili",i);
			me->add("combat_exp",(me->query_skill("force")+500));
			me->add("mana",me->query_skill("force")/3);
			tell_object(me,HIY"\n你於"+NATURE_D->game_time()+"終於將蕭峯從大遼解救出來，獲得"+i+"點最大內力、"+(me->query_skill("force")+500)+"點經驗和"+(int)me->query_skill("force")/3+"點聲望。\n\n"NOR);
			log_file("quest/TLBB", sprintf("%s(%s) 大遼解救篇完成。獎勵：%d點最大內力，%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), i,(me->query_skill("force")+500),me->query_skill("force")/3) );
		}
		me->set(QUESTDIR4+"over",1);
        me->set(QUESTDIR+"time",time());
        me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
        me->delete_temp("quest/天龍八部/大遼救援篇");
		me->delete_temp("quest/busy");//任務衝突標誌取消
		destruct(ob);
  }
}
int ask_father()
{
    object me;
    me=this_player();
    if(me->query(QUESTDIR4+"over"))
    {
    	command("say 蕭遠山，正是我父親。現已被少林高僧收為弟子。");
		  return 1;
	  }
    if(me->query(QUESTDIR3+"over"))
    {
    	command("heng");
    	command("say 蕭遠山，正是我父親。此仇不能不報。");
		return 1;
	}
    if(!me->query(QUESTDIR3+"over"))
    {
    	command("? "+me->query("id"));
		return 1;
	}
    command("? "+me->query("id"));
	command("say 蕭遠山，不認識......");
	return 1;
}
int ask_skills()
{
    object me;
    me=this_player();
    if(me->query("quest/天龍八部/武功/quanli"))
    {
		command("pat "+me->query("id"));
		command("say 不是都告訴你了嗎......");
		
		message_vision(HIY"\n$N向你呼的一拳打出，$n急忙應招。兩人所使的拳招，都是一般的平平無奇，但$N每一招都是\n"
			             +"慢了一步，任由$n先發。$n一出招，$N跟着遞招，也不知是由於他年輕力壯，還是行動加倍的\n"
						 +"迅捷，每一招都是後發先至。這“太祖長拳”本身拳招只有六十四招，但每一招都是相互剋制，\n"
						 +"$N看準了對方的拳招，然後出一招愉好剋制的拳法，$n焉得不敗？\n\n"NOR,this_object(),me);
		command("haha "+me->query("id"));
		return 1;
	}
    if(!me->query(QUESTDIR3+"over"))
    {
    	command("heng");
    	command("say 我正忙着報仇，此仇不能不報。");
		return 1;
	}
    //可以考慮增加一個太祖拳的pfm
	//純粹為了玩耍，威力一般甚至偏低

	command("say 不錯，武功至理，關鍵在一個融會貫通，無論後發制人，還是先發制人，都要看情況而定。");
	command("pat "+me->query("id"));
	command("say 何謂平淡，太祖拳可是江湖上是武林中最為流行的武功，但是其中三味，又有誰真正體會到？");
	command("haha "+me->query("id"));

	message_vision(HIY"\n$N驀地心念一動，呼的一拳打出，一招“衝陣斬將”，也正是“太祖長拳”中的招數。這一招\n"
		             +"姿工既瀟灑大方已極，勁力更是剛中有柔，柔中有剛，武林高手畢生所盼望達到的拳術完美之\n"
					 +"境， 竟在這一招中青露無遺。\n"NOR,this_object());
	command("noshame "+me->query("id"));
	message_vision(HIY"\n$N點了點頭，默想了一會，似乎對武功之道體會更深一步。\n\n"NOR,me);
	me->set("quest/天龍八部/武功/quanli",1);
	me->add("combat_exp",200);
	log_file("quest/TLBB", sprintf("%s(%s) 向蕭峯詢問拳理，獲得200點經驗。\n", me->name(1),me->query("id")) );
	return 1;
}
int ask_truth()
{
    object me;
    me=this_player();
    if(me->query(QUESTDIR4+"over"))
    {
    	command("say 一切都已經過去，就重新開始吧。");
		return 1;
	  }
    if(me->query(QUESTDIR3+"over"))
    {
    	command("heng");
		command("say 此等大仇不能不報。");
		return 1;
	  }
    if(!me->query(QUESTDIR3+"start"))
    {
    	command("? "+me->query("id"));
    	command("say 拜託，情節還沒開始，不要clone我好不。");
    	command("heng "+me->query("id"));
		return 1;
	}
	if(me->query_condition("killer"))
	{
	  	command("heng");
	  	command("say 你還是處理好和官府的關係吧。");
	  	return 1;
	}
    if(me->query(QUESTDIR3+"start")&&!me->query_temp(QUESTDIR3+"help"))
    {
    	command("? "+me->query("id"));
    	command("say 這麼快你能找到我？BUG啊，靠，老實交待誰在幫你？");
		return 1;
	}
    if(me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"help")&&!me->query_temp(QUESTDIR3+"askxiao"))
    {
    	message_vision(HIY"$N聽過$n的詢問，頓時似乎蒼老了很多。\n"NOR,this_object(),me);
    	command("say 我也不知道具體原委，這些日子以來，生不得安寧，朋友東分西裂，養父、師傅都無端被害。");
    	command("sigh");
    	command("say 我受傷未能遠行，還請這位"+RANK_D->query_respect(me) +"去一次頌摩崖，那裏據説有一塊刻字記載當年事蹟。");
    	command("shout");
    	command("thank "+me->query("id"));
    	me->set_temp(QUESTDIR3+"askxiao",1);
		return 1;
	}
    command("thank "+me->query("id"));
    command("say 一切有勞"+RANK_D->query_respect(me) +"了。");
	return 1;
}
int ask_yintui()
{
    object me;
    me=this_player();
    if(me->query(QUESTDIR4+"over"))
    {
    	command("say 一切都已經過去，就重新開始吧。");
		  return 1;
	  }
    if(me->query(QUESTDIR3+"good"))
    {
    	command("sigh");
    	command("say 也罷，天下何處不留人。這江湖中事我也不涉了，我既是契丹人，也該回我大遼。");
    	command("bye");
   		destruct(this_object());
		return 1;
	}
	if(me->query_condition("killer"))
	{
	  	command("heng");
	  	command("say 你還是處理好和官府的關係吧。");
	  	return 1;
	}
    if(!me->query_temp(QUESTDIR3+"good") && !me->query(QUESTDIR3+"good") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR3+"bad"))
    {
        remove_call_out("check_answer");
    	tell_object(me,HIW"你見蕭峯呆呆發矇，知道他正為這契丹人的身份傷神，卻聽蕭峯越來越暴躁，大聲號叫：“我不是漢人，我不是漢人！\n"
    	                  "我是契丹胡虜，我是契丹胡虜！”提起手來，一掌掌往山壁上劈去，壁上石屑四濺。喬峯心中鬱怒難伸，仍是一掌掌的\n"
    	                  "劈去，似要將這一個多月來所受的種種委屈，都要向這塊石壁發泄，到得後來，手掌出血，一個個血手印拍上石壁，他\n"
    	                  "兀自不停。\n\n"NOR);
		command("shout");
    	message_vision(HIY"$N漸漸發起狂來，神色卻是越來越是悲痛。\n\n"NOR,this_object());
    	tell_object(me,HIW"你知道似蕭峯這等武功若不及時勸説，這等悲憤只怕內功大有損傷，當即哈哈大笑一聲。果然，蕭峯怒視於你。你且自\n"
    	                  "顧説道：“大丈夫提得起、放得下，漢人中有好人壞人，契丹人中，自然也有好人壞人。你生為契丹人又當如何，只要\n"
    	                  "行俠仗義，這天下還不是要去要來”。\n\n"NOR);          	 
    	command("ah "+me->query("id"));
		me->set_temp(QUESTDIR3+"good",1);
		command("papaya");
    	command("consider");
		command("papaya "+this_object()->query("id"));
    	remove_call_out("xiaofeng_guiyin");
    	call_out("xiaofeng_guiyin",5,me);
		return 1;
	}
	if(me->query(QUESTDIR3+"over")&& me->query(QUESTDIR3+"bad"))
	{
		  command("heng "+me->query("id"));
		  kill_ob(me);
		  return 1;
   	}
	command("heng "+me->query("id"));
	return 1;
}
void xiaofeng_guiyin(object me)
{
   object ob=this_object();
   if(!me) 
   {
	   message_vision(HIW"$N急急忙忙地離開這裏。\n"NOR,ob);
	   destruct(ob);
	   return;
   }
  if(environment(ob)!=environment(me)) 
  {
    command("chat "+me->name()+"怎麼如此邋遢，竟然無端走開？");
    command("chat* heng "+me->query("id"));
    tell_object(me,HIG"\n你這種情況竟然臨陣逃脱，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
	me->delete_temp("quest/天龍八部");
	me->delete_temp("quest/busy");//任務衝突標誌取消
    me->delete(QUESTDIR3+"start");
    me->delete(QUESTDIR3+"over");
    me->add("mana",-200);
    if(me->query("mana")<0) me->set("mana",0);
	destruct(ob);
    return;
  }
  if(me->query_temp(QUESTDIR3+"good") && !me->query(QUESTDIR3+"good") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR3+"bad"))
  {
    command("nod "+me->query("id"));
    tell_object(me,HIG"\n卻見蕭峯臉色大見緩和，以蕭峯原本的大智慧，也定能明白這其中的道理。你也放下心來。\n"NOR);
    command("sigh");
    command("pat "+me->query("id"));
    command("say 也罷，我這就回我大遼，做我自己，還自行俠仗義，怎能這般自甘消沉。");
    command("haha");
    command("thank "+me->query("id"));
    command("wave "+me->query("id"));
    command("bye "+me->query("id"));
    me->set(QUESTDIR3+"good",1);
	me->delete_temp("quest/天龍八部");
	me->delete_temp("quest/busy");//任務衝突標誌取消
	me->set(QUESTDIR+"time",time());
	me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
	me->add("mana",me->query_skill("force")/4);
    tell_object(me,HIY"\n\n你於"+NATURE_D->game_time()+"選擇勸説蕭峯歸隱江湖，也算功德無量，獲得"+(int)me->query_skill("force")/4+"點聲望的獎勵。\n\n");
	log_file("quest/TLBB", sprintf("%s(%s) 選擇勸説蕭峯歸隱江湖。獲得%d點聲望。\n", me->name(1),me->query("id"), me->query_skill("force")/4) );
	destruct(ob);
  }
}
void kill_ob(object me)
{
 if(me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR3+"good") && !me->query(QUESTDIR3+"bad"))
  {
    message_vision(HIR"$N呼嘯一聲，雖然我並非最佳狀態，也不是"+me->name()+"之輩就能偷襲的！\n"NOR,this_object());
    command("chat* sneer "+me->query("id"));
   }
  ::kill_ob(me);
}
void die()
{
  object me,ob=this_object();
  int i;
  if(ob->query("kill_id")
         && (me=present(ob->query("kill_id"),environment(ob)))
	  && me->query(QUESTDIR3+"over")
	  && !me->query(QUESTDIR3+"good")
	  && me->query(QUESTDIR3+"bad"))
	{
		me->delete_temp("quest/天龍八部");
		me->delete_temp("quest/busy");//任務衝突標誌取消
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		command("chat* heng");
		command("chat 好好，"+me->name()+"竟然趁我不注意偷襲我，等我武功恢復之日，當是中原武林血洗之時！");
		command("sneer "+me->query("id"));
		command("dead "+me->query("id"));
		command("bye "+me->query("id"));
		i = 10+random(20);
		me->add("max_neili",i);
		tell_object(me,HIY"\n\n你於"+NATURE_D->game_time()+"選擇為武林除害，擊敗蕭峯，獲得"+i+"點內力的獎勵。\n\n");
		log_file("quest/TLBB", sprintf("%s(%s) 選擇擊敗蕭峯。獲得%d點內力。\n", me->name(1),me->query("id"), i) );
		destruct(ob);
		return;
	}
  if(ob->query("daliao")
    && (me=find_player(ob->query("daliao")))
    && me->query(QUESTDIR4+"start")
    && !me->query(QUESTDIR4+"over"))
	{
		command("chat* inn "+me->query("id"));
		command("say 想不到敵人如此強勁，"+me->name()+"不要管我，你還是先自離開吧，不要枉自送了性命，有機會再會！");
		command("dead");
		command("wave "+me->query("id"));
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		me->delete_temp("quest/天龍八部");
		me->delete_temp("quest/busy");//任務衝突標誌取消
		tell_object(me,HIY"\n\n你於"+NATURE_D->game_time()+"營救蕭峯失敗。\n\n");
		log_file("quest/TLBB", sprintf("%s(%s) 營救蕭峯失敗，蕭峯死亡。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")));
		destruct(ob);
		return;
  }
  if(ob->query("no_death"))
  {
	  ob->set("qi", ob->query("max_qi")*2/3);
	  ob->set("eff_qi", ob->query("max_qi")*2/3);
	  ob->set("jing", ob->query("max_jing"));
	  ob->set("eff_jing", ob->query("max_jing"));
	  ob->add("neili", ob->query("max_neili")*2);
	  ob->set("jingli", ob->query("max_jingli"));
	  if(ob->is_busy()) ob->start_busy(-1);	  
	  message_vision("$N深深吸了幾口氣，臉色看起來好多了。\n", ob);
	  message_vision("$N深深吸了幾口氣，精神看起來好多了。\n", ob);
	  message_vision(HIR "\n$N微一凝神，運起混天氣功，全身骨節發出一陣爆豆般的聲響。\n" NOR, ob);
	  command("heng");
	  return;
  }
  ::die();
}
void unconcious()
{
  die();
}
void dest(object ob)
{
  if(!ob) return;
  tell_room(environment(ob), HIR+"\n"+ob->name()+"匆匆忙忙地離開了。\n"NOR);
  destruct(ob);
}

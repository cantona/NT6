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
void greeting(object me);
void xiaofeng_guiyin(object me);
void create()
{
	set_name("蕭峯", ({"xiao feng", "xiao", "feng"}));
	set("gender", "男性");
	set("title",HIB"奇俠"NOR);
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
	set("neili", 60000);
	set("max_neili", 35000);
	set("jiali", 200);
  set("max_jingli", 15000);
  set("jingli", 15000);
	set("eff_jingli", 15000);
  set("combat_exp", 10000000);	 
	set_skill("force", 420);   
	set_skill("bangjue", 200);
	set_skill("literate", 200);        
	set_skill("medicine", 200);        
	set_skill("huntian-qigong", 420);
	set_skill("yijin-jing", 200);     
	set_skill("strike", 420);           
	set_skill("jingang-quan", 420);     
	set_skill("xianglong-zhang", 420);     
	set_skill("dodge", 420);      	     
	set_skill("xiaoyaoyou", 420);   
	set_skill("parry", 420);          
	set_skill("stick", 420);          
	set_skill("dagou-bang", 420);          
	set_skill("cuff", 420);          
	map_skill("cuff", "jingang-quan");
	map_skill("force", "huntian-qigong");
	map_skill("strike", "xianglong-zhang");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "xianglong-zhang");
	map_skill("stick", "dagou-bang");
	prepare_skill("strike","xianglong-zhang");
	prepare_skill("cuff","jingang-quan");
  set("chat_chance_combat", 99);
  set("chat_msg_combat", ({
          (: exert_function, "huntian" :),
          (: exert_function, "shentong" :),
          (: perform_action, "strike.paiyun" :),
          (: perform_action, "strike.xiao" :),
  }));
  set("inquiry", ([
		"段譽" : random(2)?"那是我二弟。\n":"我二弟一身內力震古爍今，六脈神劍更是天下無雙。\n",
		"虛竹" : random(2)?"那是我三弟。\n":"我三弟現為縹緲宮宮主，只怕現在更是西夏國的駙馬爺了。\n",
		"真相" : (: ask_truth :),
		"蕭遠山" : (: ask_father :),
		"拜師" : "嗯....，我註定一聲漂泊，還是算了吧。\n",
		"丐幫" : "丐幫是我家，我家在丐幫。",
		"丐幫" : "我一身武功出自少林，也算是半個少林弟子。",
		"天龍寺" : "天龍寺是大理段家武學的最高之地。",
		"洪七公" : "恩，聽説下一輩中也是他為人最為俠義，武功最高。",
		"阿朱" : "......怕是這一生我唯一的牽掛了。",
		"阿紫" : "恩，不提也罷，丁老怪的弟子，那個不是心狠手辣。",
		"阿碧" : "阿朱的妹妹，聽説和慕容公子在一起。",
		"天龍寺" : "天龍寺是大理段家武學的最高之地。",
		"降龍十八掌" : "這是我行走江湖的吃飯的東西，哈哈。",
		"打狗棒" : "丐幫幫主之外不傳之武功，確實精妙無比。",
		"歸隱" : (: ask_yintui :),
		"隱退" : (: ask_yintui :),
		"洗手" : (: ask_yintui :),
		"隱退江湖" : (: ask_yintui :),
		"歸隱江湖" : (: ask_yintui :),
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
	object me,room;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
  	if(!me->query_condition("killer")&&me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over"))
    {
	    this_object()->set("qi", this_object()->query("max_qi"));
	    this_object()->set("eff_qi", this_object()->query("max_qi"));
	    this_object()->set("neili", this_object()->query("max_neili")*2);
      tell_object(me,CYN"你驚訝地「啊！」了一聲。\n"NOR);    
      message_vision(HIW"$N長長地舒了一口氣，傷勢看來基本全部恢復了。"NOR,this_object());                    
      tell_object(me,HIC"\n你沒有料道，蕭峯竟然恢復如此之迅速，果然是功夫了得。\n"NOR);  
      command("thank "+me->query("id"));
      //remove_call_out("greeting");
		  call_out("greeting",2,me);
    }
	 	if(!me->query_condition("killer")&& me->query(QUESTDIR4+"start") && me->query_temp(QUESTDIR4+"breakmen") && !me->query(QUESTDIR4+"over"))
    {
    	command("ah "+me->query("id"));
    	command("say 沒想到，又是大俠捨命相救。"); 
    	command("thank "+me->query("id"));
      me->start_busy(2);
		  tell_object(me,HIC"\n你上前説道，“我們還是趕快離開此地，只怕這次為了營救你，江湖中人已全部出動，無論丐幫、少林、大理、\n"
		                      "還是遠在西域的縹緲七十二宮。”\n"NOR);
		  command("sigh");
		  command("say 好，我們這就趕快一起闖出去。");
      if (!(room = find_object("/d/xingxiu/silk3")))
          room = load_object("/d/xingxiu/silk3");
      if(!room)
      { 
      	tell_object(me,HIR"\n趕快找wiz吧，竟然房間不存在!!!\n");
      }
      else
      {
                      me->set(QUESTDIR4+"over",1);
                      me->set(QUESTDIR+"time",time());
                      me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
                      me->delete_temp(QUESTDIR4+"dagouzhen");
                      me->delete_temp(QUESTDIR4+"shaolinzhen");
                      me->delete_temp(QUESTDIR4+"kill");
                      me->delete_temp(QUESTDIR4+"anhao");
                      me->delete_temp(QUESTDIR4+"count");
                      me->delete_temp(QUESTDIR4+"breakmen");
                      me->delete_temp(QUESTDIR4+"askxuanci");
                      me->delete_temp(QUESTDIR4+"askwu");
                  me->move("/d/xingxiu/daliao/shanlu3");
                  this_object()->move("/d/xingxiu/daliao/shanlu3");
                  me->move("/d/xingxiu/daliao/shanlu2");
                  this_object()->move("/d/xingxiu/daliao/shanlu2");
                  me->move("/d/xingxiu/daliao/shanlu1");
                  this_object()->move("/d/xingxiu/daliao/shanlu1");
                  "/cmds/std/look.c"->look_room(me,environment(me)); 
   		  me->move(room);
   		  this_object()->move(room);
   		  "/cmds/std/look.c"->look_room(me, room); 
        tell_object(me,HIG"\n你們邊打邊退，一路奔波，連續走過好幾個地方，才來到一個斷崖邊。也巧，這裏正是當年蕭峯雙親雙亡的地方。\n"NOR);
        message_vision(HIW"$N長長地舒了一口氣。\n"NOR,this_object());
   		  command("whisper "+me->query("id")+" 也算終於脱險了，我與中原武林之間的恩恩怨怨葉一筆勾銷。");
   		  command("chat* thank "+me->query("id"));
   		  command("wave "+me->query("id"));
   		  command("chat* byebye");
		    me->add("max_neili",me->query_skill("force")/2);
		    me->add("combat_exp",me->query_skill("force"));
		    me->add("shen",me->query_skill("force")*5);
		    me->add("mana",me->query_skill("force")/2);
        tell_object(me,HIY"\n你於"+NATURE_D->game_time()+"終於將蕭峯從大遼解救出來，獲得"+(int)me->query_skill("force")/2+"點最大內力、"+(int)me->query_skill("force")+"點經驗和"+(int)me->query_skill("force")/2+"點聲望。\n\n");
        log_file("quest/TLBB", sprintf("%s(%s) 終於將蕭峯從大遼解救出來，時間 %s。獲得%d點最大內力，%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), ctime(time()),me->query_skill("force")/2,me->query_skill("force"),me->query_skill("force")/2) );
                    destruct(this_object());
                    return;
 	    }
    }
	} 
}

void greeting(object me)
{
	if(!me) return;
  if(environment(this_object())!=environment(me)) 
  {
    command("chat "+me->name()+"怎麼如此邋遢，竟然無端走開？");
    command("chat* heng "+me->query("id"));
    tell_object(me,HIG"\n你這種情況竟然臨陣逃脱，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
    me->delete_temp(QUESTDIR3+"kill");
    me->delete_temp(QUESTDIR3+"lookcliff");
    me->delete(QUESTDIR3+"start");
    me->add("mana",-200);
    if(me->query("mana")<0) me->set("mana",0);
    return;
	}
	if(me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over"))
  {
    command("thank "+me->query("id"));
    command("say 再次感謝大俠救命之恩。");
    tell_object(me,HIG"\n\n你走過去看了看蕭峯，還是將你看到的告訴了蕭峯：智光大師所道的山壁上如今正中一大片盡是斧鑿的印痕，\n"
                          "顯而易見，是有人故意將留下的字跡削去了。\n"NOR);
	  tell_room(environment(me),HIG"\n"+me->name()+"走到蕭峯跟前，低聲説了些什麼。\n"NOR, ({ me }));
    command("ah");
    message_vision(HIW"$N突然悲笑起來，喃喃道：“看來我真是契丹人，我真的不是漢人。”\n"NOR,this_object());
    command("say");
    message_vision(HIC"$N神色漸漸有些不正常，似乎已經有些發狂。\n"NOR,this_object());
    tell_object(me,HIW"\n突然之間，你腦子閃過兩個念頭。一個因為這蕭峯已確是契丹人，他若公開反對大宋，只怕朝廷不知多少人因此\n"
                        "喪命，而且此時你趁他意亂傷神之際，正是揚你威名的大好時機；可是一個俠義之心告訴你，如此確似小人行為\n"
                        "一般不堪，這契丹人中也有好人壞人，也可以行俠仗義，何必執著於身份。\n"NOR);
    tell_object(me,HIR"\n一時間，你是勸其歸隱（ask xiao about 歸隱），還是為武林除害（kill xiao）？你一時委實難以決定。\n"NOR);
    me->set(QUESTDIR3+"over",1);
    me->start_busy(3);
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
    	command("say 這麼快你能找到我？BUG啊，靠，説：誰在幫你？");
		  return 1;
	  }
    if(me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"help")&&!me->query_temp(QUESTDIR3+"askxiao"))
    {
    	message_vision(HIY"$N聽過$n的詢問，頓時似乎蒼老了很多。\n"NOR,this_object(),me);
    	command("say 我也不知道具體原委，這些日子以來，生不得安寧，朋友東分西裂，養父、師傅都無端被害。");
    	command("sigh");
    	command("say 我受傷未能遠行，還請這位大俠去一次頌摩崖，那裏據説有一塊刻字記載當年事蹟。");
    	command("thank "+me->query("id"));
    	me->set_temp(QUESTDIR3+"askxiao",1);
		  return 1;
	  }
    command("thank "+me->query("id"));
    command("say 一切有勞大俠了。");
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
    if(!me->query(QUESTDIR3+"good") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR3+"bad"))
    {
    	tell_object(me,HIW"你見蕭峯呆呆發矇，知道他正為這契丹人的身份傷神，卻聽蕭峯越來越暴躁，大聲號叫：“我不是漢人，我不是漢人！\n"
    	                  "我是契丹胡虜，我是契丹胡虜！”提起手來，一掌掌往山壁上劈去，壁上石屑四濺。喬峯心中鬱怒難伸，仍是一掌掌的\n"
    	                  "劈去，似要將這一個多月來所受的種種委屈，都要向這塊石壁發泄，到得後來，手掌出血，一個個血手印拍上石壁，他\n"
    	                  "兀自不停。\n\n"NOR);
    	message_vision(HIY"$N漸漸發起狂來，神色卻是越來越是悲痛。\n"NOR,this_object());
    	tell_object(me,HIW"你知道似蕭峯這等武功若不及時勸説，這等悲憤只怕內功大有損傷，當即哈哈大笑一聲。果然，蕭峯怒視於你。你且自\n"
    	                  "顧説道：“大丈夫提得起、放得下，漢人中有好人壞人，契丹人中，自然也有好人壞人。你生為契丹人又當如何，只要\n"
    	                  "行俠仗義，這天下還不是要去要來”。\n\n"NOR);          	 
    	command("ah "+me->query("id"));
    	command("consider");
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
	if(!me) return;
  if(environment(this_object())!=environment(me)) 
  {
    command("chat "+me->name()+"怎麼如此邋遢，竟然無端走開？");
    command("chat* heng "+me->query("id"));
    tell_object(me,HIG"\n你這種情況竟然臨陣逃脱，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
    me->delete_temp(QUESTDIR3+"kill");
    me->delete_temp(QUESTDIR3+"lookcliff");
    me->delete(QUESTDIR3+"start");
    me->delete(QUESTDIR3+"over");
    me->add("mana",-200);
    if(me->query("mana")<0) me->set("mana",0);
    return;
  }
  if(!me->query(QUESTDIR3+"good") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR3+"bad"))
  {
    command("nod "+me->query("id"));
    tell_object(me,HIG"\n卻見蕭峯臉色大見緩和，以蕭峯原本的大智慧，也定能明白這其中的道理。你也放下心來。\n"NOR);
    command("say 也罷，我這就回我大遼，做我自己，還自行俠仗義，怎能這般自甘消沉。");
    command("thank "+me->query("id"));
    command("bye");                     
    me->set(QUESTDIR3+"good",1);
		me->add("mana",me->query_skill("force")/2);
		me->add("shen",me->query_skill("force")*5);
    tell_object(me,HIY"\n\n你於"+NATURE_D->game_time()+"選擇勸説蕭峯歸隱江湖，也算功德無量，獲得"+(int)me->query_skill("force")/2+"點聲望的獎勵。\n\n");
    log_file("quest/TLBB", sprintf("%s(%s) 選擇勸説蕭峯歸隱江湖，時間 %s。獲得%d點聲望。\n", me->name(1),me->query("id"), ctime(time()),me->query_skill("force")/2) );
	  destruct(this_object());
	}
}
void die()
{
	object me,ob=this_object();
	me=ob->query_temp("last_damage_from");
        if(userp(me=ob->query_temp("last_damage_from")) 
	  && me->query(QUESTDIR3+"over")
	  && !me->query(QUESTDIR3+"good")
	  && !me->query(QUESTDIR3+"bad"))
	{
 	  me->set(QUESTDIR3+"bad",1);
 	  command("chat* heng");
    command("chat 好好，"+me->name()+"竟然趁我不注意偷襲我，等我武功恢復之日，當是中原武林血洗之時！");
		me->add("max_neili",me->query_skill("force")/2);
		me->add("shen",-me->query_skill("force")*5);
    tell_object(me,HIY"\n\n你於"+NATURE_D->game_time()+"選擇為武林除害，擊敗蕭峯，獲得"+(int)me->query_skill("force")/2+"點內力的獎勵。\n\n");
    log_file("quest/TLBB", sprintf("%s(%s) 選擇擊敗蕭峯，時間 %s。獲得%d點內力。\n", me->name(1),me->query("id"), ctime(time()),me->query_skill("force")/2) );
	  destruct(this_object());
  }
  else if(this_object()->query("no_death"))
  {
	ob->set("qi", 20000);
	ob->set("eff_qi", 20000);
	ob->set("jing", 15000);
	ob->set("max_jing", 15000);
	ob->add("neili", 8000);
  ob->set("jingli", 15000);
	ob->set("jing", 15000);
  command("heng");
  message_vision(HIR "\n$N微一凝神，運起混天氣功，全身骨節發出一陣爆豆般的聲響。\n" NOR, ob);
	}
   ::die();
}
void unconcious()
{
  die();
}

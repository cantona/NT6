//cool@SJ,990605
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
void new_happen(object me);
string ask_kurong();

void create()
{
        set_name("本因大師", ({ "benyin dashi","benyin","dashi"}) );
        set("nickname", "天龍寺主持");
	set("long", "一位白鬚白眉的老僧，身穿一襲金絲木棉袈裟。\n"+
			"若以俗家輩份排列，本因大師應是當今大理國保定帝的俗家叔父。\n");
	set("gender", "男性" );
        set("attitude", "friendly");
        set("age", 69);
        set("str", 25);
        set("int", 26);
        set("con", 28);
        set("dex", 26);
	set("unique", 1);

	set("class", "bonze");
	set("shen", 10);
        set("jing", 2000);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 100);
        set("qi", 3000);
        set("max_qi", 3000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("combat_exp", 1350000);

        set_skill("qiantian-yiyang", 165);
        set_skill("tianlong-xiang", 165);
        set_skill("yiyang-zhi", 150);
        set_skill("duanjia-jianfa",170);
        set_skill("buddhism", 165);
        set_skill("literate", 120);
        set_skill("parry", 160);
        set_skill("finger", 165);
        set_skill("sword", 160);
        set_skill("dodge", 165);
        set_skill("kurong-changong", 100);
        set_skill("force", 160);
        set_skill("liumai-shenjian", 120);
        set_skill("medicine", 110);
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "yiyang-zhi");
        map_skill("sword", "duanjia-jianfa");
        map_skill("finger", "yiyang-zhi");
        prepare_skill("finger","yiyang-zhi");
        create_family("天龍寺", 13, "方丈");
	set("inquiry", ([
		"name": "貧僧就是本因",
		"龍樹院" : "龍樹院在雨花閣後面的松樹林中",
		"枯榮" : "枯榮大師在龍樹院參悟",
		"枯榮大師" : "枯榮大師在龍樹院參悟",
		"松樹林" : (: ask_kurong :),
		"龍樹院" : (: ask_kurong :),
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
        ]) );
        set("chat_chance_combat", 30);
        set("chat_msg_combat",({
              (: perform_action, "finger.sandie" :),
        }));
        setup();
        carry_object(BINGQI_D("changjian"))->wield();
        carry_object("/d/tls/obj/nianzhu")->wear();
        carry_object("/d/tls/obj/jiasha")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();
}

string ask_kurong()
{
	object me,ob;
	mapping ob_fam,my_fam;
	ob=this_player();
	me=this_object();
	ob_fam = (mapping)ob->query("family");
	my_fam = (mapping)me->query("family");

	if ((ob_fam && ob_fam["family_name"] != "天龍寺")||ob->query("class") != "bonze")
		return ("對不起，你不能去打擾枯榮大師！\n");
	if (ob_fam["generation"] == (my_fam["generation"] + 1)){
		return ("松林很密，容易迷路，你一進林，向北走四步，向西走三步，再向北走一步，西走三步就到了 \n");
	} 
	else return ("你輩分不夠，不能去拜見枯榮大師。 \n");
}

#include "ben.h";

void init()
{
	object me,obj1,obj2;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
	 	if(me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"kill_dizi"))
    {
    	command("look "+me->query("id"));
    	command("touch "+me->query("id"));
    	command("say 有這位"+RANK_D->query_respect(me) +"幫忙，本寺當可高枕無憂了。"); 
    }
	 	if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"caught") && !me->query(QUESTDIR2+"over"))
    {
    	command("sigh");
    	command("say 段王子被抓，這如何是好，我佛慈悲，但願王子吉人天相啊。"); 
    }
	
	if(me->query(QUESTDIR2+"start") 
		&& !me->query_temp(QUESTDIR2+"caught_") 
		&& !me->query_temp(QUESTDIR2+"caught") 
		&& !me->query(QUESTDIR2+"over")
		&& me->query_temp(QUESTDIR2+"kill_dizi"))
    {
    	command("look "+me->query("id"));
    	command("touch "+me->query("id"));
    	command("say 多些這位"+RANK_D->query_respect(me) +"幫忙，本寺當可高枕無憂了。"); 
      tell_object(me,HIG"\n你走進大廳，卻發現這裏更是熱鬧非凡，場中兩人正都在一起，那身受僧衣的怕就是鳩摩智了，另外一個竟然正是大理王子段譽，\n"
                          "武功之高，世上罕見。\n"NOR);
      if(!(obj1=present("duan yu",this_object()))||!(obj1=present("zhongnian nanzi",this_object())))
      {
  	     obj1=new("/d/dali/wuliang/npc/dy");
		 obj1->set_name("段譽", ({ "duan yu", "duan","yu"}) );
		 obj1->set("title",HIB"大理國鎮南王世子"NOR);
		 obj1->set("long", "大理國鎮南王之子。");	
  	     obj1->move(environment(me));
      }
      if(!(obj2=present("jiumo zhi",this_object())))
      {
  	     obj2=new("/kungfu/class/xueshan/jiumozhi");
  	     obj2->move(environment(me));
      }
      message_vision(HIC"只見斗室中劍氣縱橫，刀勁飛舞，便似有無數迅雷疾風相互衝撞激盪。鳩摩智只覺得段譽內勁越來越強，劍法也是變化莫測，\n"
                        "隨時自創新意，與適才本因、本相等人的拘泥劍招大不相同，令人實難捉摸。他自不知段譽記不明白六路劍法中這許多繁複的\n"
                        "招式，不過危急中隨指亂刺，那裏是什麼自創新招了？心下既驚且悔：“天龍寺中居然伏得有這樣一個青年高手，今日當真是\n"
                        "自取其辱。”突然間嗤嗤嗤連砍三刀，叫道：“且住！” \n\n"NOR,me);   
         
      message_vision(HIM"\n段譽當即收招，只是你卻發現他真氣竟然不能隨意收發，只將手指一抬向懷頂指去，$N不禁暗叫不好，抬眼望去鳩摩智似已有覺悟。\n\n"NOR,me);   
	  me->start_busy(1);
	  remove_call_out("new_happen");
	  me->set_temp(QUESTDIR2+"caught_",1);
      call_out("new_happen",6, me);
    }
	} 
}
void new_happen(object me)
{
  object obj1,obj2,ob;
  ob = this_object();
  if(!me) 
  {
	  command("?");
	  if((obj1=present("duan yu",environment(ob))))
		  destruct(obj1);
	  if((obj1=present("zhongnian nanzi",environment(ob))))
		  destruct(obj1);
	  if((obj1=present("jiumo zhi",environment(ob))))
		  destruct(obj1);
	  return;
  }
  if(environment(ob)!=environment(me)) 
  {
	  command("say 怎麼關鍵時候，"+me->name()+"在何處？");
	  me->delete(QUESTDIR2+"start");
	  me->delete_temp("quest/天龍八部");
	  me->delete_temp("quest/busy");//任務衝突標誌取消 
	  command("heng");
	  return;
  }
  
  if(!(obj1=present("duan yu",environment(ob)))&& !(obj1=present("zhongnian nanzi",environment(ob))))
  {
	  command("ah");
	  command("say 段譽呢？這麼快，除了鳩摩智，誰將他搶走呢？");
	  me->delete(QUESTDIR2+"start");
	  me->delete_temp("quest/天龍八部");
	  me->delete_temp("quest/busy");//任務衝突標誌取消 
	  command("?");
	  tell_object(me,HIR"段譽不知所蹤，任務失敗。\n"NOR);
	  if((obj2=present("jiumo zhi",environment(ob))))
	  {
		  message_vision(HIG"\n$N似乎也感到莫名其妙，轉身離開了。\n"NOR,obj2);
		  destruct(obj2);
	  }
	  return;
  }
  
  if(!(obj2=present("jiumo zhi",environment(this_object()))))
  {
	  command("ah");
	  command("say 鳩摩智呢？竟然莫名其妙退走了？");
	  me->delete(QUESTDIR2+"start");
	  me->delete_temp("quest/天龍八部");
	  me->delete_temp("quest/busy");//任務衝突標誌取消 
	  command("?");
	  tell_object(me,HIR"繼續情節無法展開。\n"NOR);
	  if((obj1=present("duan yu",environment(ob))))
	  {
		  message_vision(HIG"\n$N高興地跳了起來，轉身離開了。\n"NOR,obj1);
		  destruct(obj1);
	  }
	  return;
  }
  
  if(me->query(QUESTDIR2+"start") 
	  && me->query_temp(QUESTDIR2+"caught_") 
	  && !me->query_temp(QUESTDIR2+"caught") 
	  && !me->query(QUESTDIR2+"over")
	  && me->query_temp(QUESTDIR2+"kill_dizi"))
  {
 
    message_vision(HIY"\n果然，鳩摩智見段譽臉有迷惘之色，收斂真氣時手忙腳亂，全然不知所云，心念微動，便即縱身而上，揮拳向他臉上擊去。他見鳩\n"
                        "摩智揮拳打到，便即毛手毛腳的伸臂去格。鳩摩智右掌翻過，已抓住了他胸口‘神封穴’。段譽立時全身痠軟，動彈不得。鳩摩智\n"
                        "立即伸指又點他‘極泉’、‘大椎’、‘京門’數處大穴。鳩摩智倒退三步，説道：“這位小施主心中記得六脈神劍的圖譜。原來\n"
                        "的圖譜已被枯榮大師焚去，小施主便是活圖譜，在慕容先生墓前將他活活的燒了，也是一樣。”左掌揚處，向前急連砍出五刀，抓\n"
                        "住段譽退出了牟尼堂門外。\n\n"NOR,me);  
   	command("@@");
    message_vision(HIY"\n這生變化實在出乎意料之外，你雖已瞧出段譽武學之中隱伏有大大的破綻，卻也決計料想不到，竟能如此輕而易舉的手到擒來。等\n"
                        "鳩摩智拿人走人之時，已經來不及了。本因等縱前想要奪人，均被他這連環五刀封住，無法搶上。\n\n"NOR,me);  
   	command("wah");
    message_vision(HIC"\n鳩摩智長笑説道：“燒了死圖譜，反得活圖譜。慕容先生地下有人相伴，可不覺寂寞了！”右掌斜劈，喀喇喇一聲響，將牟尼堂的\n"
                        "兩根柱子劈倒，身形微幌，便如一溜輕煙般奔入林中，剎那間不知去向。你和本因雙雙搶出，見鳩摩智已然走遠。卻聽內堂枯榮長\n"
                        "老道：“快追！”衣襟帶風，一飄數丈。似是本參大師和他並肩齊行，向北追趕。 \n\n"NOR,me);
    me->set_temp(QUESTDIR2+"caught",1);
	destruct(obj1);
	destruct(obj2);
   	return;
  }
}
string askjiumozhi()
{
	object me;
	object *obj;
	int x;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "聽説，大輪寺第一高僧鳩摩智將來我天龍寺佛法交流，真是我大理之幸啊。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query_temp(QUESTDIR2+"jiumozhi")&&!me->query(QUESTDIR2+"over"))
	{
      //增加時間和經驗間隔限制
      //時間一天，經驗500K
      if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
   	                 return "感謝"+RANK_D->query_respect(me) +"如此仗義。今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
      if(me->query(QUESTDIR+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000)
  	                return "以"+RANK_D->query_respect(me) +"目前的經驗就算目前有情況，也幫不上什麼忙，還是抓緊練功吧！";
      //設定標誌
	  tell_object(me,HIW"\n你素知大輪明王鳩摩智是吐蕃國的護國法王，但只聽説他具大智慧，精通佛法，想來武功也是超高。只是這等\n"NOR);
  	  tell_object(me,HIW"明搶之事，確實不通情理。‘六脈神劍經’更是天龍寺鎮寺之寶，這等上門要書的做法擺明就是欺負他人。\n"NOR);
  	  tell_object(me,HIC"你打定主意道：這等欺負人的行徑，確是武林不齒，在下不才，也要管上一管。\n\n"NOR);
	  command("touch "+me->query("id"));
  	  obj = users();
	  x = sizeof(obj);
	  while(x--) {
		  if ( obj[x]->query_temp(QUESTDIR2+"jiumozhi") && obj[x]!=me) 
			  return "不過，有"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已經在幫我了，"+RANK_D->query_respect(me) +"還是抓緊練功吧！";		  
	  }
	  me->set(QUESTDIR+"time",time());
	  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));        

  	  me->set_temp(QUESTDIR2+"jiumozhi",1);
	  me->set_temp("quest/busy",1);//與任務系統衝突標誌
	  log_file("quest/TLBB", sprintf("%s(%s) 開始天龍八部天龍寺救援篇。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	  return "這大輪明王也算是舉世聞名的高僧了，怎能恁地不通情理，膽敢向本寺強要此經？只怕善意者不來，來者不善，\n"
		         "此事後果非小，我作不得主，請枯榮師叔出來主持大局。不過，這次有"+RANK_D->query_respect(me) +"相助，只怕是明王的失算了。\n"
		         "\n"NOR+HIG+me->name()+"點頭道：有枯榮師叔出來主持大局最好。我且先到天龍寺門口一看。"NOR;
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "多謝"+RANK_D->query_respect(me) +"相助。只是這魔僧妄為吐蕃國第一佛法高僧。";
  }

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
                  return "蕭峯，難不是你所迫出中原，今日所謂搭救不知何意！";
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
		  return "我佛慈悲。小王子自萬劫谷回來，總是氣血不定，才被送往我天龍寺枯榮長老那裏求救來了。";
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
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   return "天龍寺和中原官府應該沒有半點關係，"+RANK_D->query_respect(me) +"還是自我小心通緝！";
	}
  if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("sigh");
	  tell_object(me,HIY"只見本因方丈從懷中取出一封金光燦爛的信箋，遞在你手中。你接了過來，着手重甸甸地，但見這信奇異之極。\n"NOR);
  	  tell_object(me,HIY"你識得寫的是：“書呈崇聖寺住侍”，從金套中抽出信箋，也是一張極薄的金箋，上用梵文書寫，大意説：“\n"NOR);
  	  tell_object(me,HIG"當年與姑蘇慕容博先生相會，訂交結友，談論當世武功。慕容先生言下對貴寺‘六脈神劍’備致推崇，深以未\n"NOR);
  	  tell_object(me,HIG"得拜觀為憾。近聞慕容先生仙逝，哀痛無已，為報知己，擬向貴寺討求該經，焚化於慕容先生墓前，日內來取，\n"NOR);
  	  tell_object(me,HIG"勿卻為幸。貧僧自當以貴重禮物還報，未敢空手妄取也。”信末署名‘大雪山大輪寺釋子鳩摩智合十百拜’。\n"NOR);
  	  command("heng");

  	  command("look "+me->query("id"));
  	  if(me->query("combat_exp")<3000000)		  return ""+RANK_D->query_respect(me) +"好意心領了，只是只怕那鳩摩智武功高強，你也無法幫忙多少。";
  	  if(me->query("shen")<0)		  return ""+RANK_D->query_respect(me) +"好意心領了，只是......。";

  	  me->set(QUESTDIR2+"start",1);
	  return "如果能有"+RANK_D->query_respect(me) +"幫忙，只怕我天龍寺這次當高枕無憂了。";
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

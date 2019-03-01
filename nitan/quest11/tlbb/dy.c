// duanyu.c 段譽
// COOL@SJ,990827
// Modified by tangfeng 2004
// 這裡的段譽涉及到三個場景，一個在無量玉像，一個在石屋裡，一個在大倫寺暗室裡
// By Spiderii@ty 加入時間限制
inherit F_MASTER;
#include <ansi.h>
inherit NPC;

#define QUESTDIR "quest/天龍八部/"
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"
#define QUESTDIR3 "quest/天龍八部/蕭峰身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"
#define QUESTDIR6 "quest/天龍八部/武功/"

string tianlonghelp();
string askxiaofeng();
string askjiumozhi();
string ask_name();
int ask_home();
int ask_save();
void outroom(object me);
void dest(object me,object ob);
void greeting(object me);

void create()
{
        set_name("青年男子", ({"qingnian nanzi", "nanzi", "man"}));
        set("gender", "男性");
        set("age", 20);
        set("long", "這是一個青年男子，披頭散發，赤裸著上身，下身只系著一條短褲，露出\n"
                    "了兩條大腿，臉孔略尖，眼神似乎有些發狂。\n");
        set("attitude", "peaceful");
        set("str", 15);
        set("per", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("no_quest", 1);

        set("inquiry", ([
		"段譽" : (: ask_name :),
		"name" : (: ask_name :),
		"獲救" : (: ask_save :),
		"救你" : (: ask_save :),
		"救段譽" : (: ask_save :),
		"救你們" : (: ask_save :),
		"搭救" : (: ask_save :),
		"解救" : (: ask_save :),
		"save" : (: ask_save :),
		"段延慶" : "就是他把我關進來的。\n",
		"拜師" : "嗯....，我的師傅是老子、孔子和莊子，他們的學問我還沒學全呢。\n",
		"大理" : "大理是我家，我家在大理。",
		"天龍寺" : "天龍寺是大理段家武學的最高之地。",
		"天龍有難" : (: tianlonghelp :),
		"蕭峰" : "我大哥蕭峰啊，端得一條好漢。",
		"營救蕭峰" : (: askxiaofeng :),
		"慕容復" : "慕容公子確是其江南文採，詩琴書畫無所不精，武功更是冠絕天下。",
		"慕容博" : "我聽說是，姑蘇慕容不出的傑才，可惜英年早逝。",
		"鳩摩智" : (: askjiumozhi :),
		"六脈神劍" : "天龍寺最高絕學。",
		"段正淳" : "那是我爹爹。",
		"刀白鳳" : "你找我媽媽有什麼事情？",
		"段正明" : "你找我伯父有什麼事情？",
		"虛竹" : "你找我三弟有什麼事情？",

		"回家" : (: ask_home :),
		"go home" : (: ask_home :),

		//六脈神劍的quest好像有人做了一半，在枯榮長老身上有部分描述
        ]));

        set("jing", 10000);
        set("max_jing", 10000);
        set("jingli", 10000);
        set("eff_jingli", 10000);
        set("qi", 50000);
        set("max_qi", 20000);
        set("neili", 60000);
        set("max_neili", 40000);
        set("jiali",500);
        
        set("combat_exp", 15000000);
        set_skill("buddhism", 250);            
        set_skill("daode-jing", 250);                   
        set_skill("literate", 300);                
        set_skill("force", 600);                
        set_skill("beiming-shengong", 600);     
        set_skill("dodge", 600);                
        set_skill("lingbo-weibu", 600);         
        set_skill("parry", 300);
        set_skill("finger", 300);
        set_skill("yiyang-zhi", 200);
        set_skill("liumai-shenjian", 200);
        map_skill("parry", "yiyang-zhi");
        map_skill("finger", "yiyang-zhi");
        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
        setup();        
}
void init()
{
	object me;
	me = this_player();
	::init();
	if (interactive(me) && living(me) 
		&& !me->query_condition("killer")
		&& me->query(QUESTDIR1+"start") ) {
		me->start_busy(2);
        remove_call_out("greeting"); 
		call_out("greeting",2,me);
	} 
}
void greeting(object me)
{
	if(!me) return;
	if(environment(this_object())!=environment(me)) return;

	if(!me->query_condition("killer")&&me->query(QUESTDIR1+"start") 
			&& !me->query_temp(QUESTDIR1+"see_duanyu1")
			&& !me->query_temp(QUESTDIR1+"see_duanyu2")
			&& !me->query(QUESTDIR1+"wuliangover")
			&& me->query_temp(QUESTDIR1+"jianying"))
    {
		//玉像處
		  message_vision(HIC"\n$N一轉身大吃一驚，卻發現身旁卻見一個男子站在玉像前，痴痴的呆看著，那表情竟然由愛生敬，由敬成痴。\n"NOR, me);  
		  log_file("quest/TLBB", sprintf("%s(%s) 凌波微步玉像處遇見段譽。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
		  me->set_temp(QUESTDIR1+"see_duanyu2",1);
		  me->start_busy(1);
		  command("crazy");
		  command("say");
    }
	
	if(!me->query_condition("killer")
		&& me->query(QUESTDIR2+"start") 
		&& me->query_temp(QUESTDIR2+"pushdown") 
		&& !me->query(QUESTDIR2+"over"))
    {
		  message_vision(HIC"\n$N擠進暗室，發現一個中年男子，正炯炯有神地盯著你看，感覺不到一點被囚困的樣子。\n\n"NOR, me);                      
		  command("ah "+me->query("id"));
		  command("look "+me->query("id"));
		  command("heng");
		  command("say");
		  command("say 真乃人不可貌相，這魔僧看似一代高僧，卻妄為大輪明王。"); 
		  me->start_busy(1);
    }
}
string ask_name()
{
		set_name("段譽", ({ "duan yu", "duan","yu"}) );
		set("title",HIG"大理國鎮南王世子"NOR);
		set("long", HIG"雖身處暗室，卻依舊風採宜人，料想也是富貴子弟、世家豪傑。"NOR); 
		command("nod");
		return "在下便是段譽。";
}
int ask_home()
{
    object me,ob;
    ob=this_object();
	me=this_player();
	if(!me->query_condition("killer")
		&& me->query(QUESTDIR1+"start") 
		&& me->query_temp(QUESTDIR1+"see_duanyu2")
		&& !me->query_temp(QUESTDIR1+"gohome")
		&& !me->query_temp(QUESTDIR1+"see_duanyu1")
		&& !me->query(QUESTDIR1+"wuliangover")
		&& me->query_temp(QUESTDIR1+"jianying")
		&& ob->query("id")=="duan yu")
    {
		message_vision(HIY"\n$N輕輕道：“鎮南王正在王府心急成憂，閣下還是回去看看。”\n"NOR, me, this_object());
		command("oh");
		command("consider");
		me->start_busy(1);
		command("say");
		me->set_temp(QUESTDIR1+"gohome",1);
		call_out("outroom",6,me);
		return 1;
    } 
	command("consider");
	me->start_busy(1);
	command("say");
	command("say 我也想回去，只是.......");
	command("shout");
    return 1;
}
void outroom(object me)
{
  object ob=this_object();
  if(!me) return;
  if(!me->query(QUESTDIR1+"start")) return;
  if(!me->query_temp(QUESTDIR1+"gohome")) return;
  if(me->query_temp(QUESTDIR1+"see_duanyu1")) return;
  if(me->query(QUESTDIR1+"wuliangover")) return;

  if(environment(ob)!=environment(me)) 
  {
  	command("say 人呢？"+me->name()+"剛才不是還在嗎？");
	me->delete("quest/天龍八部/凌波微步篇");
  	command("say 我還是先回去了，爹爹和伯父一定著急了。");
  	command("sigh");
    me->set(QUESTDIR+"time",time());
 	me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
	destruct(ob);
  	return;
  }
  
  command("look "+me->query("id"));
 
  if(me->query("gender")=="女性")
  {
	  if(me->query("per")>26)
	  {
		  command("say 這位姐姐，竟然也這麼漂亮，真是有得和這玉像一拼，不過這玉像精工也太神色動人了。");
		  command("points");
		  tell_object(me,HIC"\n你側過身子看那玉像時，只見她眼光跟著轉將過來，便似活了一般。你大吃一驚，側頭向右，玉像的眼光似乎也對著你移動。不論\n"
			  "你站在那一邊，玉像的眼光始終向著你，眼光中的神色更是難以捉摸，似喜似愛，似是情意深摯，又似黯然神傷。\n"NOR);
		  tell_room(environment(me),HIC"轉頭卻見"+me->query("name")+"也是一復神色怪怪的樣子，也似乎被什麼吸引住了似的。\n"NOR, ({ me })); 
		  tell_object(me,HIC"\n你又向玉像呆望良久，這才轉頭，見東壁上刮磨平整，刻著數十行字，都是“莊子”中的句子，大都出自“逍遙遊”、“養生主”、\n"
			  "“秋水”、“至樂”幾篇，筆法飄逸，似以極強腕力用利器刻成，每一筆都深入石壁幾近半寸。文末題著一行字雲：“逍遙子為秋\n"
			  "水妹書。洞中無日月，人間至樂也。”！\n"NOR);
		  tell_object(me,HIR"\n過了一會，禁不住脫口而出：“真是天仙下凡啊，這等姿色，別說是男子見了，心神不定，就是我身為女兒身，也是神色恍惚。”\n"
			  HIY"\n你突然竟然有雙膝跪倒拜下去的沖動。 \n"NOR);
		  command("ah "+me->query("id"));
		  command("touch "+me->query("id"));	  
	  }
	  else
	  {
		  command("say "+me->query("name")+"，這位姐姐，你且仔細看看這玉像，真是太神色動人了。");
		  command("points");
		  tell_object(me,HIC"\n你側過身子看那玉像時，只見她眼光跟著轉將過來，便似活了一般。你大吃一驚，側頭向右，玉像的眼光似乎也對著你移動。不論\n"
			  "你站在那一邊，玉像的眼光始終向著你，眼光中的神色更是難以捉摸，似喜似愛，似是情意深摯，又似黯然神傷。\n"NOR);
		  tell_room(environment(me),HIC"轉頭卻見"+me->query("name")+"也是一復神色怪怪的樣子，也似乎被什麼吸引住了似的。\n"NOR, ({ me })); 
		  tell_object(me,HIC"\n你又向玉像呆望良久，這才轉頭，見東壁上刮磨平整，刻著數十行字，都是“莊子”中的句子，大都出自“逍遙遊”、“養生主”、\n"
			  "“秋水”、“至樂”幾篇，筆法飄逸，似以極強腕力用利器刻成，每一筆都深入石壁幾近半寸。文末題著一行字雲：“逍遙子為秋\n"
			  "水妹書。洞中無日月，人間至樂也。”！\n"NOR);
		  tell_object(me,HIR"\n過了一會，禁不住脫口而出：“真是天仙下凡啊，這等姿色，別說是男子見了，心神不定，就是我身為女兒身，看了真是自慚行愧啊。”\n"
			  HIY"\n你突然竟然有雙膝跪倒拜下去的沖動。 \n"NOR);
		  command("ah "+me->query("id"));
		  command("shrug "+me->query("id"));	  
	  }
  }
  else
  {
 	  command("say "+me->query("name")+"，也是同道中人，你且仔細看看這玉像，真是太神色動人了。");
	  command("points");
	  tell_object(me,HIC"\n你側過身子看那玉像時，只見她眼光跟著轉將過來，便似活了一般。你大吃一驚，側頭向右，玉像的眼光似乎也對著你移動。不論\n"
	  "你站在那一邊，玉像的眼光始終向著你，眼光中的神色更是難以捉摸，似喜似愛，似是情意深摯，又似黯然神傷。\n"NOR);
	  tell_room(environment(me),HIC"轉頭卻見"+me->query("name")+"也是一復神色怪怪的樣子，也似乎被什麼吸引住了似的。\n"NOR, ({ me })); 
	  tell_object(me,HIC"\n你又向玉像呆望良久，這才轉頭，見東壁上刮磨平整，刻著數十行字，都是“莊子”中的句子，大都出自“逍遙遊”、“養生主”、\n"
		  "“秋水”、“至樂”幾篇，筆法飄逸，似以極強腕力用利器刻成，每一筆都深入石壁幾近半寸。文末題著一行字雲：“逍遙子為秋\n"
		  "水妹書。洞中無日月，人間至樂也。”！\n"NOR);
      if(me->query("gender")=="無性") tell_object(me,HIR"\n你暗想：“我要是真能做個女人，就是死一千遍，一萬遍，也如身登極樂，歡喜無限。” \n"NOR);
	  tell_object(me,HIR"\n過了一會，禁不住脫口而出：“神仙姊姊，你若能活過來跟我說一句話，我便為你死一千遍，一萬遍，也如身登極樂，歡喜無限。”\n"
		  HIY"\n你突然竟然有雙膝跪倒拜下去的沖動。 \n"NOR);
	  command("ah "+me->query("id"));
	  command("touch "+me->query("id"));
  } 
  command("sigh");
  command("say 我還是先回去了，爹爹和伯父一定著急了。");
  command("chat* bye "+me->query("id"));	 
  command("wave "+me->query("id"));
  tell_room(environment(me),HIG"\n只見，段譽匆匆忙忙地離開，只是神色似乎很是留戀不舍。\n\n"NOR, ({}));
  me->set_temp(QUESTDIR1+"see_duanyu1",1);
  destruct(ob);
  return;
}


int ask_save()
{
    object me,ob,obj;
	int i, time;
    me=this_player();
    ob=this_object();
           
       //by Spiderii@ty 加入新標記,只為防止以前開lbwb的玩家可以連續fan bojuan
       time = time() - me->query("quest/天龍八部/武功/time");
       if ( me->query("quest/天龍八部/武功/time") && time < 86400 ) 
          {
		       message_vision("$N似乎不懂$n的意思。\n", ob,me);
	         return 1;
		 }


    if(ob->query("id")!="duan yu")
	{
		message_vision("$N似乎不懂$n的意思，道：$n要救誰，莫不是又來騙我的？。\n", ob, me);
		command("fear");
		return 1;
	}
	if (!me->query_condition("killer")
		&& me->query(QUESTDIR1+"start") 
		&& !me->query(QUESTDIR1+"over") 
		&& me->query_temp(QUESTDIR1+"kill_duan") 
		&& me->query(QUESTDIR1+"wuliangover"))
	{
		command("nod "+me->query("id"));
		message_vision(HIC"$N道：“今日相救無以回報，壯士是學武之人，我身上有卷帛卷，乃昔日\n"
			+"奇遇獲得，今日贈于你，略表解救之謝意。”說完，$N從懷裡摸出一團物事。\n"
			+"突然，$N大失驚色，“啊喲！怎麼會變成這個樣子？罷了！罷了！莫非天意？。”\n"
			+"拿去吧，能領會多少就看你的造化了。說完，$N把它交給$n。\n"NOR, ob, me);
		obj=new("/d/dali/obj/dodge_book");
              obj->set("owner", me->query("id"));//By Spiderii@ty 加個標記,防止BUG
              me->set("quest/天龍八部/武功/time", time()); //加個限制。禁止連續翻,只為防備以前開lbwb的玩家 By Spiderii@ty

		obj->move(me);
		//設定標志
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
		me->delete_temp("quest/天龍八部");
		me->set(QUESTDIR1+"over",1);//結束
		me->delete_temp("quest/busy");//任務沖突標志取消
		me->add_busy(4);
		i=10+random(10);
		me->add("max_neili",i);
		me->add("combat_exp",me->query_skill("force")+400);
		me->add("mana",me->query_skill("force")/3);
		command("thank "+me->query("id"));
		tell_object(me,HIY"\n你于"+NATURE_D->game_time()+"經過千辛萬苦終于段譽從萬劫谷解救出來，獲得"+i+"點最大內力、"+(me->query_skill("force")+400)+"點經驗和"+(int)me->query_skill("force")/3+"點聲望。\n\n");
		log_file("quest/TLBB", sprintf("%s(%s) 凌波微步篇完成。獎勵：%d點最大內力，%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), i,(me->query_skill("force")+400),me->query_skill("force")/3) );
		remove_call_out("dest");
		call_out("dest",5,me,ob);
		return 1;
	}
	if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"pushdown") && !me->query(QUESTDIR2+"over"))
	{
		command("say "+me->query("name")+"已經是第二次相救了，真的非常感激，我這裡正好有塊礦石，你且拿去。");
		obj=new("/d/zhiye/obj/kuangshi1");
		obj->set_level(5+random(3));
		obj->move(me);
		message_vision("$N給了$n一塊"+obj->query("name")+"。\n", ob, me);
    	command("chat* thank "+me->query("id"));
    	command("wave "+me->query("id"));
    	command("bye "+me->query("id"));
		//設定標志
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
		me->set(QUESTDIR2+"over",1);  //結束 	
		me->delete_temp("quest/天龍八部");
		me->delete_temp("quest/busy");//任務沖突標志取消
		i=10+random(10);
		me->add("max_neili",i);
		me->add("combat_exp",(me->query_skill("force")+500));
		me->add("mana",me->query_skill("force")/3);
		tell_object(me,HIY"\n你于"+NATURE_D->game_time()+"經過千辛萬苦終于段譽從天龍寺解救出來，獲得"+i+"點最大內力、"+((int)me->query_skill("force")+500)+"點經驗和"+(int)me->query_skill("force")/3+"點聲望。\n\n");
		log_file("quest/TLBB", sprintf("%s(%s) 天龍營救篇完成。獎勵：%d點最大內力，%d點經驗，%d點聲望和%s。\n", me->name(1),me->query("id"), i,(me->query_skill("force")+500),me->query_skill("force")/3,obj->query("name")) );
		destruct(this_object());
		return 1;
	}	
	if(random(2)) command("nod "+me->query("id"));
	else command("jump "+me->query("id"));
	return 1;
}

void dest(object me,object ob)
{
  if(!ob) return;
  if(!me || environment(ob)!=environment(me))
  {
	  destruct(ob);
	  return;
  }
  environment(ob)->set("exits/down","/d/dali/wuliang/midao1");
  message_vision(HIY"$n忽然看見角落裡泥土翻飛，有三個身穿貼身緊靠的人從地裡鑽了出來 \n"
		+"$n仔細一看，原來是大理國的華赫艮、巴天石和范驊。范驊上前向段譽 \n"
		+"鞠了個躬,道：“公子，我們來救你來了。”眼角一瞥，看見了$n，道：\n"
		+"“敢問這位台兄？”，段譽道：“這位台兄也是來救我的，他殺了四大惡人\n"
		+"從前面推開巨石而入。”范、巴、華等人聽了又驚又佩，，范驊道：“四。\n"
		+"大惡人黨羽眾多，恐怕還會有援兵來到，此地不宜久留，還是隨我從地道。\n"
		+"趕緊離開吧。”眾人點頭稱是，于是范、巴、華、段譽跳下地道離開了了\n"NOR, ob, me);
  destruct(ob);
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
  	  command("sigh "+me->query("id"));
		  return "真乃人不可貌相，這魔僧看似一代高僧，卻妄為大輪明王。";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "鳩摩智妄為西域第一佛法高僧，所謂口生蓮花，全是一派胡言。";
  }
  command("nod");
	return "大輪明王鳩摩智是吐蕃國的護國法王，但聽說他具大智慧，精通佛法，好想見識一下。";
}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("nod");
  		return "我大哥蕭峰如此英雄，何來援救之說。";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "聽說這件事情，哼，我既可前往大遼。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
		  return "蕭峰，難不是你所迫出中原，今日所謂搭救不知什麼意思。假惺惺！";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("heng");
		  return "聽說這件事情，哼，我既可前往大遼。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("heng");
		  return "聽說這件事情，哼，我既可前往大遼。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "這一戰真是痛快，"+me->query("name")+"更是威震武林，端得厲害啊。";
  }
  command("hoho");
	return "江湖人稱南慕容、北蕭峰，這蕭峰正是我大哥，如此英雄好漢，何來援救之說。";
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
		  return "多謝"+RANK_D->query_respect(me) +"救我回國。";
  }
  command("hoho");
	return "天龍寺是我段家武學的最高之地，高手眾雲，請不要危言聳聽。";
}

//hufei.c
//by tangfeng@SJ
//較量和胡家刀法的設定有些不好，重新修改，類似擂台比武，這樣避免死亡
//胡家刀法skills既然完成，武功部分重新設定
// Update By lsxk@hsbbs add通寶物品提高解quest機率 2007/7/20
// By Spideiri@ty 加入天賦系統
inherit F_MASTER;
inherit NPC;
//inherit FIGHTER;
#include <ansi.h>
//inherit F_SSERVER;

#define QUESTDIR "quest/雪山飛狐/"
#define QUESTDIR1 "quest/雪山飛狐/兩頁刀法篇/"
#define QUESTDIR2 "quest/雪山飛狐/復仇篇/"
#define QUESTDIR3 "quest/雪山飛狐/解藥篇/"
#define QUESTDIR4 "quest/雪山飛狐/武功/"

//int do_halt1(string arg);
void greeting(object me);
void unconcious();
void kill_ob(object me);
int do_hit(string arg);
void do_halt(object me);
void die();
int ask_biwu();
int ask_cheng();
int ask_yaowu();
int ask_hujiadaofa();
int ask_huyidao();
int ask_jiachou();
int ask_liangyedaofa();
int ask_zhiliao();
int ask_yanji();
int ask_miaoruolan();
int ask_tian();
int ask_miaorenfeng();
int ask_jiaoliang();
int hufei_fight(object me, object ob);
int thinking(object me, object ob);
int killing();
int start_condition(object ob);
int power_condition(object me,object ob,int p);
int busy_pass(object ob);

void create()
{
	set_name("胡斐", ({ "hu fei", "hu", "fei" }) );
	set("gender", "男性" );
	set("title", HIW"雪山飛狐"NOR);
	set("age", 26);
	set("long",
	    "遼東大俠胡一刀的兒子。\n"
	    "這人滿腮虯髯，根根如鐵，一頭濃髮，卻不結辮，橫生倒豎般有如亂草。"NOR);
	set("str", 25+random(30));
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
	set("unique", 1); //千萬別出問題阿，這個設定
    set(QUESTDIR4+"hujiadaofa",1);
    set(QUESTDIR4+"lengquanshengong_teach",1);
	set_skill("force", 300);
    set("no_get", 1);
    set("no_bark", 1);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("blade", 300);
	set_skill("cuff",300);
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
  set_skill("lengquan-shengong",300);
	set_skill("hujia-daofa",300);
	map_skill("force","lengquan-shengong");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
	map_skill("blade","hujia-daofa");
	map_skill("parry","hujia-daofa");
	set("double_attack",1);
    prepare_skill("cuff", "zhentian-quan");
	set("combat_exp", 2000000);
	set("max_qi", 30000);
	set("max_jing", 30000);
	set("max_neili", 5000);
	set("eff_jingli",30000);
	set("qi",30000);
	set("jing",30000);
	set("jingli",30000);
	set("neili", 5000);
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
       (: exert_function, "lengquan" :),
       (: perform_action, "blade.feidao" :),
       (: perform_action, "blade.luandao" :)
     }));
    set("inquiry", ([
    "胡一刀" : (: ask_huyidao :),
    "hu yidao" : (: ask_huyidao :),
    "胡家刀法" : (: ask_hujiadaofa :),
    "hujia-daofa" : (: ask_hujiadaofa :),
    "兩頁刀法" : (: ask_liangyedaofa :),
    "較量" : (: ask_jiaoliang :),
    "切磋" : (: ask_jiaoliang :),
    "比武" : (: ask_biwu :),
    "20年前" : (: ask_biwu :),
    "比試" : (: ask_biwu :),
    "決鬥" : (: ask_biwu :),
    "治療" : (: ask_zhiliao :),
    "解藥" : (: ask_zhiliao :),
    "苗若蘭" : (: ask_miaoruolan :),
    "苗人鳳" : (: ask_miaorenfeng :),
    "閻基" : (: ask_yanji :),
    "程靈素" : (: ask_cheng :),
    "田歸農" : (: ask_tian :),
    "天龍門" : (: ask_tian :),
    "家仇" : (: ask_jiachou :),
     "報仇" : (: ask_jiachou :),
    "仇恨" : (: ask_jiachou :),
    "復仇" : (: ask_jiachou :),
	]));
	setup();
	set("chat_chance", 1);
	set("chat_msg", ({
		"胡斐跪在墳前拜了又拜。\n",
	}));
	carry_object("/clone/weapon/blade/blade.c")->wield();
	carry_object("/clone/weapon/blade/blade.c");
	carry_object("/clone/armor/baihu-qiu.c")->wear();
}

void init()
{
  object ob;
	::init();
  ob = this_player();
  if (!this_object()->query_temp("biwu")&& interactive(ob = this_player()) ) {
       remove_call_out("greeting");
       call_out("greeting", 2, ob);
  }
  add_action("do_answer","answer");
  add_action("do_hit", "hit");
}

void greeting(object me)
{
  int shen,i;
  if(!me) return;
  if(environment(me)!=environment(this_object())) return;
  shen = me->query("shen");
  if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"over")&&!me->query(QUESTDIR2+"over"))
  {
	me->start_busy(1);
	tell_object(me,CYN"\n你急忙在胡斐的耳邊悄聲地將真相告訴胡斐，胡斐聞言更是泣不成聲....\n\n"NOR);
    tell_room(environment(me),HIC"\n只見"+me->query("name")+"急步趕來，在胡斐的耳邊悄聲地説着什麼。\n\n"NOR, ({ me }));
  	command("chat* cry");
	tell_room(environment(me),HIC"\n胡斐突然大哭起來，悲叫道：“田歸農！”，似乎有不解之仇。"NOR, ({}));
    tell_object(me,HIW"\n“田歸農！”只是這段殺父之仇，因為天龍門的消飛雲散，這段恩怨也只能不了了之。\n"NOR);
  	tell_object(me,HIG"你不知道是喜是悲，想想這個結果對胡斐來説也許也是個了結。\n\n"NOR);
  	command("whisper "+me->query("id")+" 苗大俠，不知道毒發如何？");
  	tell_object(me,HIC"你點頭道：我馬上去苗家莊，你心情不定，還是先歇息為妙。\n"NOR);
	tell_room(environment(me),HIC""+me->query("name")+"向胡斐點了點頭，神色很是着急。\n"NOR, ({}));
    //設定標記
    me->set(QUESTDIR2+"over",1);
    me->delete_temp(QUESTDIR2+"over");
    me->set(QUESTDIR+"time",time());
    me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
    //獎勵
    me->add("combat_exp",me->query_skill("force")*3/2);
   	i=180+random(40);
   	me->add("mana",i);
    tell_object(me,YEL"\n你於"+NATURE_D->game_time()+"解開雪山飛狐復仇篇，獲得"+(int)me->query_skill("force")*3/2+"點經驗獎勵、"+i+"點聲望。\n"NOR);
    log_file("quest/FEIHU", sprintf("%s(%s) 復仇篇完成。獎勵：%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), me->query_skill("force")*3/2,i ) );
	}
	else
	{
	  if(shen <0 ) command("look "+me->query("id"));
	  else command("say");
  }
}

int ask_cheng()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
  	message_vision(YEL"$N臉上露出懷念之情。\n"NOR,this_object());
	  command("say 真的感謝程姑娘，要不是她恐怕我抱憾終生。");
	  command("think");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"getjieyao"))
  {
  	message_vision(YEL"$N臉上露出懷念之情。\n"NOR,this_object());
	  command("suicide1");
	  command("say 真的感謝程姑娘，我們還是趕快去救治苗大俠吧。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& (me->query_temp(QUESTDIR3+"jieyao2")||me->query_temp(QUESTDIR3+"qixinghaitang")))
  {
  	message_vision(YEL"$N臉上露出懷念之情。\n"NOR,this_object());
	  command("suicide1");
	  command("say 我們快點趕到程姑娘那裏，苗大俠的毒如此兇猛，只怕......");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao1"))
  {
	  command("sigh");
	  command("say 我們快點去找到七星海棠。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start"))
  {
    message_vision(YEL"$N臉上露出懷念之情。\n"NOR,this_object());
	  command("blush");
	  command("say 程姑娘當年我與她有過一面之交，只是現在身在何處，不很清楚......");
	  command("sigh");
	  return 1;
  }
  message_vision(YEL"$N臉上露出懷念之情。\n"NOR,this_object());
  command("say 你也認識程姑娘，這些年來，其實我一直在找她。");
	command("sigh");
	return 1;
}

int ask_biwu()
{
	object me = this_player();
  if(me->query(QUESTDIR3+"marry"))
  {
	  command("say 20年前的比武，現在已經完全明瞭，胡苗兩家今天能夠再次重歸於好，多虧大俠幫忙。");
  	command("thank "+me->query("id"));
	  command("say 還要多謝大俠能夠撮合在下與苗姑娘的婚姻。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 20年前的比武，現在已經完全明瞭。苗大俠如此正氣，我竟然懷疑他，還好毒也解了，沒能鑄成大錯。");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 確實沒有想到事情如此複雜。恨我自己，苗大俠如此正氣，我竟然懷疑他，這毒如此兇猛，只怕......");
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("shout");
	  command("say 20年前的比武，的確還有疑點，但是既然知道殺害我爹的兇手，就算我這身武功不濟，也決不苟生。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"start"))
  {
	  command("say 20年前的比武，知道真相的人都不復人世，這些年來我一直在尋找殺害爹媽的兇手。");
	  command("shout");
	  command("say 而且，可惜我武功未能圓通，不能為報父仇，這胡家刀法總是不能返璞歸真。");
	  return 1;
  }
  message_vision(YEL"$N臉上露出不解之情。\n"NOR,this_object());
	command("say 當年我爹爹和號稱“打遍天下無敵手”的苗人鳳在此比武，苗人鳳以毒刀\n將我爹爹害死，我娘自刎殉夫。待我遇見那殺父仇人，定將他碎屍萬斷......不過，\n"
          "他二人豪氣相侔，相敬相重，苗人鳳怎麼會下如此黑手？");
	command("consider");
	return 1;
}

int ask_hujiadaofa()
{
	object me = this_player();
	object ob = this_object();
	int i,lv;
	if(me->query_condition("killer"))
	 {
	   command("fear "+me->query("id"));
     command("say 小心官府通緝！");
	   return 1;
   }
    if(!me->query(QUESTDIR4+"hujiadaofa") && me->query("combat_exp")<= 2000000)
   {
     command("@@ "+me->query("id"));
     command("say 以你當前的經驗恐怕還是難以領悟，還是抓緊去練功去吧。");
     return 1;
   }
	if(me->query(QUESTDIR2+"start") && !me->query(QUESTDIR3+"over"))
  {
	  command("shake "+me->query("id"));
	  command("say 現在時間緊急，這刀法還是以後切磋吧。");
	  return 1;
  }

  if(me->query(QUESTDIR4+"hujiadaofa"))
  {
   if(me->query("potential")<= 5)
   {
	  command("kick "+me->query("id"));
	  if(random(2)) command("say 胡什麼刀，什麼法啊？");
	  else command("say 潛能不夠學什麼刀法！");
    return 1;
   }
   else
   {
    message_vision("$N向$n請教有關胡家刀法的奧妙。\n", me, this_object());
    me->receive_damage("jing", 30);
    tell_object(me,"你聽了胡斐的指點，對胡家刀法的奧妙似乎有些心得。\n");
    me->add("potential",-(random(3)+2));
    if( me->query("potential")<0)
        me->set("potential",0);
    me->improve_skill("hujia-daofa", 150+random(me->query_int()*2));
    me->improve_skill("blade", random(me->query_int())/2);
    //天賦“領悟大師”影響效果：  by spiderii@ty ..lsxk想法太過變態了
        lv = me->query("max_pot")-100;
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你經過轉世重修後，領悟到了武技萬變不離其宗的道理，瞬間領悟到了胡家刀法的精華所在。\n"NOR);
            me->set_skill("hujia-daofa",lv);
            }

    return 1;
   }
  }
  //600sec招待一次玩家
  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 有些累了，這刀法還是以後切磋吧。");
	  return 1;
  }
  //非vip玩家，只能失敗三次
  if(me->query(QUESTDIR4+"hujiadaofa_fail")>=3 && me->query("registered")<3)
  {
	  command("shake "+me->query("id"));
	  command("say 現在時間緊急，這刀法還是以後切磋吧。");
	  return 1;
	}
	//武功學習之間需要間隔一天，經驗需要間隔1M
	//注意這個標記和苗家劍法使用同一個標記。
	if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<86400)
	{
	  command("shake "+me->query("id"));
	  command("say 今天先切磋到這裏吧，明天吧。");
	  return 1;
  }
   if(me->query(QUESTDIR4+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"combat_exp")<500000 &&!me->query("cw_exp"))
	{
	  command("look "+me->query("id"));
	  command("say 以你當前的經驗恐怕還是難以領悟，還是抓緊去練功去吧。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	command("nod "+me->query("id"));
    message_vision(HIB"\n$n突然運起獨門內功冷泉神功，只感覺刀勢無風自起。\n"NOR, me, ob);
    //胡斐忙碌
    ob->set_temp("busy",1);
    remove_call_out("busy_pass");
	call_out("busy_pass",600, ob);
    power_condition(me,ob,300+random(100));
	  for ( i = 0; i < 6+random(6);i++)
	  {
         if (!present(me,environment(ob)) || me->query("qi") <= me->query("max_qi")/20 ||me->query("eff_qi") <= me->query("max_qi")/20 || me->query("jing") <= 50 || me->query("jingli") <= 50)
         {
            if(random(2))command("sneer");
            else if(random(2)) command("say 這位"+RANK_D->query_respect(me) +"武功未能返璞歸真，只怕難以領悟胡家刀法的絕技！");
         	  me->reincarnate();
            return 1;
         }
         else
         {
            if(random(2)) command("sneer "+me->query("id"));
            else command("say 小心了，還有一招。");
            ob->delete_temp("quest/雪山飛狐/武功/lengquan");
            COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            ob->set_temp("quest/雪山飛狐/武功/lengquan",1);
          }
    }
    ob->delete_temp("quest/雪山飛狐/武功/lengquan");
    start_condition(ob);
    command("smile "+me->query("id"));
    message_vision(HIC"\n\n猶如電光雷閃，一晃數招已過，$n微笑着對$N説道：「剛才我使用的招數可看清楚了？」\n"NOR,me,ob);
    //標記時間和經驗
    me->set(QUESTDIR4+"time",time());
    me->set(QUESTDIR4+"combat_exp",me->query("combat_exp"));
    tell_object(me,YEL"你拼命地回憶瞬間交手的一幕，回憶着剛才的招數，你開始認真思索着.........\n"NOR);
    remove_call_out("thinking");
		call_out("thinking",0, me, ob);
    me->start_busy(1);
	  return 1;
  }
  if(me->query(QUESTDIR1+"start"))
  {
	  command("shout");
	  if(random(2)) command("say 可惜我武功未能圓通，不能為報父仇，這胡家刀法總是不能返璞歸真。");
	  else command("say 苗人鳳聽説武功號稱打遍天下，自是厲害，可惜我胡家刀法祕籍竟有殘缺，因此在下武功終未大成。");
	  return 1;
  }
  if(me->query_temp(QUESTDIR1+"jiachou"))
  {
 	  command("heng");
	  command("say 我胡家刀法確是一等一的武功，只是爹爹留給我祕籍竟然缺了兩頁，缺了紮根基的入門功夫，缺了拳法刀法的總訣。");
	  command("say 這些年來，無論怎麼用功，總是難以融會貫通，聽説苗人鳳號稱打遍天下無敵手，可惜我胡家刀法祕籍竟有殘缺，不是對手。");
 	  command("sigh");
    command("say 我聽平四叔説，這兩頁好像被一個江湖郎中奪去，前一段時間有人説在苗疆看到他。");
    me->set(QUESTDIR1+"start",1);
    me->delete_temp(QUESTDIR1+"jiachou");
	  return 1;
  }
	command("sneer");
	if(random(2)) command("say 想和我比試？看好了！");
  power_condition(me,ob,250+random(200));
  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  if(random(2)) COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  if(random(2)) COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  start_condition(ob);
	command("sneer");
	return 1;
}

int busy_pass(object ob)
{
	if(!ob) return 0;
	if(ob->query_temp("busy")) ob->delete_temp("busy");
	if(ob->query("busy")) ob->delete("busy");
   remove_call_out("busy_pass");
  message_vision(HIC"\n$N伸了伸懶腰。\n"NOR,ob);
  return 1;
}

int thinking(object me, object ob)
{
	int i,p;
	if(!me) return 0;
  if(environment(me)!=environment(this_object()))
  {
  	start_condition(ob);
    if(random(2)) message_vision(HIC"\n$N伸了伸懶腰，道：$n竟然臨陣逃脱，沒料得蠢材一個。\n"NOR,ob,me);
    else message_vision(HIC"\n$N疑惑問道：夷~~~人呢？$n，人呢？\n"NOR,ob,me);
  	return 1;
  }

  if(me->query_temp(QUESTDIR4+"thinking")<(3+random(3)))
	{
		me->add_temp(QUESTDIR4+"thinking",1);
    if(random(2)) tell_object(me,HIG"\n你努力地回憶剛才的每一招每一式，似有無數人影交相互動，每一招每一式你都努力去看清楚...\n"NOR);
    else tell_object(me,HIY"\n突然間，你似乎抓到了什麼，你努力地回憶剛才的每一招每一式，你能充分感覺招數的凌厲和急速...\n"NOR);
          tell_room(environment(me),HIC""+me->query("name")+HIC"似乎在思索着什麼，一服愁眉不展的樣子。\n"NOR, ({}));
	  remove_call_out("thinking");
		call_out("thinking",4+random(3), me, ob);
	}
	else
	{
	  //難度降低，畢竟單純的胡家刀法威力一般
    //如果有特殊通寶物品，略微提高成功機率。  by lsxk@hsbbs 2007/7/20
      if(me->query_temp("sj_credit/quest/public/hjdf"))
          p=random(me->query("kar")+10);
      else
		p=random(me->query("kar"));
      me->delete_temp("sj_credit/quest/public/hjdf");
          if(p> 27 && me->query("kar")<31 && QUEST_D->questing(me,1,0,1))
      {
       tell_object(me,HIG"\n你明悟其中，突然間明白了一切。\n"NOR);
       message_vision(HIC"\n$N「哈哈哈」大笑幾聲，説道：“原來如此，原來如此。”\n"NOR,me);
       command("ah");
       command("congra "+me->query("id"));
       command("chat* congra "+me->query("id"));
       tell_object(me,HIR"你聽了胡斐的指點，對胡家刀法的奧妙似乎有些心得。\n"NOR);
       tell_object(me,HIR"只是你發現這胡家刀法還需要冷泉神功才能發揮全效。\n"NOR);
       me->set(QUESTDIR4+"hujiadaofa",1);
       me->delete_temp(QUESTDIR4+"thinking");
   	   i=180+random(40);
   	   me->add("mana",i);
  	   tell_object(me,HBYEL"\n你於"+NATURE_D->game_time()+"解開雪山飛狐胡家刀法篇，並獲得"+i+"點聲望。\n\n"NOR);
       log_file("quest/FEIHU", sprintf(HIR"%s(%s) 失敗%d次後揭開胡家刀法，獲得%d點聲望。富源：%d;隨機取值：%d。\n"NOR, me->name(1),me->query("id"),me->query(QUESTDIR4+"hujiadaofa_fail"), i,me->query("kar"),p ) );
    }
    else
    {
       tell_object(me,HIG"\n你腦海裏似乎抓住了什麼，可是依然不是很明白。\n"NOR);
       command("poor "+me->query("id"));
       message_vision(HIC"\n$N搖了搖頭，道：“好像還是很困難的。”説罷，深深地歎了口氣。\n"NOR,me);
	   me->add(QUESTDIR4+"hujiadaofa_fail",1);
	   log_file("quest/FEIHU", sprintf(HIR"%s(%s) 胡家刀法失敗次數：%d次,富源：%d；隨機取值%d。\n"NOR, me->name(1),me->query("id"),me->query(QUESTDIR4+"hujiadaofa_fail"),me->query("kar"),p) );
       if(me->query(QUESTDIR4+"hujiadaofa_fail")>=3 && me->query("registered")<3)
       {
      	tell_object(me,HBYEL"\n很遺憾你於"+NATURE_D->game_time()+"最後一次嘗試揭開雪山飛狐胡家刀法，卻沒有成功。\n\n"NOR);
        log_file("quest/FEIHU", sprintf("%s(%s) 最後一次嘗試揭開雪山飛狐胡家刀法，卻沒有成功。經驗 %d。\n", me->name(1),me->query("id"), me->query("combat_exp") ) );
       }
    }
    me->delete_temp(QUESTDIR4+"thinking");
  }
  return 1;
}

int ask_huyidao()
{
	object me = this_player();
  if(me->query(QUESTDIR2+"over"))
  {
  	command("nod "+me->query("id"));
  	command("say 不錯不錯，當年的關東大俠胡一刀正是我父親！");
   	message_vision(HIB"$N説完這句話，滿臉盡是得意之色！\n"NOR,this_object());
	  return 1;
  }
  if(me->query(QUESTDIR2+"start"))
  {
  	command("heng");
  	command("say 當年的關東大俠胡一刀正是我父親！");
  	command("say 爹爹的死我這就去找苗人鳳算賬去！");
  	return 1;
  }
  command("nod "+me->query("id"));
  command("say 當年的關東大俠胡一刀正是我父親！");
  command("say 可惜爹爹的仇，還未報！");
	return 1;
}

int ask_jiachou()
{
	object me = this_player();
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
     command("say 小心官府通緝！");
	   return 1;
	}
  if(me->query(QUESTDIR3+"marry"))
  {
	  command("say 家仇已了，胡苗兩家今天能夠再次重歸於好，也多虧大俠幫忙。");
  	command("thank "+me->query("id"));
	  command("say 還要多謝大俠能夠撮合在下與苗姑娘的婚姻。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"over"))
  {
	  command("say 胡苗兩家今天能夠再次重歸於好，也多虧大俠幫忙。苗大俠如此正氣，我竟然懷疑他，還好毒也解了，沒能鑄成大錯。");
	  command("sigh "+me->query("id"));
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 確實沒有想到事情如此複雜。恨我自己，苗大俠如此正氣，我竟然懷疑他，這毒如此兇猛，只怕......");
	  return 1;
  }

  if(me->query(QUESTDIR2+"start"))
  {
	  command("say 所謂父仇不共戴天，既然知道殺害我爹的兇手，就算我這身武功不濟，也決不苟生。");
	  if(!me->query_temp(QUESTDIR2+"answer")){
		  //詢問家仇是涉及quest的第一二步，增加時間間隔半天，經驗需要間隔500K
		  if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<43200)
		  {
			  command("cry "+me->query("id"));
			  command("say 不過，今天已經很麻煩了"+me->query("name")+"了，復仇的事情也不急在一時。");
			  return 1;
		  }
                  if(me->query(QUESTDIR+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000 && !me->query("cw_exp"))
		  {
			  command("look "+me->query("id"));
			  command("say 不過，以你當前的經驗恐怕還是難以有所幫助，還是抓緊去練功去吧。");
			  return 1;
		  }
		  if(me->query(QUESTDIR4+"win_hu") || me->query(QUESTDIR4+"fight_hu")>=3)
		  {
			  command("look "+me->query("id"));
			  command("sigh");
			  if(!me->query(QUESTDIR4+"win_hu"))
				  command("whisper "+me->query("id")+" 這位"+RANK_D->query_respect(me) +"武功也算不錯，不知道是否願意幫忙？");
			  else command("whisper "+me->query("id")+" 這位"+RANK_D->query_respect(me) +"，武功超絕，不知道是否願意幫忙？");
			  me->set(QUESTDIR+"time",time());
			  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
			  command("addoil "+me->query("id"));
			  tell_object(me,HIG"回答命令answer yes 或者answer no\n"NOR);
			  me->set_temp(QUESTDIR2+"answer_",1);
			  log_file("quest/FEIHU", sprintf("%s(%s) 決定進入苗家莊。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
			  return 1;
		  }
		  else
		  {
			  command("look "+me->query("id"));
			  command("say 你連我都不是對手，如何幫我復仇？");
			  return 1;
		  }
	  }
	  else
	  {
		  command("look "+me->query("id"));
		  command("thank "+me->query("id"));
		  command("say 只要這位"+RANK_D->query_respect(me) +"能夠幫忙，在下不勝感激。其實我也不能確認這事情原委。");
	  }
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {

	  command("say 我一直懷疑他就是殺害我爹的兇手，只是苗家素有俠名，所以不敢確認，如今真相大白。");
	  command("say 所謂父仇不共戴天，既然知道殺害我爹的兇手，就算我這身武功不濟，也決不敢偷生了。");
	  command("sigh");
	    //詢問家仇是涉及quest的第一二步，增加時間間隔半天，經驗需要間隔500K
       if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<43200)
	   {
		   command("cry "+me->query("id"));
		   command("say 不過，今天已經很麻煩了"+me->query("name")+"了，復仇的事情也不急在一時。");
		   return 1;
	   }
           if(me->query(QUESTDIR+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000 && !me->query("cw_exp"))
	   {
		   command("look "+me->query("id"));
		   command("say 不過，以你當前的經驗恐怕還是難以有所幫助，還是抓緊去練功去吧。");
		   return 1;
	   }
        //必須勝過hu,或者比試三場之後
	   if(me->query(QUESTDIR4+"win_hu") || me->query(QUESTDIR4+"fight_hu")>=3)
       {
   		   command("look "+me->query("id"));
		   command("sigh");
		   if(!me->query(QUESTDIR4+"win_hu"))
			   command("whisper "+me->query("id")+" 這位"+RANK_D->query_respect(me) +"武功也算不錯，不知道是否願意幫忙？");
		   else command("whisper "+me->query("id")+" 這位"+RANK_D->query_respect(me) +"，武功超絕，不知道是否願意幫忙？");
		   me->set(QUESTDIR+"time",time());
		   me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));

		   tell_object(me,HIG"回答命令answer yes 或者answer no\n"NOR);
		   command("addoil "+me->query("id"));
		   me->set_temp(QUESTDIR2+"answer_",1);
		   me->set(QUESTDIR2+"start",1);//?? 怎麼有玩家沒有成功??
		   log_file("quest/FEIHU", sprintf("%s(%s) 決定進入苗家莊。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
		   return 1;
	   }
	   else
	   {
		   command("look "+me->query("id"));
		   command("say 你連我都不是對手，如何幫我復仇？");
		   return 1;
	   }
  }
  if(me->query(QUESTDIR1+"start"))
  {
	  command("shout");
	  command("say 我一直懷疑苗人鳳就是殺害我爹的兇手，只是他素有俠名，所以不敢確認。");
	  return 1;
  }
  if(me->query_temp(QUESTDIR1+"jiachou"))
  {
    message_vision(YEL"$N臉上露出不解之情。\n"NOR,this_object());
	  command("consider");
	  command("say 我真的不明白，想不通這其中的變化，只可惜我爹媽死得不明不白。");
	  return 1;
  }

  message_vision(YEL"$N臉上露出不解之情。\n"NOR,this_object());
	command("say 當年我爹爹和號稱“打遍天下無敵手”的苗人鳳在此比武，苗人鳳以毒刀\n"
"  將我爹爹害死，我娘自刎殉夫。待我遇見那殺父仇人，定將他碎屍萬斷......不過，\n"
"  他二人豪氣相侔，相敬相重，苗人鳳怎麼會下如此黑手？");
	command("consider");
	me->set_temp(QUESTDIR1+"jiachou",1);
  me->set(QUESTDIR+"time",time());
  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
	return 1;
}

int do_answer(string arg)
{
	object me = this_player();
	if(!me->query_temp(QUESTDIR2+"answer_")) return 0;
	if(!arg ||(arg!="yes" && arg!="no")) return 0;
	if(arg=="yes")
	{
    tell_object(me,CYN"\n你深深地歎了口氣，説道：恩，這段公案也應該有個水落石出！我就幫你去一次苗家莊吧。\n"NOR);
	  me->set_temp(QUESTDIR2+"answer",1);
	}
	else
	{
    tell_object(me,CYN"\n你驚異地説道：我卻有些懷疑，苗大俠怎麼可能是兇手呢！不是算為你，我也要去一次苗家莊吧！\n"NOR);
	  me->set_temp(QUESTDIR2+"answer",1);
	}
	return 1;
}

int ask_jiaoliang()
{
	object me = this_player();
	object ob = this_object();
	object room;
	mapping mp;
	int i;
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
     command("say 小心官府通緝！");
	   return 1;
	}
  if( mapp(mp = me->query_conditions_by_type("poison")) && sizeof(mp)>0 )
	{
	   command("poor "+me->query("id"));
     command("say 你還是先治好你的病再來切磋吧！");
	   return 1;
	}
  if( mapp(mp = me->query_conditions_by_type("killer")) && sizeof(mp)>0 )
	{
	   command("sigh "+me->query("id"));
     command("say 你還是先解決了你的個人恩怨再來切磋吧！");
	   return 1;
	}
  if(!me->query(QUESTDIR3+"over") && me->query(QUESTDIR2+"start"))
  {
	  command("shake "+me->query("id"));
	  command("say 現在時間緊急，還是先治療苗大俠要緊。");
	  return 1;
  }
  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 剛切磋完，以後切磋吧。");
	  return 1;
  }
  //普通玩家三次,
   if(me->query(QUESTDIR4+"fight_hu")>=3 && me->query("registered")<3)
  {
	  command("shrug "+me->query("id"));
	  command("say 天色不早了，這刀法還是以後切磋吧。");
	  return 1;
	}

	//較量增加時間間隔3個小時。
  if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<(3600*3))
	{
	  command("shake "+me->query("id"));
	  command("say 今天先切磋到這裏吧，稍後吧。");
	  return 1;
  }
        if((me->query(QUESTDIR4+"fight_hu")>=3 && me->query(QUESTDIR4+"fight_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"fight_exp")<500000 && !me->query("cw_exp"))
                ||(me->query(QUESTDIR4+"fight_hu")<3 &&me->query(QUESTDIR4+"fight_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"fight_exp")<100000)&& !me->query("cw_exp"))
	{
		command("shake "+me->query("id"));
		command("say 你武功沒什麼大的變化，還是抓緊練武去吧。");
		return 1;
	}
  //經驗太差的直接讓他昏倒，嘿嘿
  if(random(me->query("combat_exp"))<random(ob->query("combat_exp")/2) && !wizardp(me))
  {
	  for ( i = 0; i < 1+random(3);i++)
	  {
	     COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
    }
    return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("nod "+me->query("id"));
    message_vision(HIY"\n$n突然運起獨門內功冷泉神功，只感覺刀勢無風自起。\n"NOR, me, this_object());
    //玩家最好武功在400等級以上，縱然如此還是比較危險。
    power_condition(me,ob,300+random(100));
    //胡斐和玩家將進入另外一個房間
    if (!(room = find_object("/d/huanghe/lianwuchang")))
       room = load_object("/d/huanghe/lianwuchang");
    if( !room )
 	  {
	     command("shake "+me->query("id"));
	     command("say 暫時沒有空餘的場地較量，稍後吧，或者通知巫師一下。");
	     return 1;
    }
    if(room->query_temp("biwu"))
 	  {
	     command("shake "+me->query("id"));
	     command("say 暫時沒有空餘的場地較量，稍後吧，或者通知巫師一下。");
	     return 1;
    }
    //標誌
    me->set(QUESTDIR4+"time",time());
	me->set(QUESTDIR4+"fight_exp",me->query("combat_exp"));
    me->set_temp(QUESTDIR4+"fight_id",ob->query("id"));
    me->add(QUESTDIR4+"fight_hu",1);
    ob->set_temp("busy",1);
    ob->set_temp("biwu",1);
	  ob->set_temp("quest/try_fight_id",me->query("id"));

    message_vision(HIY"$N向$n一招手道：“且隨我來”，$N和$n急急忙忙地離開墳地。\n"NOR, ob,me);
    ob->move(room);
    me->move(room);
    message_vision(YEL"$N急急忙忙地來到練武場。\n"NOR, ob);
    message_vision(YEL"$N急急忙忙地來到練武場。\n"NOR, me);
	  command("sneer");
    remove_call_out("busy_pass");
		call_out("busy_pass",600, ob);
    me->start_busy(1);
    ob->start_busy(1);
  log_file("quest/FEIHU", sprintf("%s(%s) 決定再次和胡斐較量。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	  return 1;
  }
	command("say 想和我比試？看好了！");
  power_condition(me,ob,250+random(200));
	for ( i = 0; i < 2+random(3);i++)
	{
	     COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  }
	command("sneer");
	start_condition(ob);
	return 1;
}

int ask_liangyedaofa()
{
	object me = this_player();
  if(me->query(QUESTDIR1+"over"))
  {
  	command("thank "+me->query("id"));
	  command("say 感謝"+RANK_D->query_respect(me) +"幫我找到這兩頁刀法，我才能將胡家刀法融會貫通。");
	  return 1;
  }
	command("?");
  command("say 兩頁刀法？不是很明白。");
	return 1;
}
int ask_yanji()
{

	object me = this_player();
  if(me->query(QUESTDIR2+"over"))
  {
	  command("say 一切都結束了，也多虧他告訴我這一切恩恩怨怨。");
	  command("zxx2 "+me->query("id"));
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("heng");
	  command("say 這小人竟然乘亂偷走我家祕籍，待我見到必不可饒！");
	  return 1;
  }
 	command("?");
	command("say 我好像不認識這個人。");
	command("consider");
	return 1;
}
int ask_zhiliao()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("?");
	  command("say 我不是醫生，呵呵，問我什麼治療？ ");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start"))
  {
	  command("sigh "+me->query("id"));
	  command("say 治療苗大俠恐怕只有程姑娘了，好歹也讓求她了，只是不知道現在程姑娘人在哪裏。");
	  return 1;
  }
  command("?");
	command("say 我不是醫生，呵呵，問我什麼治療？");
	return 1;
}
int ask_miaoruolan()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"marry"))
  {
  	command("blush");
  	command("thank "+me->query("id"));
	  command("say 小蘭最近很好。還要多謝大俠能夠撮合在下與苗姑娘的婚姻。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"over"))
  {
	  command("say .............");
	  command("blush "+me->query("id"));
	  return 1;
  }
	command("say .............");
	command("blush "+me->query("id"));
	if(random(2)) command("zxx2");
	else command("sigh");
	return 1;
}
int ask_miaorenfeng()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
  	command("thank "+me->query("id"));
	  command("say 苗大俠最近很好。還要多謝大俠能夠化解苗胡兩家的恩怨。");
  	command("thank "+me->query("id"));
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("blush "+me->query("id"));
	  command("say 果真一代大俠，可惜之前我一直冤枉了他。");
	  return 1;
  }
	command("say .............");
	command("consider");
	command("say 我不明白苗大俠與我爹爹如此交好，為何使出如此毒手，而他平常為人卻有光明磊落！");
	return 1;
}
int ask_tian()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 天龍門現在一門盡亡，也算是天網恢恢阿。");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("heng");
	  command("say 確實沒有想到事情如此複雜。不知道這天龍門現在還有餘人......");
    message_vision(HIC"$N緩緩地搖了搖頭，歎氣道：恩恩怨怨何時了。\n"NOR, me);
	  return 1;
  }
	command("say 聽説是上任天龍門掌門，很久不知下落了。現在天龍門大不如以前了。");
	return 1;
}

int accept_object(object who, object ob,object me)
{
	if(who->query_condition("killer"))
	{
	   command("shake "+who->query("id"));
     command("say 你目前被官府通緝，我如何敢受"+ob->name()+"！");
	   return 0;
	 }
	 if(ob->query("id")=="liangye daofa")
   {
   	 command("ah "+(string)who->query("id"));
     if(who->query_temp(QUESTDIR1+"liangye") && who->query(QUESTDIR1+"start"))
     {
     	command("jump "+(string)who->query("id"));
      tell_object(who,HIC"\n你把兩頁刀法將給胡斐。胡斐仔細地看了兩遍，不由驚叫起來，“正是這兩頁刀法，不是大俠何處得來？”\n"NOR);
      tell_object(who,HIC"你簡單説了一下你去苗疆；卻見胡斐傻傻地盯着這兩頁刀法，不由自主地演練起來，全然忘記你的存在。\n"NOR);
	    tell_room(environment(who),HIC"\n胡斐似乎從"+who->query("name")+"拿到一本武功祕籍，竟然當場演練起來。\n"NOR, ({ who }));
     	who->start_busy(1);
      remove_call_out("telltruth");
      call_out("telltruth",6, who);
     }
     else  command("thank "+(string)who->query("id"));
     call_out("destroying", 1, ob);
     return 1;
   }
    else
   {
     command("? "+(string)who->query("id"));
     return 0;
   }
}
void destroying(object obj)
{
        if(!userp(obj)) destruct(obj);
        return;
}
void telltruth(object me)
{
	    int i;
	    if(!me) return;
	    if(environment(me)!=environment(this_object()))
	    {
   	    message_vision(HIB"\n$n突然抬起頭來，疑惑問道：“$N已經走了？我還沒有好好感謝呢。”\n"NOR, me, this_object());
	    	return;
	    }
      if(!me->query_temp(QUESTDIR1+"liangye")) return;
     	command("haha");
     	command("say 不錯就是它，正是我胡家刀法無法圓通的缺陷所在！");
     	tell_object(me,YEL"\n你看胡斐練得差不多，同時把從閻基那裏聽來的關於20年前比武的一些信息告訴胡斐，從比武到最後，最\n"NOR);
     	tell_object(me,YEL"後因為胡一刀妄想破解“提撩劍白鶴舒翅”結果不敵而自殺。説了好一會，才説完。\n\n"NOR);
	    tell_room(environment(me),HIC"\n"+me->query("name")+"似乎悄悄告訴胡斐一些事情。\n"NOR, ({}));
     	command("bite");
     	command("say");
     	command("say 無論如何，看來爹爹死在苗人鳳手下千真萬確。我的胡家刀法終於能夠返璞歸真，既然苗人鳳\n就是兇手，就算我武功不濟，也必保此仇！");
      me->set(QUESTDIR1+"over",1);
   	  me->add("max_neili",me->query_skill("force")/3);
          me->add("combat_exp",me->query_skill("force")*2);
      i=random(40)+80;
      me->set(QUESTDIR+"time",time());
      me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
      me->add("mana",i);
          tell_object(me,HBYEL"\n你於"+NATURE_D->game_time()+"解開雪山飛狐兩頁刀法篇，獲得"+(int)me->query_skill("force")/3+"點最大內力、"+((int)me->query_skill("force")*2)+"點經驗獎勵以及"+i+"點聲望。\n\n"NOR);
      log_file("quest/FEIHU", sprintf("%s(%s) 兩頁刀法篇完成。獲得%d點最大內力，%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), me->query_skill("force")/3,me->query_skill("force")*2 ,i) );
     	me->delete_temp(QUESTDIR1+"liangye");
      return;
}
void kill_ob(object me)
{
	command("sneer " + me->query("id"));
  power_condition(me,this_object(),300+random(100));
  remove_call_out("killing");
	call_out("killing", 2);
	::kill_ob(me);
}
int start_condition(object ob)
{
	 if(!ob) return 0;
   ob->set_skill("force", 300);
	 ob->set_skill("dodge", 300);
	 ob->set_skill("parry", 300);
	 ob->set_skill("blade", 300);
	 ob->set_skill("cuff",300);
	 ob->set_skill("taxue-wuhen",300);
	 ob->set_skill("zhentian-quan",300);
	 ob->set_skill("lengquan-shengong",300);
	 ob->set_skill("hujia-daofa",300);
   ob->map_skill("force","lengquan-shengong");
	 ob->set("combat_exp", 2000000);
	 ob->set("max_qi", 30000);
	 ob->set("eff_qi", 30000);
	 ob->set("max_jing", 3000);
	 ob->set("max_neili", 5000);
	 ob->set("eff_jingli",3000);
	 ob->set("qi",30000);
	 ob->set("jing",3000);
	 ob->set("jingli",3000);
	 ob->set("neili", 5000);
   return 1;
}
int power_condition(object me,object ob,int p)
{
	  int i;
    if (!present("blade",ob))
	    carry_object(BINGQI_D("blade"))->wield();
	  else command("wield blade");
    ob->set_temp("quest/雪山飛狐/武功/lengquan",1);
	  i=me->query("max_pot");
	  if(p<150) p=150;
	  if(i<p) i=p;
	  i=i-100;
	  ob->set_skill("force", i+random(50));
	  ob->set_skill("dodge", i+random(50));
	  ob->set_skill("parry", i+random(50));
	  ob->set_skill("blade", i+random(50));
	  ob->set_skill("cuff",i+random(50));
	  ob->set_skill("taxue-wuhen",i+random(50));
	  ob->set_skill("zhentian-quan",i+random(50));
	  ob->set_skill("lengquan-shengong",i+random(50));
	  ob->set_skill("hujia-daofa",i+random(50));
	  ob->map_skill("force","lengquan-shengong");
 	  i=me->query("combat_exp");
	  ob->set("combat_exp",i);
	  i=me->query("neili");
	  if(i<15000) i=15000;
	  ob->set("neili", i);
	  i=me->query("max_neili");
	  if(i<6000) i=6000;
	  ob->set("jiali",200);
	  ob->set("max_neili", i);
  	i=me->query("max_qi");
          ob->set("max_qi", i*(6+random(3))/4);
 	  ob->set("eff_qi", ob->query("max_qi"));
 	  ob->set("qi", ob->query("max_qi"));
    return 1;
}
int do_hit(string arg)
{
         object me,ob;
         me=this_player();
         ob=this_object();
         if((arg==("hu"))||(arg==("hu fei"))){
           	command("sneer");
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	return 1;
         }
         return 0;
}
int killing()
{
	int i;
	object *enemy,ob,me;

	ob=this_object();
	enemy = ob->query_enemy();
	if( !enemy || !arrayp(enemy) )
	{
		 remove_call_out("killing");
	   start_condition(ob);
  	 return 0;
  }
	i = sizeof(enemy);
	if(i>4) i=4;
  if(i>0) me=enemy[random(i)];
  else
  {
		 remove_call_out("killing");
	   start_condition(ob);
  	 return 0;
  }
  if(!me || !ob->is_fighting(me) )
	{
		 remove_call_out("killing");
	   start_condition(ob);
  	 return 0;
  }

  if (!present("blade",ob))
  {
	  message_vision(HIR"\n$N身行向後一躍，不知道從哪裏竟然又拿出一把鋼刀。\n"NOR,ob);
  	carry_object(BINGQI_D("blade"))->wield();
  }
	else command("wield blade");
  i=ob->query_temp("pfm");

 //zongjue 無用
 if(ob->query_skill_mapped("blade") != "hujia-daofa")
  {
	ob->map_skill("blade","hujia-daofa");
	ob->map_skill("parry","hujia-daofa");
	  message_vision(HIR"\n$N冷冷一笑：“$n的那點招數，對我完全無效，什麼獨孤九劍，豈能料到我神功奧妙無雙。”\n"NOR,ob,me);
  }
  //增加絕技
  if(i<(2+random(me->query("int")/5))) i++;
  else
  {
    ob->delete_temp("quest/雪山飛狐/武功/lengquan");
    i=0;
  	if(ob->query_busy())
  	{
  		if(ob->query_busy()>2) ob->start_busy(me->query_busy()/2);
  		else ob->start_busy(random(2));
      if(random(2)) message_vision(HIR"\n$N逆轉冷泉神功，瞬間化解原本束縛$N行動的困境，手腳頓時靈活了許多！\n"NOR, ob);
      else message_vision(HIC"\n$N氣穿百穴，逆轉冷泉神功，瞬間原本束縛$N行動的困境已化為烏有，招數更見凌厲！\n"NOR, ob);
    }
     switch(random(6))
     {
     	case 0:
            message_vision(HIW"\n$N輕舒猿臂，手中的鋼刀吞吞吐吐，變化莫測，籠罩了$n周身要害！\n" NOR, this_object(),me);
            if(random(3) && !me->query_busy())
            {
            	message_vision(HIC"$n見來招實在是變幻莫測，不由得心生懼意，招式登時出了破綻！\n" NOR, this_object(),me);
              me->add_busy(2+random(4));
            }
            break;
     	case 1:
     		    message_vision(HIR"\n$N手中的鋼刀幻出漫天刀雲，雷霆霹靂般的擊向一刀劈向$n！\n" NOR, this_object(),me);
	          ob->add_temp("apply/attack", ob->query_skill("blade"));
	          ob->add_temp("apply/damage", ob->query_skill("blade"));
          	  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
	          ob->add_temp("apply/attack", -ob->query_skill("blade"));
	          ob->add_temp("apply/damage", -ob->query_skill("blade"));
	          ob->start_busy(1);
            break;
     }
    ob->set_temp("quest/雪山飛狐/武功/lengquan",1);
  }
  ob->set_temp("pfm",i);
	call_out("killing",1);
  return 1;
}
/*
void die()
{
	object ob=this_object();

	if(ob->query_temp("biwu"))
	{
    start_condition(ob);
    if((string)file_name(environment(ob))!="/d/huanghe/lianwuchang")
        message_vision(HIR"\n$N撓了撓頭，似乎很是困惑。\n"NOR,ob);
    ob->set_temp("lost",1);
   	ob->remove_all_killer();
  }
  else
  {
	::die();
  }
}

int ask_me1()
{
	object me = this_player();
	{
	command("say 當年我爹爹和號稱“打遍天下無敵手”的苗人鳳在此比武，苗人鳳以毒刀\n"
"將我爹爹害死，我娘自刎殉夫。待我遇見那殺父仇人，定將他碎屍萬斷......不過，\n"
"他二人豪氣相侔，相敬相重，苗人鳳怎麼會下如此黑手？");
	command("consider");
	me->set_temp("marks/ah1",1);
	return 1;
	}
}

int do_emote()
{
	object ob = this_object();
	if(this_player()->query("id")=="yan ji") {
	  command("say 閻基，原來是你這個敗類害死我爹爹，去死吧！");
	  message_vision("$N一刀將$n砍翻在地。\n", ob,present("yan ji"));
	  present("yan ji")->die();
	  command("say 我去殺了那個田歸農，為爹爹報仇！");
	  message_vision("$N勿勿忙忙離開了。\n",ob);
	  destruct(ob);
	  return 1;
	  }
}
*/

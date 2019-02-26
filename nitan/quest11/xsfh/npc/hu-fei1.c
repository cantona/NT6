//hufei.c
//by tangfeng@SJ

inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR "quest/雪山飛狐/"
#define QUESTDIR1 "quest/雪山飛狐/兩頁刀法篇/"
#define QUESTDIR2 "quest/雪山飛狐/復仇篇/"
#define QUESTDIR3 "quest/雪山飛狐/解藥篇/"
#define QUESTDIR4 "quest/雪山飛狐/武功/"
int do_halt1(string arg);
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
int try_fight(object me, object ob);
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
	    HIR"遼東大俠胡一刀的兒子。"NOR);
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
	set("unique", 1);

	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("blade", 300);
	set_skill("cuff",300);
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
	set_skill("xuantian-wuji",300);
	set_skill("hujia-daofa",300);
	map_skill("force","lengquan-shengong");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
	map_skill("blade","hujia-daofa");
	map_skill("parry","hujia-daofa");
  prepare_skill("cuff", "zhentian-quan");
	set("combat_exp", 2000000);
	set("max_qi", 30000);
	set("max_jing", 3000);
	set("max_neili", 5000);
	set("eff_jingli",3000);
	set("qi",30000);
	set("jing",3000);
	set("jingli",3000);
	set("neili", 5000);

        set("inquiry", ([
        "胡一刀" : (: ask_huyidao :),
        "胡家刀法" : (: ask_hujiadaofa :),
        "兩頁刀法" : (: ask_liangyedaofa :),
        "較量" : (: ask_jiaoliang :),
        "比武" : (: ask_biwu :),
        "治療" : (: ask_zhiliao :),
        "苗若蘭" : (: ask_miaoruolan :),
//    "苗人風" : (: ask_miaorenfeng :),
        "苗人鳳" : (: ask_miaorenfeng :),
        "苗人風" : (: ask_miaorenfeng :),
        "閻基" : (: ask_yanji :),
        "程靈素" : (: ask_cheng :),
        "田歸農" : (: ask_tian :),
        "家仇" : (: ask_jiachou :),
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
  if (interactive(ob = this_player()) ) {
       remove_call_out("greeting");
       call_out("greeting", 1, ob);
  }
	add_action("do_answer","answer");
	add_action("do_halt1","halt");
  add_action("do_hit", "hit");
}
int do_halt1(string arg)
{
         object me,ob;
         me=this_player();
         ob=this_object();
	       command("sneer");
         remove_call_out("do_halt");
         remove_call_out("try_fight");
  	     ob->reset_action();
	       ob->delete("quest/try_fight");
	       ob->delete("quest/try_fight_id");
	       me->delete_temp(QUESTDIR+"較量/hu_fighting");
	       start_condition(ob);
	       command("halt");
         ob->remove_all_killer();
         me->remove_all_killer();
         return 1;

}
void greeting(object me)
{
  int shen,i;
  if(!me) return;
  if(environment(me)!=environment(this_object())) return;
  shen = me->query("shen");
	if(me->query_temp(QUESTDIR2+"over"))
	{
/*
　胡斐喘了口氣，面對著這個自己生平想過幾千幾萬遍之人，一時之間竟爾沒了主意：“他是我殺父仇人，可是他又是若蘭的父親”。
　　“他害得我一生孤苦，但聽平四叔説，他豪俠仗義，始終沒對不起我的爹媽”。
　　“他號稱打遍天下無敵手，武功藝業，舉世無雙，但我偏不信服，倒要試試是他強呢還是我強？”
*/
	 if(me->query_condition("killer"))
	 {
	   command("fear "+me->query("id"));
     command("say 小心官府通緝！");
	   return;
	 }
		tell_object(me,CYN"\n你急忙將真相告訴胡斐，胡斐聞言更是泣不成聲....\n"NOR);
  	command("cry");
    me->delete_temp(QUESTDIR2+"over");
        tell_object(me,HIW"\n“田歸農！”胡斐悲笑起來，仇恨似乎更是沉積，算是萬幸，天龍門早已滅門，這恩怨也算是瞭解。\n\n"NOR);
    me->set(QUESTDIR2+"over",1);
    me->delete_temp(QUESTDIR2+"over");
  	tell_object(me,HIG"你不知道是喜是悲，想想這個結果對胡斐來説也許也是個園結。\n"NOR);
  	command("say 苗大俠，不知道毒發如何？");
  	tell_object(me,CYN"你點頭道：我馬上去苗家莊，你心情不定，還是先歇息為妙。\n"NOR);
   	me->add("max_neili",me->query_skill("force")/2);
   	me->add("combat_exp",me->query_skill("force"));
   	i=180+random(40);
   	me->add("mana",i);
  	tell_object(me,HBYEL"\n你於"+NATURE_D->game_time()+"解開雪山飛狐復仇篇，獲得"+(int)me->query_skill("force")/2+"點最大內力、"+(int)me->query_skill("force")+"點經驗獎勵、"+i+"點聲望。\n\n"NOR);
          log_file("quest/FEIHU", sprintf("%s(%s) 揭開雪山飛狐Quest復仇篇,時間 %s。獲得%d點最大內力，%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), ctime(time()),me->query_skill("force")/2,me->query_skill("force"),i ) );
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
	  command("say 真的感謝程姑娘，要不是她恐怕我抱憾終生。");
	  command("think");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"getjieyao"))
  {
	  command("suicide1");
	  command("say 真的感謝程姑娘，我們還是趕快去救治苗大俠吧。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& (me->query_temp(QUESTDIR3+"jieyao2")||me->query_temp(QUESTDIR3+"qixinghaitang")))
  {
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
	  command("blush");
	  command("say 程姑娘當年我與她有過一面之交，只是現在身在何處，不很清楚......");
	  command("sigh");
	  return 1;
  }
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
	command("say 當年我爹爹和號稱“打遍天下無敵手”的苗人鳳在此比武，苗人鳳以毒刀\n將我爹爹害死，我娘自刎殉夫。待我遇見那殺父仇人，定將他碎屍萬斷......不過，\n"
          "他二人豪氣相侔，相敬相重，苗人鳳怎麼會下如此黑手？");
	command("consider");
	command("doubt");
	return 1;
}

int ask_hujiadaofa()
{
	object me = this_player();
	object ob = this_object();
	int i;
	if(me->query_condition("killer"))
	 {
	   command("fear "+me->query("id"));
     command("say 小心官府通緝！");
	   return 1;
	}
	if(me->query(QUESTDIR2+"start") && !me->query(QUESTDIR3+"over"))
  {
	  command("shake "+me->query("id"));
	  command("say 現在時間緊急，這刀法還是以後切磋吧。");
	  return 1;
  }
  if(me->query(QUESTDIR4+"hujiadaofa_fail")>=3 && me->query("registered")<3)
  {
	  command("shake "+me->query("id"));
	  command("say 這刀法還是以後切磋吧。");
	  return 1;
	}

  if(me->query(QUESTDIR4+"hujiadaofa"))
  {
   if(me->query("potential")<= 5)
   {
	  command("? "+me->query("id"));
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
    me->improve_skill("hujia-daofa", 10+random(me->query_int()));
    me->improve_skill("blade", random(me->query_int())/2);
    return 1;
   }
  }
	if(me->query(QUESTDIR4+"time") && (time() - me->query(QUESTDIR4+"time"))<86400)
	{
	  command("hehe "+me->query("id"));
	  command("say 現在時間緊急，這刀法還是明天再來吧。");
	  return 1;
	}
  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 不是剛學完嗎，這刀法還是以後切磋吧。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("nod "+me->query("id"));
	  if(me->query(QUESTDIR4+"combat_exp") && (me->query("combat_exp") - me->query(QUESTDIR4+"combat_exp"))<1000000)
	  {
	    command("shake "+me->query("id"));
	    command("say 你還是專門練功去吧，你武功未有長進，只怕還是難以領悟。");
	    return 1;
	  }
    message_vision(HIB"\n$n突然運起獨門內功冷泉神功，只感覺刀勢無風自起。\n"NOR, me, ob);
    ob->set_temp("quest/雪山飛狐/武功/lengquan",1);
    ob->set_temp("busy",1);
    power_condition(me,ob,300+random(100));
	  for ( i = 0; i < 6+random(8);i++){
	     hufei_fight(me, ob);
    }
    ob->delete_temp("quest/雪山飛狐/武功/lengquan");
    start_condition(ob);
    tell_object(me,CYN"\n\n\n一晃數招已過，胡斐笑説道：「剛才我使用的招數可看清楚了？」\n"NOR);
    command("smile "+me->query("id"));
    remove_call_out("busy_pass");
    remove_call_out("thinking");
    me->set(QUESTDIR4+"time",time());
    me->set(QUESTDIR4+"combat_exp",me->query("combat_exp"));
    ob->set_temp("busy",1);
		call_out("busy_pass",600, ob);
		call_out("thinking",3, me, ob);
    tell_object(me,CYN"你開始認真考慮。\n"NOR);
    me->start_busy(3+random(i));
	  return 1;
  }
  if(me->query(QUESTDIR1+"start"))
  {
	  command("shout");
	  if(random(2)) command("say 可惜我武功未能圓通，不能為報父仇，這胡家刀法總是不能返璞歸真。");
	  else command("say 苗人風聽説武功號稱打遍天下，自是厲害，可惜我胡家刀法祕籍竟有殘缺，因此在下武功終未大成。");
	  return 1;
  }
  if(me->query_temp(QUESTDIR1+"jiachou"))
  {
 	  command("heng");
	  command("say 我胡家刀法確是一等一的武功，只是爹爹留給我祕籍竟然缺了兩頁，缺了紮根基的入門功夫，缺了拳法刀法的總訣。");
	  command("say 這些年來，無論怎麼用功，總是難以融會貫通，聽説苗人風號稱打遍天下無敵手，可惜我胡家刀法祕籍竟有殘缺，不是對手。");
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
int hufei_fight(object me, object ob)
{
  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  if (!present(me,environment(ob)) || me->query("qi") <= me->query("max_qi")/50 || me->query("jing") <= 10 || me->query("jingli") <= 10)  {
	command("sneer");
	command("say 這位大俠武功未能返璞歸真，只怕難以領悟胡家刀法的絕技！");
	return 0;
  }
  return 1;
}
int busy_pass(object ob)
{
	if(!ob) return 0;
	if(ob->query_temp("busy")) ob->delete_temp("busy");
  return 1;
}

int thinking(object me, object ob)
{
	int i;
  if(environment(me)!=environment(this_object()))
  {
  	start_condition(ob);
  	return 1;
  }
	if(!me->query_temp(QUESTDIR4+"thinking"))
	{
		me->set_temp(QUESTDIR4+"thinking",1);
    tell_object(me,HIG"你努力地回憶剛才的每一招每一式......\n"NOR);
    tell_object(me,CYN"你努力地回憶剛才的每一招每一式......\n"NOR);
		call_out("thinking",4, me, ob);
	}
	else
	{
	  if(random(me->query("pur"))>28 && random(me->query("int"))>28)
    {
       tell_object(me,HIG"\n你明悟其中，突然間明白了一切。\n"NOR);
       tell_object(me,CYN"你「哈哈哈」大笑幾聲。\n"NOR);
       tell_object(me,CYN"你説道：「"NOR+HIR"我明白了。"NOR+CYN"」\n"NOR);
       command("nod");
       command("congra");
       tell_object(me,HIR"你聽了胡斐的指點，對胡家刀法的奧妙似乎有些心得。\n"NOR);
       tell_object(me,HIR"只是你發現這胡家刀法還需要冷泉神功才能發揮全效。\n"NOR);
       me->set(QUESTDIR4+"hujiadaofa",1);
       me->delete(QUESTDIR4+"hujiadaofa_fail");
   	   i=180+random(40);
   	   me->add("mana",i);
  	   tell_object(me,HBYEL"\n你於"+NATURE_D->game_time()+"解開雪山飛狐胡家刀法篇，並獲得"+i+"點聲望。\n\n"NOR);
	     log_file("quest/FEIHU", sprintf("%s(%s) 揭開雪山飛狐胡家刀法,時間 %s，並獲得%d點聲望。\n", me->name(1),me->query("id"), ctime(time()),i ) );
    }
    else
    {
       tell_object(me,HIG"\n你似乎抓住了什麼，可是依然不是很明白。\n"NOR);
       tell_object(me,CYN"你搖了搖頭，道：好像還是很困難的。\n"NOR);
       tell_object(me,HIY"你深深地歎了口氣。\n"NOR);
       me->add(QUESTDIR4+"hujiadaofa_fail",1);
      if(me->query(QUESTDIR4+"hujiadaofa_fail")>=3 && me->query("registered")<3)
       {
      	tell_object(me,HBYEL"\n你於"+NATURE_D->game_time()+"最後一次嘗試揭開雪山飛狐胡家刀法，卻沒有成功。\n\n"NOR);
   		  log_file("quest/FEIHU", sprintf("%s(%s) 最後一次嘗試揭開雪山飛狐胡家刀法，卻沒有成功。時間 %s。\n", me->name(1),me->query("id"), ctime(time()) ) );
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
  	command("say 爹爹的死我這就去找苗人風算賬去！");
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
	  command("say 正所謂父仇不兩立，既然知道殺害我爹的兇手，就算我這身武功不濟，也決不苟生。");
	  if(!me->query(QUESTDIR2+"answer")){
	     command("look "+me->query("id"));
       command("sigh");
	     command("say 這位大俠，武功超絕，不知道是否願意幫忙？");
       tell_object(me,HIG"回答命令answer yes 或者answer no\n"NOR);
       me->set_temp(QUESTDIR2+"answer_",1);
    }
    else
    {
	     command("look "+me->query("id"));
       command("thank");
	     command("say 只要這位大俠能夠幫忙，在下不勝感激。其實我也不能確認這事情原委。");
    }
  	return 1;
  }
  if(me->query(QUESTDIR+"time") && (time() - me->query(QUESTDIR+"time"))<86400)
	{
	  command("shake "+me->query("id"));
	  command("say 沒看見我很忙，明天再來。");
	  return 1;
	}
  if(me->query(QUESTDIR1+"over"))
  {
	  command("say 我一直懷疑他就是殺害我爹的兇手，只是苗家素有俠名，所以不敢確認，如今真相大白。");
	  command("say 正所謂父仇不兩立，既然知道殺害我爹的兇手，就算我這身武功不濟，也決不敢偷生了。");
    command("sigh");
    me->set(QUESTDIR+"time",time());
	  command("look "+me->query("id"));
	  command("say 這位大俠，武功超絕，不知道是否願意幫忙？");
    tell_object(me,HIG"回答命令answer yes 或者answer no\n"NOR);
    me->set_temp(QUESTDIR2+"answer_",1);
    me->set(QUESTDIR2+"start",1);
	  return 1;
  }
  if(me->query(QUESTDIR1+"start"))
  {
	  command("shout");
	  command("say 我一直懷疑苗人風就是殺害我爹的兇手，只是他素有俠名，所以不敢確認。");
	  return 1;
  }
  if(me->query_temp(QUESTDIR1+"jiachou"))
  {
	  command("shout");
	  command("consider");
	  command("say 我真的不明白，想不通這其中的變化，只可惜我爹媽死得不明不白。");
	  return 1;
  }
	command("say 當年我爹爹和號稱“打遍天下無敵手”的苗人鳳在此比武，苗人鳳以毒刀\n"
"  將我爹爹害死，我娘自刎殉夫。待我遇見那殺父仇人，定將他碎屍萬斷......不過，\n"
"  他二人豪氣相侔，相敬相重，苗人鳳怎麼會下如此黑手？");
	command("consider");
	command("doubt");
  me->set(QUESTDIR+"time",time());
	me->set_temp(QUESTDIR1+"jiachou",1);
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
	  me->set_temp(QUESTDIR2+"answer","yes");
	}
	else
	{
    tell_object(me,CYN"\n你驚異地説道：我卻有些懷疑，苗大俠怎麼可能是兇手呢！不是算為你，我也要去一次苗家莊吧！\n"NOR);
	  me->set_temp(QUESTDIR2+"answer","no");
	}
	return 1;
}

int ask_jiaoliang()
{
	object me = this_player();
	object ob = this_object();
	if(me->query_condition("killer"))
	 {
	   command("fear "+me->query("id"));
     command("say 小心官府通緝！");
	   return 1;
	}
  if(!me->query(QUESTDIR3+"over") && me->query(QUESTDIR2+"start"))
  {
	  command("shake "+me->query("id"));
	  command("say 現在時間緊急，還是以後切磋吧。");
	  return 1;
  }
  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 剛切磋完，以後切磋吧。");
	  return 1;
  }
  if(random(me->query("combat_exp"))<random(ob->query("combat_exp")*2/3) && !wizardp(me))
  {
	  command("say 危險，太危險了！");
    COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	  command("fear "+me->query("id"));
    COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	  command("say 危險，太危險了！");
    COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	  command("fear "+me->query("id"));
    return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("nod "+me->query("id"));
    message_vision(HIY"\n$n突然運起獨門內功冷泉神功，只感覺刀勢無風自起。\n"NOR, me, this_object());
    me->set_temp(QUESTDIR+"較量/hu_fighting",1);
    power_condition(me,ob,300+random(100));
	  ob->set("quest/try_fight",1);
	  ob->set("quest/try_fight_id",me->query("id"));
    ob->kill_ob(me);
	  command("sneer");
    remove_call_out("busy_pass");
    remove_call_out("do_halt");
    remove_call_out("try_fight");
    ob->set_temp("busy",1);
		call_out("busy_pass",600, ob);
    call_out("do_halt", 150,me);
		call_out("try_fight", 2, me, ob);
    me->start_busy(1);
    ob->start_busy(1);
	  return 1;
  }

	command("say 想和我比試？看好了！");
	command("sneer");
  power_condition(me,ob,250+random(200));
  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	command("sneer");
	start_condition(ob);
	return 1;
}

int try_fight(object me, object ob)
{
	int i;
	if (!me->is_fighting(ob)|| !ob->is_fighting(me)||!present(me,environment(ob)) || me->query("eff_qi") <= 1000|| me->query("qi") <= 0 || me->query("jing") <= 10 || me->query("jingli") <= 10)  {
	   command("sneer");
	   command("say 這位大俠武功未能返璞歸真，只怕難以抵擋胡家刀法的進攻！");
     remove_call_out("do_halt");
     remove_call_out("try_fight");
  	 ob->reset_action();
	   ob->delete("quest/try_fight");
	   ob->delete("quest/try_fight_id");
	   me->delete_temp(QUESTDIR+"較量/hu_fighting");
	   start_condition(ob);
	   command("halt");
     ob->remove_all_killer();
     me->remove_all_killer();
  	 return 1;
  }
  if (!present("blade",ob))
	    carry_object(BINGQI_D("blade"))->wield();
	else command("wield blade");

  i=me->query_temp(QUESTDIR+"較量/fight_times");

  if(i<(2+random(me->query("int")/20))) i++;
  else
  {
  	if(ob->query_busy())
  	{
  		if(ob->query_busy()>2) ob->start_busy(me->query_busy()/2);
  		else ob->start_busy(random(2));
      message_vision(HIR"\n$N"MAG"逆轉冷泉神功，瞬間化解原本束縛$N行動的困境，手腳頓時靈活了許多！\n"NOR, ob);
      if(random(2))
      {
            message_vision(HIW"\n$N"HIW"輕舒猿臂，手中的鋼刀吞吞吐吐，變化莫測，籠罩了$n"HIW"周身要害！\n" NOR, this_object(),me);
            ob->command("haha");
            if(random(3))
            {
            	message_vision(HIY"\n$n"HIY"見來招實在是變幻莫測，不由得心生懼意，招式登時出了破綻！\n" NOR, this_object(),me);
              me->add_busy(3+random(4));
              COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            }
            else
            {
            	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            }
	    }
    }
    else
    {
     switch(random(6))
     {
     	case 0:
            message_vision(HIW"\n$N"HIW"輕舒猿臂，手中的鋼刀吞吞吐吐，變化莫測，籠罩了$n"HIW"周身要害！\n" NOR, this_object(),me);
            ob->command("haha");
            if(random(3))
            {
            	message_vision(HIY"\n$n"HIY"見來招實在是變幻莫測，不由得心生懼意，招式登時出了破綻！\n" NOR, this_object(),me);
              me->add_busy(3+random(4));
              COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            }
            else
            {
            	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            }
            break;
     	case 1:
     	case 2:
            message_vision(HIC"\n突然之間，本就快捷絕倫的刀法驟然變得更加凌厲！就在這一瞬之間，$N已劈出七刀！\n"NOR, this_object(),me);
            ob->command("haha");
          	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
          	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
          	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
          	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            break;
     	case 3:
     	case 4:
     		    message_vision(HIR"\n$N手中的鋼刀幻出漫天刀雲，雷霆霹靂般的擊向$n！\n" NOR, this_object(),me);
	          ob->add_temp("apply/attack", ob->query_skill("blade"));
	          ob->add_temp("apply/damage", ob->query_skill("blade"));
          	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
	          ob->add_temp("apply/attack", -ob->query_skill("blade"));
	          ob->add_temp("apply/damage", -ob->query_skill("blade"));
            ob->command("haha");
            break;
     	default:
      	    message_vision(HIB"\n$n突然運起獨門內功冷泉神功，只感覺刀勢無風自起。\n"NOR, me, this_object());
            ob->command("heng");
	          ob->add_temp("apply/attack", ob->query_skill("blade")/4);
            break;
     }
    }
     i=0;
  }
  me->set_temp(QUESTDIR+"較量/fight_times",i);
	call_out("try_fight", 1, me, ob);
  return 1;
}
int ask_liangyedaofa()
{
	object me = this_player();
  if(me->query(QUESTDIR1+"over"))
  {
  	command("thank "+me->query("id"));
	  command("say 感謝大俠幫我找到這兩頁刀法，我才能將胡家刀法融會貫通。");
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
    tell_object(me,CYN"你緩緩地搖了搖頭，歎氣道：恩恩怨怨何時了。\n"NOR);
	  return 1;
  }
	command("say 聽説是上任天龍門掌門，很久不知下落了。現在天龍門大不如以前了。");
	return 1;
}

int accept_object(object who, object ob,object me)
{
	 if(ob->query("id")=="liangye daofa")
   {
   	 command("ah "+(string)who->query("id"));
     if(who->query_temp(QUESTDIR1+"liangye") && who->query(QUESTDIR1+"start"))
     {
     	/*
     	因為他父親曾遺給他記載着武林絕學的一本拳經刀譜，那便是胡家拳法和刀法的精義。
     	這本拳經刀譜本來少了頭上兩頁，缺了紮根基的入門功夫，缺了拳法刀法的總訣，於是不論他多麼聰明用功，總是不能入門。
     	現下機緣巧合，給閻基偷去的總訣找回來了，於是一加融會貫通，武功進境一日千里。
     	*/
     	command("jump "+(string)who->query("id"));
        tell_object(who,HIY"\n你把兩頁刀法將給胡斐。胡斐仔細地看了兩遍，不由驚叫起來，“正是這兩頁刀法，不是大俠何處得來？”\n"NOR);
        tell_object(who,HIG"你簡單説了一下你去苗疆；卻見胡斐傻傻地盯着這兩頁刀法，不由自主地演練起來，全然忘記你的存在。\n\n"NOR);
     	who->start_busy(4);
      remove_call_out("telltruth");
      call_out("telltruth", 4, who);
     }
     else  command("thank "+(string)who->query("id"));
   }
    else
   {
     command("? "+(string)who->query("id"));
   }
   call_out("destroying", 1, ob);
   return 1;
}
void destroying(object obj)
{
        if(obj) destruct(obj);
        return;
}
void telltruth(object me)
{
	    int i;
	    if(!me) return;
	    if(environment(me)!=environment(this_object()))   	return;
      if(!me->query_temp(QUESTDIR1+"liangye")) return;
      write("\n\n");
     	command("haha");
     	command("say 不錯就是它，正是我胡家刀法無法圓通的缺陷所在！");
     	tell_object(me,YEL"\n你看胡斐練得差不多，同時把從閻基那裏聽來的關於20年前比武的一些信息告訴胡斐，從比武到最後，最\n"NOR);
     	tell_object(me,YEL"後因為胡一刀妄想破解“提撩劍白鶴舒翅”結果不敵而自殺。説了好一會，才説完。\n\n"NOR);

     	command("bite");
     	command("say");
     	command("say 無論如何，看來爹爹死在苗人風手下千真萬確。我的胡家刀法終於能夠返璞歸真，既然苗人風\n就是兇手，就算我武功不濟，也必保此仇！");
      me->set(QUESTDIR1+"over",1);
   	  me->add("max_neili",me->query_skill("force")/2);
   	  me->add("combat_exp",me->query_skill("force"));
      i=random(40)+80;
      me->add("mana",i);
    	tell_object(me,HBYEL"\n你於"+NATURE_D->game_time()+"解開雪山飛狐兩頁刀法篇，獲得"+(int)me->query_skill("force")/2+"點最大內力、"+(int)me->query_skill("force")+"點經驗獎勵。\n\n"NOR);
	    log_file("quest/FEIHU", sprintf("%s(%s) 揭開雪山飛狐Quest兩頁刀法篇,時間 %s。獲得%d點最大內力，%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), ctime(time()),me->query_skill("force")/2,me->query_skill("force") ,i) );
     	me->delete_temp(QUESTDIR1+"liangye");
      return;
}
void kill_ob(object me)
{
	 command("sneer " + me->query("id"));
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
	  ob->set("max_qi", i*(2+random(3)));
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

void do_halt(object me)
{
	if(!this_object()->is_fighting() && !me->is_fighting()) return;
   command("say 我可沒功夫在耗下去了，下次再較量吧。");
   remove_call_out("do_halt");
   remove_call_out("try_fight");
	 this_object()->delete("quest/try_fight");
	 this_object()->delete("quest/try_fight_id");
   start_condition(this_object());
	 command("halt");
   this_object()->remove_all_killer();
   me->remove_all_killer();
   return;
}
void unconcious()
{
	object me,ob=this_object();

	if(this_object()->query("quest/try_fight"))
	{
	  command("ah");
    command("halt");
    start_condition(ob);
	  if(ob->query("quest/try_fight_id"))
	  {
	  	me=find_player(ob->query("quest/try_fight_id"));
	  	if(!me) return 0;
	  	if(!me->query_temp(QUESTDIR+"較量/hu_fighting")) return 0;
	    if(environment(me)!=environment(this_object()))  return 0;
	  	me->delete_temp(QUESTDIR+"較量/hu_fighting");
	  	me->add("combat_exp",me->query_skill("force")/2);
	    command("thumb "+me->query("id"));
	    command("admire "+me->query("id"));
	  	tell_object(me,HIR"\n經過一番苦鬥，你發現自己的武功大有激進。你獲得"+me->query_skill("force")/2+"點經驗。\n"NOR);
	  }
	   ob->delete("quest/try_fight");
	   ob->delete("quest/try_fight_id");
     ob->remove_all_killer();
     me->remove_all_killer();
     remove_call_out("do_halt");
     remove_call_out("try_fight");
  }
  else
  {
	command("why");
	::unconcious();
  }
}
void die()
{
	object me,ob=this_object();

	if(this_object()->query("quest/try_fight"))
	{
	  command("ah");
    command("halt");
    start_condition(ob);
	  if(ob->query("quest/try_fight_id"))
	  {
	  	me=find_player(ob->query("quest/try_fight_id"));
	  	if(!me) return 0;
	  	if(!me->query_temp(QUESTDIR+"較量/hu_fighting")) return 0;
	    if(environment(me)!=environment(this_object()))   	return 0;
	  	me->delete_temp(QUESTDIR+"較量/hu_fighting");
	  	me->add("combat_exp",me->query_skill("force")/2);
	  	tell_object(me,HIR"\n經過一番苦鬥，你發現自己的武功大有激進。你獲得"+me->query_skill("force")/2+"點經驗。\n"NOR);
	    command("thumb "+me->query("id"));
	    command("admire "+me->query("id"));
	  }
	   ob->delete("quest/try_fight");
	   ob->delete("quest/try_fight_id");
     ob->remove_all_killer();
     remove_call_out("do_halt");
     remove_call_out("try_fight");
  }
  else
  {
	command("why");
	::die();
  }
}
/*
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

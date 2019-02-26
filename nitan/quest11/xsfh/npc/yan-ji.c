//by tangfeng@SJ 8/2004


inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR1 "quest/雪山飛狐/兩頁刀法篇/"
#define QUESTDIR2 "quest/雪山飛狐/復仇篇/"
#define QUESTDIR3 "quest/雪山飛狐/解藥篇/"

void kill_player(object me);
void unconcious();
void die();
void kill_ob(object me);
int do_hit(string arg);
int ask_hufei();
int ask_qixinghaitang();
int ask_liangyedaofa();
int ask_hujiadaofa();
int ask_biwu();
int ask_miaorenfeng();
int ask_huyidao();
int ask_tian();
int ask_xiadu();
int ask_cheng();
int power_condition(object me,object ob,int p);
int start_condition(object ob);

void create()
{
	set_name("閻基", ({ "yan ji", "yan", "ji" }) );
	set("gender", "男性" );
	set("title", RED"江湖郎中"NOR);
	set("age", 51);
	set("long",
	    "赤腳醫生，善於用毒，臉上透露着一絲狡詐。\n");
	set("str", 20);
	set("dex", 20);
	set("con", 20);
	set("int", 20);
	set("per", 15);
	set("shen_type", -1);
	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("cuff",300);
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
	set_skill("blade",150);
	set_skill("hujia-daofa",150);
	set_skill("huagong-dafa",150);
	map_skill("force","huagong-dafa");
	map_skill("blade","hujia-daofa");
	map_skill("parry","hujia-daofa");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
  prepare_skill("cuff", "zhentian-quan");
	set("combat_exp", 300000);
	set("max_qi", 30000);
	set("max_jing", 10000);
	set("eff_jingli",10000);
	set("max_neili", 21000);
	set("qi",30000);
	set("jing",10000);
	set("jingli",10000);
	set("neili", 42000);
  set("no_get",1);
  set("no_bark",1);
	set("inquiry", ([
		"胡一刀" : (: ask_huyidao :),
		"苗人鳳" : (: ask_miaorenfeng :),
		"田歸農" : (: ask_tian :),
		"天龍門" : (: ask_tian :),
		"比武" : (: ask_biwu :),
		"比試" : (: ask_biwu :),
		"20年前" : (: ask_biwu :),
		"決鬥" : (: ask_biwu :),
		"胡斐" : (: ask_hufei :),
		"七星海棠" : (: ask_qixinghaitang :),
		"兩頁刀法" : (: ask_liangyedaofa :),
		"胡家刀法" : (: ask_hujiadaofa :),
		"真相"   : (: ask_xiadu :),
		"下毒"   : (: ask_xiadu :),
    "程靈素" : (: ask_cheng :),
	]));
	setup();
	set("chat_chance", 2);
	set("chat_msg", ({
		"閻基將一條帶有巨毒的蛇放入竹簍裏，“嘿嘿”的奸笑幾聲。\n",
		"閻基望了你一眼，低聲説道：你面黃肌瘦，腎水虧空，是否．．．過度？\n",
	}) );
	carry_object("/clone/armor/cloth.c")->wear();
}

void init()
{
	::init();
	add_action("do_hit","hit");
}


int ask_biwu()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 不關我的事，不關我的事啊！都是“田歸農”指使小人乾的......");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh");
	  command("say 20年前的比武，其實我也不是很明白，但是胡大俠死在苗人鳳手上，確是事實。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("consider");
	  command("say 我是亂中偷盜胡家祕籍，只是當時一片混亂，我全家被毀，我也是為了生計，別無他法。");
  	command("say 但是胡大俠當年豪氣沖天，可惜小人苗人鳳竟然使用毒劍，這段公案遲早有人要去還的。");
	  return 1;
  }
	command("heng");
	command("say 胡大俠當年豪氣沖天，可惜小人苗人鳳竟然使用毒劍，這段公案遲早有人要去還的。");
	return 1;
}

int ask_tian()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("fear "+me->query("id"));
	  command("say 都是“田歸農”指使小人乾的......這天殺的卑鄙小人！");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh");
	  command("say 田相公，原是天龍門掌門，當年苗胡比武期間，我曾見過一面，最近一直沒有消息，天龍門也似乎滅跡江湖。");
	  return 1;
  }
	command("en");
	command("say 當年苗胡比武期間，我好像見過一面，那時年輕得很。最近好像早無音訊。不是很熟悉。");
	return 1;
}

int ask_miaorenfeng()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"start"))
  {
	  command("fear "+me->query("id"));
	  command("say 我，我，苗大俠最近可好？...都是“田歸農”指使小人乾的......這天殺的卑鄙小人！");
	  return 1;
  }
  command("sigh");
	command("say 苗大俠，很久沒有聽過他的蹤跡了，20年前有過一面而已。");
	return 1;

}
int ask_cheng()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("fear "+me->query("id"));
	  command("say 程姑娘還在五毒教吧！");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"qixinghaitang"))
  {
	  command("fear "+me->query("id"));
	  command("say 程姑娘，別殺我，我什麼都交出去了，剛説的也説了，饒了我吧！");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao2"))
  {
	  command("fear "+me->query("id"));
	  command("say 程姑娘，別殺我，我什麼都交出去了，剛説的也説了，饒了我吧！");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start"))
  {
	  command("fear "+me->query("id"));
	  command("say 那丫頭？和我什麼關係！");
	  return 1;
  }
  command("nod");
	command("say 聽説藥王最得意的關門弟子，現在不知道在哪裏。");
	return 1;
}
int ask_huyidao()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"start"))
  {
	  command("fear "+me->query("id"));
	  command("say 是我錯了，害死了胡大俠，不過罪魁禍首是天田歸農！");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh");
	  command("say 20年前的比武，其實我也不是很明白，但是胡大俠死在苗人鳳手上，確是事實。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("consider");
	  command("say 我是亂中偷盜胡家祕籍，只是當時一片混亂，我全家被毀，我也是為了生計，別無他法。");
  	command("say 但是胡大俠當年豪氣沖天，可惜小人苗人鳳竟然使用毒劍，這段公案遲早有人要去還的。");
	  return 1;
  }
	command("heng");
	command("say 胡大俠當年豪氣沖天，可惜小人苗人鳳竟然使用毒劍，這段公案遲早有人要去還的。");
	return 1;
}
int ask_xiadu()
{
	object me = this_player();

  if(me->query(QUESTDIR2+"over"))
  {
	  command("fear "+me->query("id"));
          command("say 是我錯了，害死了胡大俠，不過罪魁禍首是田歸農指使我下毒的！");
	  return 1;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"zhenxiang"))
  {
	  command("fear "+me->query("id"));
          command("say 是我錯了，害死了胡大俠，不過罪魁禍首是田歸農指使我下毒的！");
	  command("say 早一日晚上，胡大爺和金面佛同榻長談，我在窗外偷聽，後來給金面佛隔窗打了一拳，只打得眼青鼻腫，滿臉鮮血！");
	  command("say 我就有些生氣，第二天，正巧田歸農過來給了我一包毒藥，説是事成之後給我100兩黃金，我也是該死，貪圖這錢！");
	  command("say 那天晚上胡大爺與金面佛同房而睡，兩人光明磊落，把兵刃都放在大廳之中。我取出那毒藥悄悄去塗在兩人刀劍之上。");
          command("say 是我錯了，害死了胡大俠，不過罪魁禍首是田歸農指使我下毒的！");
	  me->set_temp(QUESTDIR2+"over",1);
	  me->delete_temp(QUESTDIR2+"zhenxiang");
    me->start_busy(3);
    remove_call_out("move_fendi");
    call_out("move_fendi", 3, me);
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("consider");
	  command("say 20年前的比武，其實我也不是很明白，但是胡大俠死在苗人鳳的毒劍上，確是事實。");
  	command("say 但是胡大俠當年豪氣沖天，可惜小人苗人鳳竟然使用毒劍，這段公案遲早有人要去還的。");
	  return 1;
  }
	command("heng");
  command("say 20年前的比武，其實我也不是很明白，但是胡大俠死在苗人鳳的毒劍上，確是事實。");
 	command("say 但是胡大俠當年豪氣沖天，可惜小人苗人鳳竟然使用毒劍，這段公案遲早有人要去還的。");
	return 1;
}
void move_fendi(object me)
{
  if(!me) return;
  if(!me->query_temp(QUESTDIR2+"over")) return;
  if(!me->query_temp(QUESTDIR2+"move_fendi"))
  {
	  tell_object(me,HIC"你聽完這段，可是驚心動魄，萬萬沒有料到堂堂的遼東大俠竟然被一個郎中下毒害死，而指使人似乎早已不在人世。\n"NOR);
    tell_object(me,HIC"你暗想：這當務之急，恐怕是先告訴胡斐這事情的經過，只是胡家這所謂大仇也最終不了了之，的確出乎意料之外。\n"NOR);
     tell_room(environment(me),HIC"\n閻基似乎告訴了"+me->query("name")+"一些事情，"+me->query("name")+"顯得有些焦急。\n"NOR, ({ me }));
     me->set_temp(QUESTDIR2+"move_fendi",1);
	 /*
     tell_room(environment(me),HIC""+me->query("name")+"疾步離開後山。\n"NOR, ({}));
    me->move("/d/miaojiang/slu1");
    tell_object(me,HIR"你還是加快速度，往胡斐的地方奔去。\n"NOR);
          tell_room(environment(me),HIC"突然一個身影掠過，原來是"+me->query("name")+"疾步離開。\n"NOR, ({ me }));
    me->move("/d/miaojiang/myp");
    tell_object(me,HIR"你還是加快速度，往胡斐的地方奔去。\n"NOR);
          tell_room(environment(me),HIC"突然一個身影掠過，原來是"+me->query("name")+"疾步離開。\n"NOR, ({ me }));
    me->move("/d/xiangyang/damen");
    tell_object(me,HIR"你稍微歇息一下。\n"NOR);
          tell_room(environment(me),HIC"突然一個身影掠過，原來是"+me->query("name")+"疾步離開。\n"NOR, ({ me }));
  	*/
    remove_call_out("move_fendi");
    call_out("move_fendi",5, me);
  }
  else
  {
    remove_call_out("move_fendi");
    tell_object(me,HIR"你稍微歇了一口氣。\n"NOR);
	/*
    me->move("/d/huanghe/shulin2");
    tell_object(me,HIR"你還是加快速度，往胡斐的地方奔去。\n"NOR);
          tell_room(environment(me),HIC"突然一個身影掠過，原來是"+me->query("name")+"疾步離開。\n"NOR, ({ me }));
    me->move("/d/huanghe/shulin6");
    tell_object(me,HIR"你還是加快速度，往胡斐的地方奔去。\n"NOR);
	  tell_room(environment(me),HIC"突然一個身影掠過，原來是$N疾步離開。\n"NOR, ({ me }));
    me->move("/d/huanghe/fendi");
    tell_object(me,HIR"\n終於到了，你長歎一口氣。\n"NOR);
          tell_room(environment(me),HIC"突然一個身影掠過，原來是"+me->query("name")+"疾步離開。\n"NOR, ({ me }));
		  */
    me->delete_temp(QUESTDIR2+"move_fendi");
  }
  return;
}

int ask_hujiadaofa()
{
	object me = this_player();
  if(me->query(QUESTDIR1+"over"))
  {
	  command("consider");
	  command("say 我是亂中偷盜胡家祕籍，只是當時一片混亂，我全家被毀，我也是為了生計，別無他法。");
	  return 1;
  }
	command("?");
  command("say 胡家刀法？在下從不使用刀法。");
	return 1;
}
int ask_hufei()
{
	object me = this_player();
  if(me->query(QUESTDIR1+"over"))
  {
	  command("fear "+me->query("id"));
	  command("say 雖然幹了一場荒唐事，天可憐見胡大俠還剩下胡斐這個孩子。我真是後悔啊......");
	  return 1;
  }
  if(me->query(QUESTDIR1+"start")&& !me->query_temp(QUESTDIR1+"hufei") && !me->query_temp(QUESTDIR1+"liangye"))
  {
	  command("consider");
	  command("say 當年冤死的胡大俠的孩子好像叫胡斐，我已經有些忘記了。");
	  command("?");
	  command("say 這位大俠不知道我和提起這個幹什麼？");
	  me->set_temp(QUESTDIR1+"hufei",1);
	  return 1;
  }
  if(me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"hufei"))
  {
	  command("?");
	  command("say 我想起來了，確實叫胡斐，這位大俠不知道我和提起這個幹什麼？");
	  return 1;
  }
  if(me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"liangye"))
  {
	  command("cry");
	  command("say 我是亂中偷盜胡家祕籍，只是當時一片混亂，我全家被毀，我也是為了生計，別無他法。");
	  return 1;
  }
	command("consider");
	command("say 當年冤死的胡大俠的孩子好像叫胡斐，我已經有些忘記了。");
	return 1;
}
int ask_liangyedaofa()
{
	object me = this_player();
	if(me->query_condition("killer"))
	{
	  command("fear "+me->query("id"));
    command("say 小心官府通緝！");
	  return 1;
	}
  if(me->query(QUESTDIR1+"over"))
  {
	  command("fear "+me->query("id"));
	  command("say 我是亂中偷盜胡家祕籍，只是當時一片混亂，我全家被毀，我也是為了生計，別無他法。");
	  command("say 雖然幹了一場荒唐事，天可憐見胡大俠還剩下胡斐這個孩子。我真是後悔啊......");
	  return 1;
  }
  if(me->query(QUESTDIR1+"start")&& !me->query_temp(QUESTDIR1+"hufei") && !me->query_temp(QUESTDIR1+"liangye"))
  {
	  command("?");
	  command("say 我很少用刀的。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"hufei"))
  {
	  command("fear "+me->query("id"));
	  command("say 你，你是怎麼知道的？嘿嘿，看來我只能讓真相永遠消失了。");
	  me->set_temp(QUESTDIR1+"liangye",1);
	  me->delete_temp(QUESTDIR1+"hufei");
	  this_object()->kill_ob(me);
	  me->kill_ob(this_object());
	  this_object()->start_busy(1);
	  me->start_busy(1);
    power_condition(me,this_object(),200+random(100));
    remove_call_out("kill_player");
    call_out("kill_player", 1, me);
  	tell_object(me,RED"\n你不由談了口氣，何必一定兵刃相見......\n"NOR);
	  this_object()->set("quest/try_fight",1);
	  this_object()->set("quest/try_fight_id",me->query("id"));
	  return 1;
  }
 	command("?");
	command("say 我很少用刀的。");
	return 1;
}
int ask_qixinghaitang()
{
	object obj,me = this_player();
  if(me->query(QUESTDIR3+"over"))
  {
	  command("? "+me->query("id"));
	  command("say 不在我這裏了。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& (me->query_temp(QUESTDIR3+"qixinghaitang")||me->query_temp(QUESTDIR3+"jieyao2")))
  {
	  command("sigh "+me->query("id"));
	  command("say 不在我這裏了。");
	  return 1;
  }

  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao1"))
  {
	  command("fear");
	  command("say 是程丫頭讓你來得？哼，能不能拿到要看你的實力了。");
  	tell_object(me,RED"\n你不由皺着眉頭，這廝當真可惡......\n"NOR);
    power_condition(me,this_object(),300+random(50));
	  this_object()->kill_ob(me);
	  me->kill_ob(this_object());
	  this_object()->start_busy(1);
	  me->start_busy(1);
    remove_call_out("kill_player");
    call_out("kill_player", 1, me);
    obj=new(__DIR__"heiyiren");
    obj->set_name("石萬嗔", ({ "shi wanchen", "shi" }));
    obj->set("title",HIR"毒手藥王"NOR);
    obj->set("kill_id",me->query("id"));
    obj->set("type_speical","xx");
    obj->move(environment(me));
  	message_vision(HIC"\n突然從後山竄出一個人來，叫道：別怕，老閻，我來幫你！這小子，純粹找死！\n"NOR,me);
	  this_object()->set("quest/try_fight",1);
	  this_object()->set("quest/try_fight_id",me->query("id"));
	  return 1;
  }

	command("?");
	command("say 我也在尋找七星海棠。");
	return 1;
}
void kill_player(object me)
{
	object ob=this_object();
  if(!me) return;
  if(environment(me)!=environment(this_object())) return;
  if(me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"liangyedaofa"))
  {
     if (!present("blade",ob))
	             carry_object(BINGQI_D("blade"))->wield();
	      else command("wield blade");
    return;
  }
  if(me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"getjieyao1"))
  {
    if (!present("blade",ob))
	             carry_object(BINGQI_D("blade"))->wield();
	      else command("wield blade");
    return;
  }
}

void kill_ob(object me)
{
	 command("sneer " + me->query("id"));
   COMBAT_D->do_attack(this_object(), me, this_object()->query_temp("weapon") );
   COMBAT_D->do_attack(this_object(), me, this_object()->query_temp("weapon") );
   COMBAT_D->do_attack(this_object(), me, this_object()->query_temp("weapon") );
	::kill_ob(me);
}

int do_hit(string arg)
{
         object me,ob;
         me=this_player();
         ob=this_object();
         if((arg==("yan"))||(arg==("yan ji"))){
           	command("sneer");
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	return 1;
         }
         return 0;
}

void unconcious()
{
  die();
}

void die()
{
	object me,obj,ob=this_object();
	if(ob->query("quest/try_fight"))
	{
	  command("ah");
	  if(ob->query("quest/try_fight_id"))
	  {
      remove_call_out("kill_player");
      ob->remove_all_killer();
      start_condition(ob);
	  	me=find_player(ob->query("quest/try_fight_id"));
	    ob->delete("quest/try_fight");
	    ob->delete("quest/try_fight_id");
	  	if(!me) return;
      me->remove_all_killer();
      if(environment(me)!=environment(this_object())) return;
      if(me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"liangye"))
      {

	         command("say 我錯了，我錯了......");
	         command("sorry");
        	 command("say 我是亂中偷盜胡家祕籍，只是當時一片混亂，我全家被毀，我也是為了生計，別無他法。\n");
        	 tell_object(me,HIY"\n"+ob->query("name")+"交給你兩頁紙，上面記載着胡家刀法。\n"NOR);
                 tell_room(environment(me),HIC"閻基好像交給"+me->query("name")+"什麼東西，似乎是兩頁紙張。\n"NOR, ({ me }));
 	         obj=new(__DIR__"obj/paper");
           obj->set("owner",me->query("id"));
 	         obj->move(me);
           tell_object(me,HIC"\n你又詢問了一些當時的情況，閻基當即簡單説起了當時比武的經過......\n"NOR);
           tell_object(me,HIC"\n\n卻説當年比武的第六天，胡一刀之妻竟然發現苗人鳳的劍法破綻，按那劍法，苗人鳳右手一劍斜刺，左手上揚，就與白鶴將\n"
        	                       "雙翅撲開來一般，但胡一刀可以搶了先著，金面佛雙手剛展開之時，被他左右連環兩刀。出乎意料的是豈知金面佛的武功，\n"
        	                       "當真是出神入化，就在這危急之間，他雙臂一曲，劍尖斗然刺向自己胸口。胡一刀大吃一驚，只道他比武輸了，還劍自殺，\n"
        	                       "忙叫道：『"HIR"苗兄，不可"HIC"！』\n"NOR);
                 tell_room(environment(me),HIC"只見，閻基附在"+me->query("name")+"身邊，低聲説着什麼，神色有些恍惚，似乎在回憶着往事，説話有時一頓一頓的。\n"NOR, ({ me }));
        	 command("sigh");
        	 tell_object(me,HIC"\n殊不知金面佛的劍尖在第一日比武之時就已用手指拗斷了的，劍尖本身是鈍頭，他再胸口一運氣，那劍刺在身上，竟然反彈出\n"
        	                     "來。但見長劍一彈，劍柄蹦將出來，正好點在胡一刀胸口的『神藏穴』上，胡一刀登時軟倒。\n\n"NOR);
        	 tell_object(me,HIC"金面佛伸手扶住，叫道：『"HIR"得罪"HIC"！』\n"NOR);
        	 tell_object(me,HIC"胡一刀笑道：『"HIR"苗兄劍法，鬼神莫測，佩服佩服。"HIC"』\n"NOR);
        	 tell_object(me,HIC"金面佛道：『"HIR"若非胡兄好意關心，此招何能得手？"HIC"』\n\n"NOR);
        	 tell_object(me,HIC"兩人坐在桌邊一口氣乾了三碗燒酒。胡一刀哈哈一笑，提起刀來往自己頸中一抹，咽喉中噴出鮮血，伏桌而死。夫人跟着也自殺了。\n\n"NOR);
        	 tell_object(me,HIG"這段往事聽來當真一波三折，你確實沒有料到其中如此曲折，至於兩人相繼自殺更是想不明白。你默然了一會，放開閻基。\n"NOR);
        	 tell_object(me,HIG"你深深地歎了口氣。\n"NOR);
                 tell_room(environment(me),HIC""+me->query("name")+"深深地歎了口氣。\n"NOR, ({ me }));
        }
        if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao1"))
        {
	         command("say 我錯了，我錯了......");
	         command("sorry");
        	 command("say 我還給程丫頭就是，犯不着為這個大打出手。");
        	 tell_object(me,HIW"\n"+ob->query("name")+"交給你一株七星海棠。\n"NOR);
                 tell_room(environment(me),HIC"閻基交給"+ob->query("name")+"一株七星海棠。\n"NOR, ({ me }));
 	         obj=new(__DIR__"obj/qixinghaitang");
           obj->set("owner",me->query("id"));
 	         obj->move(me);
 	         tell_object(me,HIR"\n你上前喝道：“"+ob->query("name")+"，那也不能饒你。”當即內力一鬆，"+ob->query("name")+"竟然暈了過去，你順勢跟上一掌。\n"NOR);
 	         me->delete_temp(QUESTDIR3+"jieyao1");
 	         me->set_temp(QUESTDIR3+"qixinghaitang",1);
 	         tell_room(environment(me),HIC"突然閻基氣血似乎不順，雙腳一軟，徑直癱在地上。\n"NOR, ({ me }));
 	         command("inn "+me->query("id"));
 	         if(obj=present("shi wanchen",environment(me)))
 	         {
 	         	message_vision(HIC"\n$N對$n叫道：“你等着，我馬上去找救兵來！”轉身幾個起落就不見了。\n"NOR,obj,ob);
 	         	command("why "+obj->query("id"));
 	         	destruct(obj);
 	         }
 	         ob->unconcious();
        }
      }
	  }
  else
  {
	command("why");
	::die();
  }
}
int start_condition(object ob)
{
	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("unarmed", 150);
	set_skill("blade",150);
	set_skill("hujia-daofa",150);
	set_skill("huagong-dafa",150);
	map_skill("force","huagong-dafa");
	map_skill("blade","hujia-daofa");
	set("combat_exp", 300000);
	set("max_qi", 3000);
	set("max_jing", 1000);
	set("eff_jingli",1000);
	set("max_neili", 2100);
	set("qi",30000);
	set("jing",1000);
	set("jingli",1000);
	set("neili", 4200);
  return 1;
}
int power_condition(object me,object ob,int p)
{
	  int i;
    if(environment(me)!=environment(ob)) return 0;
    if (!present("blade",ob))
	    carry_object(BINGQI_D("blade"))->wield();
	  else command("wield blade");
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
	  ob->set_skill("xuantian-wuji",i+random(50));
	  ob->set_skill("hujia-daofa",i+random(50));
	  i=me->query("combat_exp");
	  ob->set("combat_exp",i);
	  i=me->query("neili");
	  if(i<12000) i=12000;
	  ob->set("neili", i);
	  i=me->query("max_neili");
	  if(i<6000) i=6000;
	  ob->set("max_neili", i);
  	i=me->query("max_qi");
	  ob->set("max_qi", i*(1+random(2)));
 	  ob->set("eff_qi", ob->query("max_qi"));
 	  ob->set("qi", ob->query("max_qi"));
    return 1;
}

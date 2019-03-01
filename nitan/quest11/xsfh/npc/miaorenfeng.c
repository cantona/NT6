//miaorenfeng.c
//by tangfeng@SJ
//修改雷同hu-fei.c
//增加冷泉神功部分
// Update by lsxk@hsbbs add通寶物品增加解mjjf quest成功幾率 2007/7/20
// By Spiderii@ty 加入天賦

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
#define QUESTDIR5 "quest/雪山飛狐/寶藏/"

void greeting(object me);
void zhenxiang(object me);
void jieshuo1(object me);
void jieshuo2(object me);
void unconcious();
void kill_ob(object me);
int do_hit(string arg);
void do_halt(object me);
void die();
int ask_huyidao();
int ask_biwu();
int ask_zhiliao();
int ask_chuangwang();
int ask_hujiadaofa();
int ask_miaojiajianfa();
int ask_cheng();
int ask_liangyedaofa();
int ask_yanji();
int ask_miaoruolan();
int ask_tian();
int ask_hufei();
int ask_hunjia();
int ask_jiaoliang();
int miao_fight(object me, object ob);
int thinking(object me, object ob);
int killing();
int start_condition(object ob);
int power_condition(object me,object ob,int p);
int busy_pass(object ob);
int skill_check(object me);
int ask_lengquanshengong();

void create()
{
	set_name("苗人鳳", ({ "miao renfeng", "miao", "renfeng" }) );
	set("gender", "男性" );
	set("title", HIY"金面佛"NOR);
	set("age", 56);
	set("long",
	    HIR"苗家莊莊主。號稱“"HIY"打遍天下無敵手"HIR"”\n"NOR);
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
	set("unique", 1);
    set(QUESTDIR4+"miaojiajianfa",1);
    set(QUESTDIR4+"lengquanshengong_teach",1);
    set("no_get", 1);
    set("no_bark", 1);
	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("sword", 300);
	set_skill("cuff",300);
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
	set_skill("lengquan-shengong",300);
	set_skill("miaojia-jianfa",300);
	map_skill("force","lengquan-shengong");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
	map_skill("sword","miaojia-jianfa");
	map_skill("parry","miaojia-jianfa");
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
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
       (: exert_function, "lengquan" :),
       (: perform_action, "sword.duoming" :),
       (: perform_action, "sword.ci" :),
     }));

  set("inquiry", ([
    "婚嫁" : (: ask_hunjia :),
    "結婚" : (: ask_hunjia :),
    "做媒" : (: ask_hunjia :),
    "冷泉神功" : (: ask_lengquanshengong :),
    "lengquan-shengong" : (: ask_lengquanshengong :),
    "胡斐" : (: ask_hufei :),
    "hu fei" : (: ask_hufei :),


    "闖王寶藏" : (: ask_chuangwang :),
    "闖王" : (: ask_chuangwang :),
    "寶藏" : (: ask_chuangwang :),

    "苗家劍法" : (: ask_miaojiajianfa :),
    "miaojia-jianfa" : (: ask_miaojiajianfa :),

    "胡一刀" : (: ask_huyidao :),
    "胡家刀法" : (: ask_hujiadaofa :),
    "刀劍融合" : (: ask_hujiadaofa :),

    "兩頁刀法" : (: ask_liangyedaofa :),
    "較量" : (: ask_jiaoliang :),
    "真相" : (: ask_biwu :),
    "往事" : (: ask_biwu :),
    "20年前" : (: ask_biwu :),
    "20年前的比武" : (: ask_biwu :),
    "比武" : (: ask_biwu :),
    "治療" : (: ask_zhiliao :),
    "苗若蘭" : (: ask_miaoruolan :),
    "解藥" : (: ask_zhiliao :),
    "閻基" : (: ask_yanji :),
    "程靈素" : (: ask_cheng :),
    "田歸農" : (: ask_tian :),
	]));
	setup();
	carry_object("/clone/weapon/sword/sword.c")->wield();
	carry_object("/clone/weapon/sword/sword.c");
	carry_object("/clone/armor/baihu-qiu.c")->wear();
}

void init()
{
  object me;
	::init();
  if (!this_object()->query_temp("biwu")&& interactive(me = this_player()) ) {
  	   me->start_busy(1);
       call_out("greeting", 2, me);
  }
  add_action("do_hit", "hit");
}

void greeting(object me)
{
  object jieyao;
  if(!me) return;
  if(environment(me)!=environment(this_object()))
  {
        if( random(2)) command("?");
        else if( random(2)) command("say");
        else if( random(2)) command("sing");
        else if( random(2)) command("love");
        else if( random(2)) command("addoil");
        else command("xixi");
  	return;
  }
	if(me->query_condition("killer"))
	{
	  command("fear "+me->query("id"));
    command("say 小心官府通緝！");
    me->move(__DIR__"lanzhou");
	  return;
	}
  if(me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"getjieyao"))
  {
  	tell_object(me,HIG"\n你走進大廳，卻看見苗人鳳正面向胡一刀的靈牌發呆，你不由一陣感觸，當年幾多周折，今天也算真相大白。\n"NOR);
    message_vision(HIC"$n似乎是聽到腳步聲，轉頭對$N道："+RANK_D->query_respect(me) +"回來了？\n"NOR,me,this_object());
  	jieyao= present("jie yao", me);
  	if(!jieyao)
  	{
     	tell_object(me,CYN"\n你上前準備將解藥送給了苗人鳳服下，且發現藥物遺失了。\n"NOR);
     	tell_object(me,CYN"怎麼這樣呢？你自是焦急萬分，看來只能再去一次五毒教了。\n"NOR);
	    tell_room(environment(me),HIC"\n"+me->query("name")+"似是上前做什麼，卻發現遺失了什麼，一臉的慌張。\n"NOR, ({}));
    log_file("quest/FEIHU", sprintf("%s(%s) 竟然遺失解藥。失敗。經驗：%d。\n",me->name(1),me->query("id"),me->query("combat_exp")) );
     	me->set_temp(QUESTDIR3+"jieyao2",1);
     	me->delete_temp(QUESTDIR3+"getjiao");
      return;
    }
    else
    {
  	  tell_object(me,HIY"\n你上前將內服藥送給了苗人鳳服下，並幫他將外敷藥附在眼睛上。\n"NOR);
  	  command("thank "+me->query("id"));
	  tell_room(environment(me),HIC"\n"+me->query("name")+"走到苗人鳳跟前，似是在給他敷藥。\n"NOR, ({}));
  	  tell_object(me,HIY"你順手拉過一把椅子，坐在苗大俠位身邊，輕輕地咳了一聲，且不知道從何說起。\n"NOR);
      destruct(jieyao);
      remove_call_out("zhenxiang");
      call_out("zhenxiang", 6, me);
      return;
    }
  }
  if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"kill") && !me->query_temp(QUESTDIR2+"huyidao") && !me->query(QUESTDIR2+"over") && !me->query_temp(QUESTDIR2+"ask_"))
  {
  	command("haha");
	me->start_busy(3);
  	tell_object(me,HIG"\n你剛進大廳，就聽到一陣爽朗的笑聲，“是哪位朋友前來助陣？苗某先是感激了！”你不由胸口一盪。\n"NOR);
  	tell_object(me,HIC"你躊躇了一下，嘴裡回答道：在下"+me->query("name")+"，不過恰巧正過此地，苗大俠可好？\n"NOR);
  	remove_call_out("zhenxiang");
    call_out("zhenxiang", 3, me);
    return;
  }

}
void zhenxiang(object me)
{
	int i,p;
  if(!me) return;
  if(environment(me)!=environment(this_object()))
  {
  	command("chat "+me->name()+"，人呢？怎麼怕我不成?");
  	return;
  }
  if(me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"getjieyao"))
  {
 	  tell_object(me,HIW"\n苗大風不愧為當世高手，一會工夫用內力化開，這眼睛也就好了。你正要感謝，卻聽到苗人鳳嘆道：“當年若不\n"NOR);
  	tell_object(me,HIW"不是一招失手，今日與胡氏夫婦三騎漫遊天下，教貪官惡吏、土豪巨寇，無不心驚膽落，那是何等的快事？”\n"NOR);
  	tell_object(me,HIY"卻聽到苗大俠悲笑起來，聞者無不心酸。所謂英雄豪情不多如此，而可恨天道造化。\n"NOR);
    me->delete_temp(QUESTDIR3+"getjieyao");
    me->set(QUESTDIR3+"over",1);
   	tell_object(me,HIR"你想了一會，也是莫名感嘆。也罷，這故事總算告一段節，你不由長嘆一口氣。\n"NOR);
	p=10+random(10);
        me->add("max_neili",p);
        me->add("combat_exp",me->query_skill("force")+500);
   	i=180+random(40);
   	me->add("mana",i);
    me->set(QUESTDIR+"time",time());
    me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
        tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解開雪山飛狐解藥篇，獲得"+p+"點最大內力、"+((int)me->query_skill("force")+500)+"點經驗獎勵、"+i+"點聲望。\n\n"NOR);
    log_file("quest/FEIHU", sprintf("%s(%s) 解藥篇完成。獎勵：%d點最大內力，%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), p,(me->query_skill("force")+500),i ) );
   	return;
  }
  if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"kill")&& !me->query_temp(QUESTDIR2+"kill_")&& !me->query_temp(QUESTDIR2+"huyidao") && !me->query(QUESTDIR2+"over") )
  {
  	message_vision(HIY"突然$N發現一陣掌風撲面而來，$N驚懼萬分，卻不敢硬接硬架，當下使出師門武功想卸開對方掌力。豈知雙手與$n\n"
  	                  "手掌甫接，登時眼前一黑，胸口氣塞，$N騰騰騰連退三步。$n的掌力只卸去了一半，余一半還是硬接了過來。\n"NOR,me,this_object());
    command("heng");
    if(!me->query("family"))
	{
  	message_vision(HIC"\n$N叫道：“苗大俠，我幫你拿賊……”卻聽$n道：“原來是"+me->query("name")+"。”\n"NOR,me,this_object());
  	message_vision(HIC"$N回答道：“還好，多謝關懷。”卻發現$n雙目突然緊閉，像是毒性發作，$N問道：“苗大俠，現在感覺如何？”\n\n"NOR,me,this_object());
        message_vision(HIC"$N猶豫了一下，沉聲說道：“我與這位"+RANK_D->query_respect(me) +"俗不來往，今天來我苗家莊，怕是有什麼問題吧？”\n\n"NOR,me,this_object());
	}
	else
	{
  	message_vision(HIC"\n$N叫道：“苗大俠，我幫你拿賊……”卻聽$n道：“原來是"+me->query("family/family_name")+"弟子，"+me->query("family/master_name")+"師傅最近可好？”\n"NOR,me,this_object());
  	message_vision(HIC"$N回答道：“還好，多謝關懷。”卻發現$n雙目突然緊閉，像是毒性發作，$N問道：“苗大俠，現在感覺如何？”\n\n"NOR,me,this_object());
        message_vision(HIC"$n猶豫了一下，沉聲說道：“我與"+me->query("family/master_name")+"俗不來往，這位"+RANK_D->query_respect(me) +"且不管我，來我苗家莊，怕是有什麼問題吧？”\n\n"NOR,me,this_object());
	}
    me->set_temp(QUESTDIR2+"kill_",1);
	me->start_busy(3);
    call_out("zhenxiang",3, me);
    return;
  }
  if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"kill")&& !me->query_temp(QUESTDIR2+"huyidao") && !me->query(QUESTDIR2+"over") && me->query_temp(QUESTDIR2+"kill_"))
  {
  	command("say");
  	tell_object(me,HIG"苗人鳳果然心思敏捷，你沉默了一下，腦子裡一邊盤想著如何開口詢問這20年前的故事......\n"NOR);
	  tell_room(environment(me),HIC"\n"+me->query("name")+"似是沉吟不定，好像思考著什麼。\n"NOR, ({}));
    log_file("quest/FEIHU", sprintf("%s(%s) 拜見苗人鳳。經驗：%d。\n",me->name(1),me->query("id"),me->query("combat_exp")) );
    me->set_temp(QUESTDIR2+"ask_",1);
    me->delete_temp(QUESTDIR2+"kill_");
    remove_call_out("zhenxiang");
    return;
  }
}

void kill_ob(object me)
{
	command("sneer " + me->query("id"));
  power_condition(me,this_object(),300+random(100));
  remove_call_out("killing");
	call_out("killing", 2);
	::kill_ob(me);
}

int do_hit(string arg)
{
         object me,ob;
         me=this_player();
         ob=this_object();
         if((arg==("miao"))||(arg==("miao renfeng"))){
           	command("sneer");
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	return 1;
         }
         return 0;
}

int ask_cheng()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("thank");
	  command("say 真的感謝程大醫生，要不是她恐怕我早入黃泉。");
	  return 1;
  }
  command("say 程姑娘，應該就是當年藥王弟子，現在可能身在五毒教吧。");
	return 1;
}

int ask_biwu()
{
	object me = this_player();

  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 20年前的比武，現在已經完全明了。只是可恨胡兄竟然被陰險小人所暗算。");
	  return 1;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"zhenxiang"))
  {
	  command("say 當年我確實和胡一刀比過武，胡兄也確實毒發身亡，但怎麼可能是我忍心下此毒手？這20年來，我也在一直查找兇手。");
	  command("consider");
	  return 1;
  }
 if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"zhenxiang_"))
  {
	  command("say 你聽我說阿，別著急。");
	  return 1;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"huyidao") )
  {
	  command("nod "+me->query("id"));
	  command("say 當年我確實和胡一刀比過武，我們從初識到相交，後來更是同床而眠，徹夜切磋武功，真是好令人懷念。");
	  command("say 只是到第五天上，胡大嫂瞧出我背後的破綻，一聲咳嗽，胡一刀竟然使出八方藏刀式，不及提防將我制住。");
	  tell_object(me,YEL"\n你聽到這裡，感覺和閻基所說不同，不由問道：“那後來呢？難不成胡一刀不是自殺？”\n\n"NOR);
    message_vision(HIC"$N露出疑惑的神色。\n"NOR,me);
	  me->start_busy(3);
	  remove_call_out("jieshuo1");
	  me->set_temp(QUESTDIR2+"zhenxiang_",1);
    call_out("jieshuo1",6, me);
  	return 1;
  }

	command("heng");
	command("say 我號稱打遍天下無敵手，不知你說的是什麼比武？");
	return 1;
}
void jieshuo1(object me)
{
  if(!me) return;
  if(environment(me)!=environment(this_object()))   {
  	command("chat "+me->name()+"，人呢？我正在講故事呢。");
  	return;
  }  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"huyidao"))
  {
    command("consider");
	  command("say 但下一招我當時用的胡家刀法，胡兄用的是苗家劍法，我臨時變招，新創一式，一個措手不及將胡兄所傷。");
	  message_vision(YEL"\n$N驚異的問道：“如果傷勢不是很嚴重，怎麼立刻斃命的呢？”$n聞言道：“刀上有毒。”說著，嘆了口氣。\n"NOR,me,this_object());
	  command("say 而且大嫂竟然也自殺，之後場面很亂，胡兄之子也被亂中砍死，20年來我一直懷疑追查真相，只是沒有任何線索。");
	  remove_call_out("jieshuo2");
    call_out("jieshuo2",6, me);
    return;
  }
}
void jieshuo2(object me)
{
  if(!me) return;
  if(environment(me)!=environment(this_object()))   {
  	command("chat "+me->name()+"，人呢？我正在講故事呢。");
  	return;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"huyidao"))
  {
    command("sigh");
    tell_object(me,HIW"\n你聽完解說一陣沉默，不由被胡與苗的豪情所感動，只怕其中真有別情！你想了一會兒，只有閻基這個線索了！\n"NOR);
    me->delete_temp(QUESTDIR2+"huyidao");
    me->delete_temp(QUESTDIR2+"zhenxiang_",1);
    me->set_temp(QUESTDIR2+"zhenxiang",1);
    return;
  }
}
int ask_miaojiajianfa()
{
	object me = this_player();
	object ob = this_object();
	int i,lv;

  if(!me->query(QUESTDIR3+"over"))
  {
	  command("shake "+me->query("id"));
	  command("sigh");
	  command("say 胡兄大事未了，在下也沒有什麼心思切磋武功了。");
	  return 1;
  }

  if(me->query(QUESTDIR4+"miaojiajianfa")&& me->query("potential")<= 5)
  {
	  command("? "+me->query("id"));
    return 1;
  }

  if(me->query(QUESTDIR4+"miaojiajianfa"))
  {
  	if(me->query("potential")>4)
  	{
      message_vision("$N向$n請教有關苗家劍法的奧妙。\n", me, this_object());
      me->receive_damage("jing", 30);
      tell_object(me,"你聽了苗人鳳的指點，對苗家劍法的奧妙似乎有些心得。\n");
      me->add("potential",-(random(3)+2));
      if( me->query("potential")<0)
        me->set("potential",0);
      me->improve_skill("miaojia-jianfa", 150+random(me->query_int()*2));
      me->improve_skill("sword", random(me->query_int())/2);
       //天賦“領悟大師”影響效果：  by spiderii@ty ..lsxk想法太過變態了
        lv = me->query("max_pot")-100;
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你經過轉世重修後，領悟到了武技萬變不離其宗的道理，瞬間領悟到了苗家劍法的精華所在。\n"NOR);
            me->set_skill("miaojia-jianfa",lv);
            }
    }
    else
    {
      message_vision("$N向$n請教有關苗家劍法的奧妙。\n", me, this_object());
      me->receive_damage("jing", 30);
      tell_object(me,"你聽了苗人鳳的指點，可是還是不能理解。\n");
    }
    return 1;
  }

  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 不是剛學完嗎，還是以後切磋吧。");
	  return 1;
  }
  //非vip玩家，只能失敗三次
  if(me->query(QUESTDIR4+"miaojiajianfa_fail")>=3 && me->query("registered")<3)
  {
	  command("shake "+me->query("id"));
	  command("say 現在時間緊急，這劍法還是以後切磋吧。");
	  return 1;
	}
	//武功學習之間需要間隔一天，經驗需要間隔1M
	//注意這個標記和刀法使用同一個標記。
	if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<86400)
	{
	  command("shake "+me->query("id"));
	  command("say 今天先切磋到這裡吧，明天吧。");
	  return 1;
  }
	if(me->query(QUESTDIR4+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"combat_exp")<500000)
	{
	  command("look "+me->query("id"));
	  command("say 以你當前的經驗恐怕還是難以領悟，還是抓緊去練功去吧。");
	  return 1;
  }
	  command("nod "+me->query("id"));
    message_vision(HIY"\n$n突然運起獨門內功冷泉神功，只感覺劍勢無風自起。\n"NOR, me, ob);
    ob->set_temp("busy",1);
    remove_call_out("busy_pass");
		call_out("busy_pass",600, ob);
    //難度稍微大于刀法，不過關系不大。
    power_condition(me,ob,350+random(150));
    for ( i = 0; i < 6+random(6);i++)
    {
         if (!present(me,environment(ob)) || me->query("qi") <= me->query("max_qi")/20 ||me->query("eff_qi") <= me->query("max_qi")/20 || me->query("jing") <= 50 || me->query("jingli") <= 50)
         {
            if(random(2))command("sneer");
            else if(random(2)) command("say 這位"+RANK_D->query_respect(me) +"武功未能返璞歸真，只怕難以領悟苗家劍法的絕技！");
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
    //標記時間和經驗
    me->set(QUESTDIR4+"time",time());
    me->set(QUESTDIR4+"combat_exp",me->query("combat_exp"));
    ob->delete_temp("quest/雪山飛狐/武功/lengquan");
    start_condition(ob);
    command("haha "+me->query("id"));
    message_vision(HIC"\n\n猶如電光雷閃，一晃數招已過，$n微笑著對$N說道：「剛才我使用的招數可看清楚了？」\n"NOR,me,ob);
    remove_call_out("thinking");
		call_out("thinking",0, me, ob);
    tell_object(me,YEL"你拼命地回憶瞬間交手的一幕，回憶著剛才的招數，你開始認真思索著.........\n"NOR);
    me->start_busy(2);
	  return 1;
}

int thinking(object me, object ob)
{
	int i,p;
	if(!me) return 0;
  if(environment(me)!=environment(ob))
  {
  	start_condition(ob);
    if(random(2)) message_vision(HIC"\n$N伸了伸懶腰，道：$n竟然臨陣逃脫，沒料得蠢材一個。\n"NOR,ob,me);
    else message_vision(HIC"\n$N疑惑問道：夷~~~人呢？$n，人呢？\n"NOR,ob,me);
  	return 1;
  }
  if(!living(me) )
  {
  	ob->revive();
  	ob->reincarnate();
  }
  if(me->query_temp(QUESTDIR4+"thinking")<(3+random(3)))
	{
		me->add_temp(QUESTDIR4+"thinking",1);
    if(random(2)) tell_object(me,HIG"\n你努力地回憶剛才的每一招每一式，似有無數人影交相互動，每一招每一式你都努力去看清楚...\n"NOR);
    else tell_object(me,HIY"\n突然間，你似乎抓到了什麼，你努力地回憶剛才的每一招每一式，你能充分感覺招數的凌厲和急速...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索著什麼，一服愁眉不展的樣子。\n"NOR, ({}));
	  remove_call_out("thinking");
		call_out("thinking",3+random(3), me, ob);
	}
	else
	{
    me->delete_temp(QUESTDIR4+"thinking");

	 //難度降低，畢竟單純的苗家劍法威力一般
   //有特殊通寶物品,提高幾率.
   if(me->query_temp("sj_credit/quest/public/mjjf"))
        p=random(58);
   else
	//沒別的，聽玩家的意見
        p=random(40);
     me->delete_temp("sj_credit/quest/public/mjjf");

    if(!QUEST_D->questing(me, 1, 0, 1)) p = 0;

         if(p > 37&& me->query("kar")<31)
    {
       tell_object(me,HIG"\n你明悟其中，突然間明白了一切。\n"NOR);
       message_vision(HIC"\n$N「哈哈哈」大笑幾聲，說道：“原來如此，原來如此。”\n"NOR,me);
       tell_object(me,HIR"你聽了苗人鳳的指點，對苗家劍法的奧妙似乎有些心得。\n"NOR);
	   if(me->query(QUESTDIR4+"hujiadaofa"))
		    tell_object(me,HIR"你發現苗家劍法如果能夠與胡家刀法相互融合，威力當可加倍。\n"NOR);
       tell_object(me,HIR"只是你發現這苗家劍法還需要冷泉神功才能發揮全效。\n"NOR);
       me->set(QUESTDIR4+"miaojiajianfa",1);
       i=180+random(40);
   	   me->add("mana",i);
  	   tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解開雪山飛狐苗家劍法篇，並獲得"+i+"點聲望。\n\n"NOR);
     log_file("quest/FEIHU", sprintf(HIR"%s(%s) 失敗%d次後揭開苗家劍法,獲得%d點聲望。random（40）取值%d。"NOR, me->name(1),me->query("id"),me->query(QUESTDIR4+"miaojiajianfa_fail"),i,p) );
    }
    else
    {
       tell_object(me,HIG"\n你腦海裡似乎抓住了什麼，可是依然不是很明白。\n"NOR);
       message_vision(HIC"\n$N搖了搖頭，道：“好像還是很困難的。”說罷，深深地嘆了口氣。\n"NOR,me);
       command("poor "+me->query("id"));
       me->add(QUESTDIR4+"miaojiajianfa_fail",1);
	   log_file("quest/FEIHU", sprintf(HIR"%s(%s) 苗家劍法失敗次數：%d次,random（30）取值%d。\n"NOR, me->name(1),me->query("id"),me->query(QUESTDIR4+"miaojiajianfa_fail"),p) );
       if(me->query(QUESTDIR4+"miaojiajianfa_fail")>=3 && me->query("registered")<3)
       {
      	tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"最後一次嘗試揭開雪山飛狐苗家劍法，卻沒有成功。\n\n"NOR);
   		log_file("quest/FEIHU", sprintf("%s(%s) 最後一次嘗試揭開雪山飛狐苗家劍法，卻沒有成功。時間 %s。\n", me->name(1),me->query("id"), ctime(time()) ) );
       }
    }
  }
  return 1;
}
int ask_hujiadaofa()
{
	object me = this_player();
	int i;
  if(this_object()->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 不是剛學完嗎，還是以後切磋吧。");
	  return 1;
  }
  if(me->query(QUESTDIR4+"hujiadaofa") && me->query(QUESTDIR4+"miaojiajianfa") )
  {
  	  //非vip玩家，只能失敗三次
     if(me->query(QUESTDIR4+"ronghe_fail")>=3 && me->query("registered")<3)
     {
	      command("shake "+me->query("id"));
	      command("say 怕是你難以領悟阿。");
	      return 1;
	    }
	   //武功學習之間需要間隔一天，經驗需要間隔1M
	   //注意這個標記和刀法使用同一個標記。
	   if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<86400)
	   {
	     command("shake "+me->query("id"));
	     command("say 今天先切磋到這裡吧，明天吧。");
	     return 1;
     }
     if(me->query(QUESTDIR4+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"combat_exp")<500000)
	   {
	     command("look "+me->query("id"));
	     command("say 以你當前的經驗恐怕還是難以領悟，還是抓緊去練功去吧。");
	     return 1;
     }
  	 command("nod "+me->query("id"));
  	 if(me->query(QUESTDIR4+"ronghe"))
  	 {
      	command("say 你已經刀劍融合，可惜缺少內功支持。傳說：冷泉神功可能在闖王寶藏裡！");
	      return 1;
      }
      me->set(QUESTDIR4+"time",time());
      me->set(QUESTDIR4+"combat_exp",me->query("combat_exp"));
 	    command("say 胡家刀法的確可以與苗家劍法融合，但是需要冷泉神功支持，這裡我可以先教給你融合的口訣！");

 	    //難度也很大，其實這也是這門武功的關鍵
		//這裡增加門檻，不希望每個玩家都能夠學會
		//假設富源random之後取28的話，int隨機應該大于22
		//int 假設25 bili 20的話，con和dex之和35 400等級exp 那麼就是75
      if((random(me->query("kar"))+random(me->query("int")))>50
		  && (random(me->query_con())+random(me->query_dex()))>60
		  && random(me->query("combat_exp"))>2000000
            &&me->query("kar")<31
            &&QUEST_D->questing(me, 1, 0, 1))
      {
           tell_object(me,HIR"你聽了苗人鳳的指點，對苗家劍法和胡家刀法的奧妙似乎更加明白。\n"NOR);
           message_vision(HIC"\n$N當即左刀右劍比劃一招，「哈哈哈」大笑幾聲，說道：“原來如此。”\n"NOR,me);
           me->set(QUESTDIR4+"ronghe",1);
           i=180+random(40);
   	       me->add("mana",i);
  	       tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解開雪山飛狐刀劍融合的奧秘，並獲得"+i+"點聲望。\n\n"NOR);
		   log_file("quest/FEIHU", sprintf(HIR"%s(%s) 失敗%d次後，揭開刀劍融合，獲得%d點聲望。kar%d/int%d/後天con%d/dex%d。\n"NOR, me->name(1),me->query("id"),me->query(QUESTDIR4+"ronghe_fail"),i ,me->query("kar"),me->query("int"),me->query_con(),me->query_dex()) );
       }
       else
       {
           tell_object(me,HIG"\n你聽了苗人鳳的指點，腦海裡似乎抓住了什麼，可是依然不是很明白。\n"NOR);
           message_vision(HIC"\n$N搖了搖頭，道：“好像還是很困難的。”說罷，深深地嘆了口氣。\n"NOR,me);
           command("poor "+me->query("id"));
           me->add(QUESTDIR4+"ronghe_fail",1);
           if(me->query(QUESTDIR4+"ronghe_fail")>=3 && me->query("registered")<3)
           {
          	tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"最後一次嘗試揭開雪山飛狐刀劍融合的奧秘，卻沒有成功。\n\n"NOR);
   		      log_file("quest/FEIHU", sprintf("%s(%s) 最後一次嘗試揭開雪山飛狐刀劍融合的奧秘，卻沒有成功。\n", me->name(1),me->query("id")) );
           }
        }
	  return 1;
  }
  command("nod "+me->query("id"));
  command("say 當年的關東大俠胡一刀曾指點我這路刀法，確實精妙無比！");
	return 1;
}
int ask_huyidao()
{
	object me = this_player();
  if(me->query(QUESTDIR3+"start"))
  {
  	command("cry");
  	command("say 胡一刀，我的好兄弟啊！");
	  return 1;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"huyidao"))
  {
  	command("say 胡一刀，我的好兄弟啊！");
  	return 1;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"kill"))
  {
  	tell_object(me,YEL"苗人鳳突然看起來蒼老了很多，不知沉默了多久，才緩緩嘆了口氣。\n"NOR);
    command("nod "+me->query("id"));
    command("say 關東大俠胡一刀正是我的至交好友啊！不知道這位"+RANK_D->query_respect(me) +"為什麼提起他？");
    me->set_temp(QUESTDIR2+"huyidao",1);
    me->delete_temp(QUESTDIR2+"kill_ren");
    me->delete_temp(QUESTDIR2+"kill_");
  	return 1;
  }
  command("nod "+me->query("id"));
  command("say 關東大俠胡一刀正是我的至交好友，你找他什麼事情！");
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
  if(!me->query(QUESTDIR3+"over"))
  {
	  command("shake "+me->query("id"));
	  command("sigh");
	  command("say 在下現在沒有什麼心思切磋武功了。");
	  return 1;
  }
  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 在下現在沒有什麼心思切磋武功了。");
	  return 1;
  }
    //普通玩家三次,
   if(me->query(QUESTDIR4+"fight_miao")>=3 && me->query("registered")<3)
  {
	  command("shrug "+me->query("id"));
	  command("say 天色不早了，這劍法還是以後切磋吧。");
	  return 1;
	}

	//較量增加時間間隔1個小時。
    if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<(3600*3))
	{
	  command("shake "+me->query("id"));
	  command("say 今天先切磋到這裡吧，稍後吧。");
	  return 1;
  }
	if((me->query(QUESTDIR4+"fight_miao")>=3 && me->query(QUESTDIR4+"fight_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"fight_exp")<500000)
		||(me->query(QUESTDIR4+"fight_miao")<3 && me->query(QUESTDIR4+"fight_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"fight_exp")<100000))
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
	  command("nod "+me->query("id"));
    message_vision(HIY"\n$n突然運起獨門內功冷泉神功，只感覺劍勢無風自起。\n"NOR, me, this_object());

    //玩家最好武功在400等級以上，縱然如此還是比較危險。
    power_condition(me,ob,300+random(200));
    if (!(room = find_object("/d/lanzhou/lianwuchang")))
        room = load_object("/d/lanzhou/lianwuchang");
    if( !room )
 	  {
	     command("shake "+me->query("id"));
	     command("say 暫時沒有空余的場地較量，稍後吧，或者通知巫師一下。");
	     return 1;
    }
    if(room->query_temp("biwu"))
 	  {
	     command("shake "+me->query("id"));
	     command("say 暫時沒有空余的場地較量，稍後吧，或者通知巫師一下。");
	     return 1;
    }

    //標志
    me->set(QUESTDIR4+"time",time());
	me->set(QUESTDIR4+"fight_exp",me->query("combat_exp"));
    me->set_temp(QUESTDIR4+"fight_id",ob->query("id"));
	me->add(QUESTDIR4+"fight_miao",1);
    ob->set_temp("busy",1);
    ob->set_temp("biwu",1);
	  ob->set_temp("quest/try_fight_id",me->query("id"));

    message_vision(HIY"$N向$n一招手道：“"+RANK_D->query_respect(me) +"且隨我來”，$N和$n急急忙忙地離開墳地。\n"NOR, ob,me);
    ob->move(room);
    me->move(room);
    message_vision(YEL"$N急急忙忙地來到練武場。\n"NOR, ob);
    message_vision(YEL"$N急急忙忙地來到練武場。\n"NOR, me);
	  command("sneer");
    remove_call_out("busy_pass");
		call_out("busy_pass",600, ob);
    log_file("quest/FEIHU", sprintf("%s(%s) 再次與苗人鳳較量。經驗：%d。\n",me->name(1),me->query("id"),me->query("combat_exp")) );
    me->start_busy(1);
    ob->start_busy(1);
	  return 1;
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

  if (!present("changjian",ob))
  {
	  message_vision(HIR"\n$N身行向後一躍，不知道從哪裡竟然又拿出一把鋼劍。\n"NOR,ob);
  	carry_object(BINGQI_D("sword"))->wield();
  }
	else command("wield changjian");
  i=ob->query_temp("pfm");

  //zongjue 無用
  if(ob->query_skill_mapped("sword") != "miaojia-jianfa")
  {
	  ob->map_skill("sword","miaojia-jianfa");
	  ob->map_skill("parry","miaojia-jianfa");
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
            message_vision(HIW"\n$N"HIW"輕舒猿臂，手中的長劍吞吞吐吐，變化莫測，籠罩了$n"HIW"周身要害！\n" NOR, this_object(),me);
            if(random(3) && !me->query_busy())
            {
            	message_vision(HIC"$n見來招實在是變幻莫測，不由得心生懼意，招式登時出了破綻！\n" NOR, this_object(),me);
              me->add_busy(1+random(4));
            }
            break;
     	case 1:
     		  message_vision(HIR"\n$N手中的長劍幻出漫天劍影，雷霆霹靂般的擊向$n！\n" NOR, this_object(),me);
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
int ask_liangyedaofa()
{
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
 	command("doubt");
	command("say 誰？我認識嗎？");
	command("consider");
	return 1;
}
int ask_zhiliao()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("say 需要治療可以尋找程姑娘，確實高手。我也多謝她了。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start"))
  {
	  command("sigh "+me->query("id"));
	  command("say 如此說來，治療我這毒，怕是只有程靈素了。");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  tell_object(me,HIW"你也將真相告訴苗人鳳，顯然現在不是悲傷的時候，這毒性越發得厲害。你說服苗人鳳，親自上前仔細觀察中毒症狀。\n\n"NOR);
	  tell_object(me,CYN"你說道：“苗大俠眼中所染的毒藥，乃是斷腸草的粉末，只怕是從毒手藥王那裡得來的。”說話期間，苗人鳳已經痛楚不忍。\n"NOR);
	  tell_object(me,CYN"苗人鳳聽道：“恩，如此說來，要治這毒只有藥王谷的人了”你點了點頭，當前之急還是趕快尋找程靈素，這毒看似好兇猛。\n\n"NOR);
	  tell_object(me,CYN"苗人鳳聽言，停頓了一下：“現在藥王谷就在苗疆之內，那就拜托"+RANK_D->query_respect(me) +"走一趟了。只是聽說藥王谷的人......”\n"NOR);
	  command("sigh");
	  tell_object(me,HIC"\n你當即說道：“咱們好歹也得將他請到，他要什麼便給他什麼。我這就去一趟苗疆藥王谷。”\n"NOR);
	  command("addoil "+me->query("id"));
	  me->set(QUESTDIR3+"start",1);
	  return 1;
  }
  command("say 藥王的唯一親傳弟子，前段時間藥王病逝，恐怕藥術一派只有這程靈素程姑娘的天地了。");
	return 1;
}
int ask_miaoruolan()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"marry"))
  {
	  command("say 小女苗若蘭這工夫只怕和胡斐那孩子在一起吧。");
	  return 1;
  }
	command("? "+me->query("id"));
	command("say 那是小女，不知你找她有何事？");
	return 1;
}
int ask_hufei()
{
	object me = this_player();

	if(me->query(QUESTDIR3+"marry"))
  {
	  command("say 現在只怕和小女苗若蘭在一起吧。天可憐見胡家一脈啊！");
	  return 1;
  }

  if(me->query(QUESTDIR3+"start"))
  {
	  command("say 天可憐見胡家一脈啊！胡兄九泉之下也可瞑目了。");
	  return 1;
  }
	command("say 胡兄之子的名字正是這胡斐，可惜當年一場大亂，被亂刀砍死了。");
	command("sigh");
	command("say 好後悔未能照顧胡兄唯一之子啊！");
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
  if(me->query(QUESTDIR3+"start"))
  {
	  command("heng");
	  command("say 確實沒有想到事情如此復雜。天龍門現在一門盡亡，也算是天網恢恢阿。");
	  return 1;
  }
	command("say 上任天龍門掌門，很久不知下落了。現在天龍門大不如以前了。");
	return 1;
}
int ask_hunjia()
{
	object obj,me = this_player();
  if(me->query(QUESTDIR3+"marry"))
  {
	  command("haha");
	  command("say 苗胡兩家恩怨終得圓滿啊。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"over"))
  {
  	tell_object(me,CYN"你說道：苗大俠，你可知道你家苗大姑娘和雪山飛狐胡斐情投意合這碼子事情？\n"NOR);
	  command("say 不知是真是假，如此甚好，哈哈，苗胡兩家恩怨終得圓滿啊。");
	  command("haha");
	  command("say 這位"+RANK_D->query_respect(me) +"為胡苗兩家出盡大力，不慎感激啊。無以為報，這是我一點心意，還請收下！");
	  me->set(QUESTDIR3+"marry",1);
	  obj=new("/clone/medicine/renshen-guo");
	  command("give "+obj->query("id")+" to "+me->query("id"));

	  if(!present(obj,me)) obj->move(me);
	  return 1;
  }
	command("say 這事和我說來無用，小女自有自己主張。");
	return 1;
}
int ask_chuangwang()
{
        object me,obj;
        me = this_player();
  if(me->query(QUESTDIR3+"over")&& !present("baozang tu",me))
  {
	if(!me->query(QUESTDIR4+"win_miao") && (me->query(QUESTDIR4+"fight_miao")<3 || random(4)))
    {
	      command("look "+me->query("id"));
	      command("say 你連我都贏不了，如何獨力尋找寶藏。我這也算是為了你好。");
	      command("pat "+me->query("id"));
	      command("say 你還是抓緊時間練功去吧。");
	      return 1;
    }
	if(!me->query(QUESTDIR4+"win_hu") && (me->query(QUESTDIR4+"fight_hu")<3 || random(4)))
    {
	      command("look "+me->query("id"));
	      command("say 你連胡斐都贏不了，如何獨力尋找寶藏。我這也算是為了你好。");
	      command("pat "+me->query("id"));
	      command("say 你還是抓緊時間練功去吧。");
	      return 1;
    }
	if(!random(10))
	{
	    if(random(2))
		{
			command("consider");
			command("say 寶藏圖在哪裡呢。");
			if(random(2)) command("pat "+me->query("id"));
			else command("papaya");
			command("addoil");
			return 1;
		}
		else if(random(2))
		{
			command("consider");
			command("say 剛才還在這裡啊。我再找找看。");
			command("papaya");
			return 1;
		}
		else if(random(2))
		{
			command("consider");
			command("say 寶藏圖.....寶什麼來著，啊，我忘記了。");
			command("pat "+me->query("id"));
			command("say 這樣吧，你還是抓緊時間練功去吧，過一會再來問吧，我這就找找看。");
			command("addoil "+me->query("id"));
			return 1;
		}
		else
		{
			command("?");
			command("makeup");
			command("say 啊呀，你久等了，你要什麼來著？");
			command("say 這樣吧，你還是抓緊時間練功去吧，過一會再來問吧，我這就找找看。");
			command("addoil "+me->query("id"));
			return 1;
		}
	}
	obj=unew("/d/lanzhou/obj/map");

	if(!clonep(obj)){
	      command("pat");
	      command("say 寶藏圖不在我這裡，真是老了糊塗了。");
	      command("pat "+me->query("id"));
	      command("say 這樣吧，你還是抓緊時間練功去吧，過一會再來問吧，我這就找找看。");
	      command("addoil "+me->query("id"));
		  return 1;
	}

	if(clonep(obj) && obj->violate_unique()){
	  	  if(objectp(environment(obj))) tell_object(environment(obj),HIC""+obj->query("name")+"被一陣風刮走了。\n"NOR, ({}));
		  destruct(obj);
	      command("pat");
	      command("say 寶藏圖不在我這裡，真是老了糊塗了。");
	      command("pat "+me->query("id"));
	      command("say 這樣吧，你還是抓緊時間練功去吧，過一會再來問吧，我這就找找看。");
	      command("addoil "+me->query("id"));
		  return 1;
	}
  	tell_object(me,HIR"苗人鳳偷偷告訴你："HIG"當年闖王破了北京之後，明朝的皇親國戚、大臣大將盡數投降。這些人無不家資豪富，闖王部下的將領\n"NOR);
  	tell_object(me,HIG"數日之間，財寶山積，那裡數得清了。後來闖王退出北京，派了親信將領，逼他們獻出金銀珠寶贖命。押著財寶去藏在一個極\n"NOR);
  	tell_object(me,HIG"穩妥的所在，以便將來卷土重來之時作為軍餉。他將藏寶的所在繪成一圖，而看圖尋寶的關鍵，卻置在軍刀之中。九宮山兵敗\n"NOR);
  	tell_object(me,HIG"逃亡，闖王將寶藏之圖與軍刀都交給了飛天狐貍。後來飛天狐貍被殺，一圖一刀落入三位義弟手中，但不久又被飛天狐貍的兒\n"NOR);
  	tell_object(me,HIG"子奪去。百年來輾轉爭奪，終于軍刀由天龍門田氏掌管，藏寶之圖卻由我苗家家傳。只是苗田兩家不知其中有這樣一個大秘密，\n"NOR);
  	tell_object(me,HIG"是以沒去發掘寶藏。這秘密由胡家世代相傳，可是姓胡的沒軍刀地圖，自也無法找到寶藏。是胡大哥將這事告知我的，請我去\n"NOR);
  	tell_object(me,HIG"掘出寶藏，救濟天下窮人。其實這個秘密到今天早已經公開，今天告訴了你，你大可去尋找一下這個寶藏。這便是藏寶圖，至\n"NOR);
  	tell_object(me,HIG"于藏寶的秘密你還是去自己挖掘吧。\n"NOR);
    tell_object(me,HIR"\n苗人鳳偷偷告訴你："HIG"探險的時候，一定要注意安全，帶好藥物，另外類似繩子、火折等常備工具不要遺漏。\n"NOR);
    command("smile");
    tell_object(me,HIR"\n苗人鳳交給你一張寶藏圖。\n"NOR);
    command("addoil");
    obj->set("owner",me->query("id"));
    obj->move(me);
    log_file("quest/FEIHU", sprintf("%s(%s) 獲得寶藏圖。經驗：%d。\n",me->name(1),me->query("id"),me->query("combat_exp")) );
    me->set(QUESTDIR+"寶藏/start",1);
	return 1;
  }
	command("say 李闖王當年確實威震朝野，可惜時不逢時，也聽說留有一大寶藏，不知道是真是假。");
	return 1;
}
int start_condition(object ob)
{
	 if(!ob) return 0;
   ob->set_skill("force", 300);
	 ob->set_skill("dodge", 300);
	 ob->set_skill("parry", 300);
	 ob->set_skill("sword", 300);
	 ob->set_skill("cuff",300);
	 ob->set_skill("taxue-wuhen",300);
	 ob->set_skill("zhentian-quan",300);
	 ob->set_skill("lengquan-shengong",300);
	 ob->set_skill("miaojia-jianfa",300);
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
    if (!present("changjian",ob))
	    carry_object(BINGQI_D("sword"))->wield();
	  else command("wield changjian");
    ob->set_temp("quest/雪山飛狐/武功/lengquan",1);
	  i=me->query("max_pot");
	  if(p<150) p=150;
	  if(i<p) i=p;
	  i=i-100;
	  ob->set_skill("force", i+random(50));
	  ob->set_skill("dodge", i+random(50));
	  ob->set_skill("parry", i+random(50));
	  ob->set_skill("sword", i+random(50));
	  ob->set_skill("cuff",i+random(50));
	  ob->set_skill("taxue-wuhen",i+random(50));
	  ob->set_skill("zhentian-quan",i+random(50));
	  ob->set_skill("lengquan-shengong",i+random(50));
	  ob->set_skill("miaojia-jianfa",i+random(50));
	  i=me->query("combat_exp");
	  ob->set("combat_exp",i);
	  i=me->query("neili");
	  if(i<15000) i=15000;
	  ob->set("neili", i);
	  i=me->query("max_neili");
	  if(i<8000) i=8000;
	  ob->set("max_neili", i);
	  ob->set("jiali",200);
  	i=me->query("max_qi");
          ob->set("max_qi", i*(6+random(3))/4);
 	  ob->set("eff_qi", ob->query("max_qi"));
 	  ob->set("qi", ob->query("max_qi"));
    return 1;
}
int busy_pass(object ob)
{
	if(!ob) return 0;
	if(ob->query_temp("busy")) ob->delete_temp("busy");
	if(ob->query("busy")) ob->delete("busy");
  if(random(2)) message_vision(HIC"\n$N打了個哈氣。\n"NOR,ob);
  else if (random(2)) message_vision(HIC"\n$N皺了皺眉頭。\n"NOR,ob);
  else message_vision(HIC"\n$N伸了伸懶腰。\n"NOR,ob);
  return 1;
}

int accept_object(object who, object ob,object me)
{

	 if(ob->query("id")=="yu pei"&&ob->query("quest")&&ob->query("owner")==who->query("id"))
   {
     if(who->query(QUESTDIR4+"lengquanshengong") && !who->query(QUESTDIR4+"lengquanshengong_teach"))
     {
     	command("ah "+(string)who->query("id"));
     	command("whisper "+(string)who->query("id")+" 這是我爹爹的東西？你從哪裡得來的？");
        tell_object(who,CYN"\n你在苗人鳳的耳邊悄聲說道：我剛才去過闖王寶藏，在那裡撿到的。\n"NOR);
     	who->set_temp(QUESTDIR4+"lengquanshengong_teach",1);
     	command("hehe");
     	command("say 30年前，田安豹與我爹爹結伴同去關外，當時我們不知為了何事，但見他二人興高採烈，歡歡喜喜而去，可是從此不見歸來。");
     	command("say 武林中朋友後來傳言，說道他們兩位為胡一刀所害，所以我與田師弟才大舉向胡一刀尋仇，那知道這一切全是誤會，全錯了！");
     	who->start_busy(1);
     }
     else  command("thank "+(string)who->query("id"));
     call_out("destroying", 1, ob);
     return 1;
   }
    else
     command("? "+(string)who->query("id"));
   return 0;
}
void destroying(object obj)
{
        if(!userp(obj)) destruct(obj);
        return;
}
int ask_lengquanshengong()
{      int lv;
	object me = this_player();
       lv = me->query("max_pot")-100;
  if(me->query(QUESTDIR4+"lengquanshengong_teach"))
  {
  	if(me->query("potential")>4)
  	{
      message_vision("$N向$n請教有關冷泉神功的奧妙。\n", me, this_object());
      me->receive_damage("jing", 30);
      if(skill_check(me))
      {
          tell_object(me,HIC"你聽了苗人鳳的指點，可是領悟起來速度極慢。\n"NOR);
          tell_object(me,HIC"也許是因為其他內功的幹擾，無法全心領悟冷泉神功。\n"NOR);
        me->add("potential",-(random(3)+3));
        if( me->query("potential")<0)
            me->set("potential",0);
        me->improve_skill("lengquan-shengong", 10+random(me->query_int()/2));
      }
      else
      {
        tell_object(me,"你聽了苗人鳳的指點，對冷泉神功的奧妙似乎有些心得。\n");
        me->add("potential",-(random(3)+2));
        if( me->query("potential")<0)
            me->set("potential",0);
        me->improve_skill("lengquan-shengong", 150+random(me->query_int()*2));
        me->improve_skill("force", random(me->query_int())/2);
      }
        //天賦“領悟大師”影響效果：  by spiderii@ty ..lsxk想法太過變態了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你經過轉世重修後，領悟到了武技萬變不離其宗的道理，瞬間領悟到了冷泉神功的精華所在。\n"NOR);
            me->set_skill("lengquan-shengong",lv);
            }
    }
    else
    {
      message_vision("$N向$n請教有關冷泉神功的奧妙。\n", me, this_object());
      tell_object(me,"你聽了苗人鳳的指點，可是還是不能理解。\n");
    }
    return 1;
  }
  if(me->query_temp(QUESTDIR4+"lengquanshengong_teach"))
  {
	  command("nod "+me->query("id"));
	  command("say 這位"+RANK_D->query_respect(me) +"對我有多次大恩。也罷，這門神功也傳給你吧。");

    message_vision(HIR"$N向$n請教有關冷泉神功的奧妙。\n"NOR, me, this_object());
    me->receive_damage("jing", 30);
    if(skill_check(me))
    {
        tell_object(me,HIC"你聽了苗人鳳的指點，可是總感覺領悟起來極其困難。\n"NOR);
      tell_object(me,HIC"也許是因為其他內功的幹擾，無法全心領悟冷泉神功。\n"NOR);
      me->improve_skill("lengquan-shengong", random(me->query_int()*2/3));
      me->delete_temp(QUESTDIR4+"lengquanshengong_teach");
      me->set(QUESTDIR4+"lengquanshengong_teach",1);
    }
    else
    {
    	tell_object(me,"你聽了苗人鳳的指點，對冷泉神功的奧妙似乎有些心得。\n");
      me->improve_skill("lengquan-shengong", 10+random(me->query_int()));
      me->improve_skill("force", random(me->query_int())/2);
      me->delete_temp(QUESTDIR4+"lengquanshengong_teach");
      me->set(QUESTDIR4+"lengquanshengong_teach",1);
    }
    return 1;
  }
  if(me->query(QUESTDIR4+"hujiadaofa")||me->query(QUESTDIR4+"hujiadaofa"))
  {
	  command("nod "+me->query("id"));
	  command("say 冷泉神功是胡家刀和苗家劍的基礎內功，也只有冷泉神功才能最大限度發揮刀劍的威力。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"over"))
  {
	  command("nod "+me->query("id"));
	  command("say 冷泉神功是闖王時期四大護衛的招牌功夫，這門武功也是我苗家武功的基礎。");
	  return 1;
  }
	command("hehe");
	command("say 我號稱打遍天下無敵手，靠的就是這身武功。");
	return 1;
}
int skill_check(object me)
{
	int i,p;
	mapping skill_status;
  string *sname;
  p=0;
  if(mapp(skill_status=me->query_skills()))
	{
		skill_status=me->query_skills();
    sname = keys(skill_status);
	  for(i=0; i < sizeof(skill_status); i++)
   	  if(SKILL_D(sname[i])->valid_enable("force")&&sname[i]!="lengquan-shengong") p=1;
  }
	return p;
}

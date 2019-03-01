//yangtiexin.c

inherit NPC;
#include <ansi.h>
int ask_yangjiaqiang();
#define QUESTDIR "quest/射雕英雄傳/風雪驚變/"
#define QUESTDIR6 "quest/射雕英雄傳/yangjiaqiang/"

void greeting(object me);

void create()
{
	set_name("楊鐵心", ({ "yang tiexin", "yang", "tiexin" }) );
	set("gender", "男性" );
	set("nickname",HIY"楊家槍傳人"NOR);
	set("age", 27);
	set("long",
"一個白凈面皮的漢子。\n"
"他是岳飛麾下名將楊再興的後代。\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
  set("no_get", 1);
  set("no_bark", 1);
	set_skill("force", 200);
	set_skill("dodge", 200);
	set_skill("parry", 200);
	set_skill("spear", 200);
	set_skill("cuff",200); 
	set_skill("jinyan-gong",200);
	set_skill("taizu-quan",200);
	set_skill("xiantian-gong",200);
	set_skill("yangjia-qiang",200);
	map_skill("force","xiantian-gong");
	map_skill("cuff","taizu-quan");
	map_skill("dodge","jinyan-gong");
	map_skill("spear","yangjia-qiang");
	map_skill("parry","yangjia-qiang");
    prepare_skill("cuff", "taizu-quan");
	set("combat_exp", 1000000);
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
       (: exert_function, "wuqi" :),
       (: perform_action, "spear.tiaoji" :),
       (: perform_action, "spear.shanji" :),
     }));

  set("inquiry", ([
    "楊家槍": (: ask_yangjiaqiang :),
    "郭嘯天" : "他是我義兄。",
    "包惜弱" : "她是我渾家。",
    "楊康" : "這是一個道人給我未出世的兒女取的名字。",
    "郭靖" : "這是我義兄郭嘯天的骨肉。",
    "李萍" : "她是我嫂子",
	]));
	setup();
	carry_object("/clone/weapon/spear.c")->wield();
	carry_object("/clone/weapon/spear.c");
	carry_object("/clone/armor/cloth.c")->wear();
} 

void init()
{
  object me;
	::init();
  if (interactive(me = this_player()) ) {
  	   me->start_busy(1);
       call_out("greeting", 2, me);
  }       
}

void greeting(object me)
{
		int i,p;
  if(!me) return;

	if(me->query_condition("killer"))
	{
	  command("fear "+me->query("id"));
    command("say 小心官府通緝！");
    me->move(__DIR__"njroad3");
	  return;
	}

  if(me->query(QUESTDIR+"start") && !me->query(QUESTDIR+"over"))
  {
	me->start_busy(3);
  	tell_object(me,HIG"\n你突然發現後院柵欄處站著一個人，那人說道：“感謝這位大俠出手援助。”\n"NOR);
  	tell_object(me,HIC"你躊躇了一下，楊鐵心說道："+me->query("name")+"，為感謝您救我一家，我可將聞名遐邇的楊家槍教授于你，你可以隨時找我請教？\n"NOR);
  	me->delete(QUESTDIR+"start");
  	me->delete_temp(QUESTDIR+"kill");
  	me->set(QUESTDIR+"over",1);
  	p=10+random(10);
    me->add("max_neili",p);
    me->add("combat_exp",me->query_skill("force")+500);
    me->set("quest/射雕英雄傳/time",time());
		me->set("quest/射雕英雄傳/combat_exp",me->query("combat_exp"));
    i=180+random(40);
   	me->add("mana",i);
  	tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解開射雕英雄傳風雪驚變篇，獲得"+p+"點最大內力、"+((int)me->query_skill("force")+500)+"點經驗獎勵、"+i+"點聲望。\n\n"NOR); 
    log_file("quest/SheDiao", sprintf("%s(%s) 風雪驚變完成。獎勵：%d點最大內力，%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), p,(me->query_skill("force")+500),i ) );

    return;
  }  	

}


int ask_yangjiaqiang() 
{
	object me = this_player();
	object ob = this_object();
   
if(me->query(QUESTDIR6+"pass"))
  {
	  command("disapp "+me->query("id"));
	  command("say 你不學已經學會楊家槍了嗎。");
	  return 1;
  } 
    
 //武功學習之間需要間隔一天，經驗需要間隔500K
	if(me->query(QUESTDIR6+"time") && time()-me->query(QUESTDIR6+"time")<86400)
	{
	  command("shake "+me->query("id"));
	  command("say 今天先切磋到這裡吧，明天吧。");
	  return 1;
  }
   if(me->query(QUESTDIR6+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR6+"combat_exp")<100000)
	{
	  command("look "+me->query("id"));
	  command("say 以你當前的經驗恐怕還是難以領悟，還是抓緊去練功去吧。");
	  return 1;
  }
  
  if(me->query(QUESTDIR+"over") > 0)
    {
    command("pat "+me->query("id"));
    message_vision(HIC"\n$n微笑著對$N說道：「可要看仔細了!」,伸手拿起牆上的鐵槍舞動起來\n"NOR,me,ob); 
    me->set(QUESTDIR6+"time",time());
    me->set(QUESTDIR6+"combat_exp",me->query("combat_exp"));
    remove_call_out("thinking");
		call_out("thinking",5, me, ob);
    tell_object(me,YEL"你拼命地回憶楊鐵心舞動的鐵槍招式，你開始認真思索著.........\n"NOR);
    me->start_busy(2);
	  return 1;
	  }
	  else
	 {  
	  command("? "+me->query("id"));
         command("say 你問這個做什麼?");
    return 1;
  }
}

int thinking(object me, object ob)
{
	int p;
	if(!me) return 0;
	
  if(me->query_temp("yjq_thinking")<(3+random(3)))
	{
		me->add_temp("yjq_thinking",1);
    if(random(2)) tell_object(me,HIG"\n你努力地回憶剛才楊鐵心鐵槍的招式,只覺得眼花繚亂...\n"NOR);
    else tell_object(me,HIY"\n突然間，你似乎抓到了什麼，你努力地回憶剛才楊鐵心鐵槍的招式，你似乎感覺到了其中的變化所在...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索著什麼，一服愁眉不展的樣子。\n"NOR, ({}));
	  remove_call_out("thinking");
		call_out("thinking",3+random(3), me, ob);
	}
	else
	{
    me->delete_temp("yjq_thinking");

     p=random(15);

       if(p = 3 &&  random(me->query("kar"))>28  && me->query("pur")>25  && me->query("kar")<31 )
    {
       tell_object(me,HIG"\n你此時生怕將剛才的精妙招式忘了，當即跟著楊鐵心的招式比劃著。\n"NOR);
       message_vision(HIC"\n$N「哈哈哈」大笑幾聲，說道：“原來如此，原來如此。”\n"NOR,me); 
       tell_object(me,HIR"你聽了楊鐵心的指點,終于領悟了楊家槍的精華所在。\n"NOR);
       me->set(QUESTDIR6+"pass",1);
       me->set_skill("yangjia-qiang",11);
       message_vision(HIC"\n你的「楊家槍」進步了！”\n"NOR,me); 
	log_file("quest/SheDiao", sprintf("%s(%s) 失敗%d次成功解開楊家槍。富源：%d；經驗：%d。", me->name(1),me->query("id"), me->query(QUESTDIR6+"fail"),me->query("kar"),me->query("combat_exp")) );
    }
    else
    {
       tell_object(me,HIG"\n你腦海裡似乎抓住了什麼，可是依然不是很明白。\n"NOR);
       message_vision(HIC"\n$N搖了搖頭，道：“好像還是很困難的。”說罷，深深地嘆了口氣。\n"NOR,me); 
       command("poor "+me->query("id"));
       me->add(QUESTDIR6+"fail",1);
	log_file("quest/SheDiao", sprintf("%s(%s) 解楊家槍：%d次。富源：%d；經驗：%d。", me->name(1),me->query("id"), me->query(QUESTDIR6+"fail"),me->query("kar"),me->query("combat_exp")) );
    }
  }
  return 1;
}

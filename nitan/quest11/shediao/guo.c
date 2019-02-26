//ytx.c

inherit NPC;
#include <ansi.h>
int ask_jiuyuan();
#define QUESTDIR "quest/射鵰英雄傳/"

void greeting(object me);

void create()
{
	set_name("郭嘯天", ({ "guo xiaotian", "guo", "xiaotian" }) );
	set("gender", "男性" );
	set("title", HIC"大俠"NOR);
	set("nickname", HIC"北俠郭靖之父"NOR);
	set("age", 28);
	set("long",
"他身材魁梧，濃眉大眼。\n"
"他是梁山泊好漢地佑星賽仁貴郭盛的後代。\n");
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
	set_skill("cuff",200); 
	set_skill("jinyan-gong",200);
	set_skill("taizu-quan",200);
	set_skill("xiantian-gong",200);
	map_skill("force","xiantian-gong");
	map_skill("cuff","taizu-quan");
	map_skill("dodge","jinyan-gong");
  prepare_skill("cuff", "taizu-quan");
    
	set("combat_exp", 1000000);
	set("max_qi", 30000);
	set("max_jing", 30000);
	set("max_neili", 50000);
	set("eff_jingli",30000);
	set("qi",30000);
	set("jing",30000);
	set("jingli",30000);
	set("neili", 50000);

  set("inquiry", ([
    "救援": (: ask_jiuyuan :),
		"楊鐵心": "他是我義弟。",
    "李萍" : "她是我渾家。",
    "郭靖" : "這是一個道人給我未出世的兒女取的名字。",
    "楊康" : "這是我義弟楊鐵心的骨肉。",
    "包惜弱" : "她是我弟媳。",

	]));
	set("chat_chance", 10);
        set("chat_msg", ({
		"村裏不怎麼的出現大批金兵，這到底是發生了什麼事情、、、\n",
		"內子和弟媳快要生了，這節骨眼上怎麼會發生這種事情呢、、、\n",
        }) );
     setup();
	carry_object("/clone/armor/cloth.c")->wear();
	carry_object(ARMOR_D("shoes"))->wear();
} 

int ask_jiuyuan()
{
	object me = this_player();

	if(me->query(QUESTDIR+"start"))
		  {
	  command("beg1 "+me->query("id"));
		command("say 這位"+RANK_D->query_respect(this_player())+"，快去救我義弟啊，要不他頂不住了？");
			  return 1;
  } 
	if(me->query(QUESTDIR+"over"))
				  {
	  command("beg1 "+me->query("id"));
		command("say 多謝這位"+RANK_D->query_respect(this_player())+"出手救我義弟呀？");		
					  return 1;
  } 
  if( me->query("combat_exp") < 2000000 )
        	{
	  command("disapp "+me->query("id"));
		command("say 以你當前的經驗恐怕還不能幫忙救援我義弟，還是抓緊去練功去吧。\n");
       			  return 1;
  }  	
  if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<86400)
	{
	  command("shake "+me->query("id"));
	  command("say 今天先幫到這裏吧，明天吧。");
	  return 1;
  }
   if(me->query(QUESTDIR+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<100000)
	{
	  command("look "+me->query("id"));
	  command("say 以你當前的經驗恐怕還是無法幫忙，還是抓緊去練功去吧。");
	  return 1;
  }
 if(!me->query(QUESTDIR+"over"))
    {
	me->set(QUESTDIR+"風雪驚變/start", 1);
	me->set(QUESTDIR+"time",time());
  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
	command("cry "+me->query("id"));
	command("say 昨日我和義弟救援一位被金兵追殺的道士，沒想到今日卻來有金兵來抓我們，\n"+
		       "這位大俠請趕快去我義弟家解救我義弟楊鐵心吧，我準備下武器隨後就到。");
		       return 1;
  }
}



inherit NPC;

#include <ansi.h>

#define TIME_TICK1 time()*60
string *list=({

"killer",

	});


int do_kill(string arg);

string do_quest1();
void create()
{
   int i;
   object *ob;
   
   set_name("拿錢買命",({ "shashou","sha" }) );
   set("gender", "男性" );
   set("nickname",HIR"拿人錢財，替人消災"NOR);
   set("age", 32);
   set("long", "這就是武林中聞名殺手集團大老板。\n");
       
   set("combat_exp", 10000000);
   set("str",30);
   set("per", 30);
   set("dex",30);
   
   set("max_gin",3000);
   set("max_kee",3000);
   set("max_sen",3000);
   set("force",3000);
   set("max_force",3000);
   
   set_skill("force",500);
   set_skill("dodge",500);
   set_skill("parry",500);
   set_skill("sword",200);
   
   set_skill("yingzi-jianfa",200);
   set_skill("huanmo-shenfa",200);
   set_skill("wanshi-jue",200);
 
   set("inquiry",([

	  "刺殺": "好吧，請用 cisha 人物id  來告訴我殺誰吧!\n",
        
	
	   ]));
   set("vocation","殺手");
   set("vocation_skill","yingzi-jianfa");
   set_temp("apply/armor",100);
   setup();
   ob=children(__DIR__"obj/qingfeng-jian");
   for(i=0;i<sizeof(ob);i++)
     if(environment(ob[i])&&userp(environment(ob[i]))){
     tell_object(environment(ob[i]),"你手中的"+ob[i]->query("name")+"被它的主人收回去了！\n");
     if(ob[i]->query("equipped"))
      ob[i]->unequip();
     destruct(ob[i]);}
     else if(environment(ob[i])){
     tell_object(environment(ob[i]),ob[i]->query("name")+"被一陣風卷走了。\n");
     destruct(ob[i]);}
     else destruct(ob[i]);
   //carry_object(__DIR__"obj/qingfeng-jian")->wield();
  
}

void init()
{
	add_action("do_kill","cisha");
	
}

int do_kill(string arg)
{
	object *usr;object me,ob;int i,j;object victim;
	int vexp,gol;int money;
	me=this_player();
	ob=this_object();
	usr=users();
	if(!arg) return notify_fail("你讓我去殺誰？明說好了!\n");
	j=0;
	if(me->query("id")==arg) return notify_fail("殺你自己？開玩笑吧？！\n");
	for(i=0;i<sizeof(usr);i++)
	{
	write("=====" + usr[i]->query("id")+ "=====\n");
		//if(usr[i]->query("id")==arg)
		//{ j=1;victim=usr[i];break;}
	}
	if(j==0) return notify_fail("恩？現在的江湖中有這個人嗎？好好看看!\n");
	if(victim->is_ghost())
	return notify_fail("這個人已經死了，你還是積點陰德吧！\n");
	vexp=victim->query("combat_exp");
	gol=vexp/1000+random(vexp/1000);
	if(gol<=0) return notify_fail("哼，武功這麼低微的人也值得我來殺?\n");
	tell_object(me,"這次行動要花掉你"+chinese_number(gol)+"兩黃金!\n");
	money=gol*10000;
	switch(MONEY_D->player_pay(this_player(), money))
	{
	case 0: return notify_fail("哼，這麼點錢，也想來找我？\n");
	case 2: return notify_fail("您的零錢不夠了，銀票又沒人找得開。\n");
	default:
	tell_object(me,"拿錢買命點點頭，道：收人錢財，與人消災，你等著好了！\n");
	if(victim->query("combat_exp")>500000)
	ob->set("combat_exp",victim->query("combat_exp"));
	if(!objectp(victim)) return notify_fail("哎呀，這個人突然跑了，下次吧!\n");
	victim->start_busy(2);
	message_vision("$N身行一晃，蹤跡不見!\n",ob);
	ob->move(environment(victim));
	message_vision(HIR"$N沖著$n叫道：有人雇我來殺你，你認命好了!\n"NOR,ob,victim);
	ob->kill_ob(victim);
log_file("killer_kill",sprintf("%s let yang kill %s\n",me->query("id"),victim->query("id")));
	call_out("yang_go",180,ob);
	return 1;
	}
	return 1;
}

void yang_go(object ob)
{
	string *dir=({"/d/luoyang/shanlu1"});
	if(!objectp(ob))
	{ remove_call_out("yang_go");return;}
	message_vision("$N四下看了看，身行一晃，蹤跡不見!\n",ob);
	ob->move(dir[random(sizeof(dir))]);
	remove_call_out("yang_go");return;
}



int is_apprentice_of(object ob)
{
	return 1;
}
int recognize_apprentice(object ob)
{
         return 1;
}



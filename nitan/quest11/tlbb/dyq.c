// cool980310
// 段延慶
// cool980724
// Modify By River 98/12
// Modify by tangfeng@SJ
// 主要修改了標誌的紀錄方式；其他無修改

inherit NPC;
#include <ansi.h>
string ask_duan1();
string ask_duan2();
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"

int do_kill(object me, object ob);

void create()
{
        set_name("青袍客", ({ "qingpao ke", "ke"}) );
        set("gender", "男性" );
        set("age", 52);
        set("str", 30);
        set("con", 30);
        set("dex", 30);
        set("int", 25);
        set("per", 10);
   	set("attitude", "friendly");

	set("max_qi", 30000);
	set("max_jing", 30000);
	set("eff_jingli", 30000);
        set("max_neili", 6000);
        set("neili", 12000);
	set("jiali", 150);
        
        set("long","這人是個老者，長鬚垂胸，面目漆黑。\n",);
	set("env/一陽指","三疊");
        set("combat_exp", 1200000+random(500000));
        set("shen", -8000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat",({ 
		(: perform_action, "finger.sandie" :), 
		(: perform_action, "finger.sanmai" :),
		(: perform_action, "finger.yizhisanmai" :),
	}));

        set_skill("parry", 210);
        set_skill("dodge", 110);
        set_skill("force", 210);
        set_skill("finger", 300);
        set_skill("buddhism", 150);
        set_skill("literate", 300);
        set_skill("staff", 300);
        set_skill("duanjia-jianfa", 220);
        set_skill("qiantian-yiyang", 300);
        set_skill("yiyang-zhi", 300);
        set_skill("tianlong-xiang", 100);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
	map_skill("finger", "yiyang-zhi");
	map_skill("force", "qiantian-yiyang");
	prepare_skill("finger","yiyang-zhi");

	set("inquiry", ([
		"段譽" : (: ask_duan2 :),
		"name" : (: ask_duan1 :),
		"段延慶" : (: ask_duan1 :),
	]));

	setup();
	carry_object("/d/dali/npc/obj/pao")->wear();
}
 void init()
{       
        object me,ob;
        ob = this_player(); 
        me = this_object();
        ::init();
        if( interactive(ob)
          && ob->query_temp(QUESTDIR1+"kill")){
         me->query("kill_id",ob->query("id"));
         call_out("kill_ob",1, ob); 
         }
}

string ask_duan1()
{
	object me,ob;
	ob=this_player();
	me=this_object();

	me->set_name("段延慶", ({ "duan yanqing", "duan","yanqing"}) );
	me->set("title",HIC"四大惡人"NOR);
	me->set("nickname",HIG"惡貫滿盈"NOR);
	if(!ob->query_temp(QUESTDIR1+"kill")) ob->set_temp(QUESTDIR1+"ask1",1);
	return "老夫便是四大惡人中的老大：段延慶！";
}

string ask_duan2()
{
        object me,ob;
        ob=this_player();
        me=this_object();

	if( !ob->query(QUESTDIR1+"over") && ob->query(QUESTDIR1+"pass_shanlu") && ob->query_temp(QUESTDIR1+"ask1")) {
		command("hehe " + ob->query("id"));
		me->set("kill_id",ob->query("id"));
		call_out("do_kill", 1, me, ob);
		return "想救段譽？送死來了！";
	}
	else return "你問這個幹什麼？";
}

int do_kill(object me, object ob)
{
	me->kill_ob(ob);
	ob->fight_ob(me);
	call_out("checking", 0, me, ob);
 	return 1;
}

void checking(object me, object ob)
{
	if (!ob) return;
	if (!me) return;
	if (!ob->query_temp(QUESTDIR1+"kill")) {
		if (me->query("qi")*10/me->query("max_qi") < 5 
		|| me->query("eff_qi")*10/me->query("max_qi") < 5 ){
			ob->set_temp(QUESTDIR1+"kill",1);
			message_vision(HIR"$n看見$N向後一跳，逃向一片大樹林。\n"NOR, me, ob);
			message_vision(HIG"$n大聲喝道：哪裏跑！$n緊緊追了過去。\n"NOR, me, ob);
			ob->move("/d/dali/wuliang/shanlin-1");
			destruct(me);
		}
		else 
			call_out("checking", 1, me, ob);
	}
}

void die()
{
	  object me;
	  object ob=this_object();
      if ( ob->query("kill_id")
                  && userp(me=present(ob->query("kill_id"),environment(ob)))
		  && me->query(QUESTDIR1+"pass_shanlu") 
		  && !me->query_temp(QUESTDIR1+"kill")
		  && !me->query(QUESTDIR1+"over")) {
		me->set("quest/天龍八部/time", time());
		me->set("quest/天龍八部/combat_exp", me->query("combat_exp"));
		me->delete_temp("quest/天龍八部");
		me->delete_temp("quest/busy");
		log_file("quest/TLBB", sprintf("%s(%s) 砍死段延慶，失敗。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
		command("sneer");
		message_vision(HIR"\n$N慘笑道：你殺了我，這輩子別想找到段譽了。\n"NOR, this_object());
		tell_object(me,HIG"\n看來，營救的事情只能由其他人完成，你還是暫時迴避一下。\n"NOR);
	}
	::die();
}

void unconcious()
{
	die();
}

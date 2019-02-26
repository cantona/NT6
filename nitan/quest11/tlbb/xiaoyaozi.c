// xiaoyaozi.c 逍遙子
// shilling 97.2

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

string ask_wyz();
void create()
{
	set_name("逍遙子", ({ "xiaoyao zi", "xiaoyao","zi" }));
	set("title", "逍遙派開山祖師");
	set("long", 
		"他就是逍遙派開山祖師、但是因為逍遙派屬於一個在江湖中\n"
		"的祕密教派，所以他在江湖中不是很多人知道，但其實他的\n"
		"功夫卻是。。。。他年滿七旬，滿臉紅光，鬚眉皆白。\n");
	set("gender", "男性");
	set("age", 75);
	set("class", "scholar");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 60);
	set("int", 60);
	set("con", 60);
	set("dex", 60);
	set("per", 60);
	
	set("max_qi", 15500);
	set("max_jing", 13000);
	set("neili", 33000);
	set("eff_jingli", 13000);
	set("max_neili", 33000);
	set("jingli", 13000);
	set("jiali", 200);
	set("combat_exp", 8000000);
	set("score", 200000);
	set("quest/天龍八部/武功/yuxiang",1);
	set("quest/天龍八部/武功/pass",1);

	set_skill("force", 450);
	set_skill("beiming-shengong", 450);
	set_skill("dodge", 200);
	set_skill("lingbo-weibu", 450);
	set_skill("liuyang-zhang", 450);
	set_skill("parry", 450);
	set_skill("blade", 450);
	set_skill("ruyi-dao", 450);
	set_skill("zhemei-shou", 450);
	set_skill("art", 200);
	set_skill("hand", 450);
	set_skill("literate", 300);
	set_skill("strike", 450);
	set_skill("sword", 450);
	set_skill("qingyun-shou", 450);
	set_skill("piaomiao-shenfa", 450);
	map_skill("force", "beiming-shengong");
	map_skill("dodge", "lingbo-weibu");
	map_skill("hand", "zhemei-shou");
	map_skill("hand", "zhemei-shou");
	map_skill("strike", "liuyang-zhang");
	
	map_skill("parry", "ruyi-dao");
	map_skill("blade", "ruyi-dao");

	prepare_skill("hand","zhemei-shou");
	prepare_skill("strike","liuyang-zhang");
	set("chat_chance_combat", 90);  
	set("chat_msg_combat", ({
                (: perform_action, "blade.wanshi" :),
                (: perform_action, "blade.ruyi" :),     
	}) );




	set("inquiry", ([

		"無崖子" : (: ask_wyz :),
			
	]));
	create_family("逍遙派", 1, "開山祖師");
	set("class", "taoist");

	setup();
	carry_object(__DIR__"obj/blade")->wield();
}

void attempt_apprentice(object ob)
{
	if ((int)ob->query_skill("beiming-shengong", 1) < 180) {
		command("say 我逍遙派內功的源泉來自於北冥神功的心法。"); 
		command("say " + RANK_D->query_respect(ob) + 
			"的北冥神功是否還應該有所提高啊？");
		return;
	}

       
	if (ob->query_int() < 35) {
		command("say 我逍遙派武功最重視“逍遙”二字。");
		command("say 而何謂“逍遙”，這隻能靠你自己去領悟。");
		command("say 但是" + RANK_D->query_respect(ob) + "的悟性似乎還有待提高啊。");
		return;
	}
	if ((string)ob->query("gender")=="男性")
   {
		command("smile");
	command("say 想不到在這世上竟然還有人可以繼承我的逍遙心法！");
	command("recruit " + ob->query("id"));
    ob->set("title",HIC"逍遙派逍遙子傳人"NOR);
       return;}
   else
      {
		message_vision("我逍遙派從不收女流之輩?”\n",ob);
       return;}
	
}




string ask_wyz()
{
	object ob = this_player();
	mapping fam = ob->query("family");
	if (!fam || fam["family_name"] != "逍遙派" )
		return RANK_D->query_respect(ob)+"，無崖子是我逍遙派中天資最為高絕的弟子，只是最近我也不知道他去哪裏了。";
        if (ob->query_skill("beiming-shengong", 1) < 300 )
	return "這位"+ RANK_D->query_respect(ob) +"，無崖子是我逍遙派中天資最為高絕的弟子，只是最近我也不知道他去哪裏了。";


if(  ob->query("marks/xiaoyao") || ob->query("quest/xiaoyao/pass") || ob->query_temp("marks/xiaoyao/gotowyz"))
      return "這位"+ RANK_D->query_respect(ob) +"，我不是讓你去找你大師兄了嗎？。";
	
       ob->set_temp("marks/xiaoyao/gotowyz", 1);
	command("nod " + ob->query("id"));
	return "你大師兄是我逍遙派中天資最為高絕的弟子，正在無量山閉關修行，算算日子也快到了，我最近正好有些事情要他去做，你去幫我把他找回來吧。";       
}

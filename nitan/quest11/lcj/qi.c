//qi.c 戚芳 by river

inherit NPC;

#include <ansi.h>
int ask_xuexi4();
string ask_diyun();
string ask_tangshi();
string ask_xieyang();
void outwuguan(object me);
#include "/d/suzhou/npc/lchj.h";

void create()
{
	set_name("戚芳", ({ "qi fang","qi","fang", "woman" }));        
	set("gender", "女性");
	set("age", 21); 
	set("long", "圓圓的臉蛋，一雙大眼黑溜溜的。\n");
	set("combat_exp", 3000);
	set("shen_type", 1);
	set("attitude", "friendly");        

	set_skill("force", 30);
	set_skill("strike", 30);
	set_skill("sword", 30);
	set_skill("shenzhao-jing",30);
	map_skill("force", "shenzhao-jing");         
 
	set("inquiry", ([
		"萬圭" : "他是我的夫君啊。",
		"學習" : (: ask_xuexi4 :),
		"狄雲" : (: ask_diyun:),	
		"唐詩選輯" : (: ask_tangshi:),	
		"鞋樣" : (: ask_xieyang:),	

		"連城訣" : "連城決？......我沒聽說過。",
		"連城劍法" : "什麼連城劍法？我只學過躺屍劍法。",
		"萬震山" : "他是我師伯。",
		"言達平" : "他是我師伯。",
		"戚長發" : "他是我爹爹。",
		"梅念笙" : "鐵骨墨萼梅念笙老先生啊。",
		"落花流水":"你說的可是南四奇！",
		"花鐵幹":"“中平槍花鐵幹”！",
		"劉乘風":"“柔雲劍劉乘風”！",
		"陸天抒":"“仁義陸大刀”！",
		"水岱":"“冷月劍水岱”！",
	]));

	setup();
	carry_object(ARMOR_D("cloth"))->wear();
	add_money("silver", 3);
}

void init()
{
	object ob;

	::init();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	if ( ob ->query_temp("jobask") == 4) {
		command("wanfu "+ob->query("id"));
		command("say 這位" + RANK_D->query_respect(ob) +",你可以 "HIY HBCYN"ask qi about 學習"CYN" 來向我了解聊天的情況。"NOR);
	}
}                               

int ask_xuexi4()
{
	object ob = this_player();
	if(ob->query_temp("jobask") == 4) {
		command("say  這位" + RANK_D->query_respect(ob) +"來武館多久啦？在這兒練功之余可和別人閒聊 "HIY HBCYN"chat"CYN"\n"+
			"來交流交流感情。還可以散布些謠言 "HIY HBCYN" rumor"CYN" ,同一門派的還可以用 "HIY HBCYN" party"CYN"。\n"+
			"閒聊和散布謠言時可用些已經有的動作。你可以試試 "HIY HBCYN"chat* hi"CYN" 。用 "HIY HBCYN"semote"CYN"\n"+
			"可以查出哪些是已有了的動作。若你話太多惹人厭就會被人投票關閉交談頻\n"+
			"道 "HIY HBCYN"vote chblk xxx"CYN" 。頻道被關了後只有等別人投票打開 "HIY HBCYN"vote unchblk\n"+
			"xxx"CYN" 。如果你想找人聊天而不想讓其他人聽到，你可以告訴 "HIY HBCYN"tell"CYN" 他(她)。有\n"+
			"人告訴你什麼事，你可以用 "HIY HBCYN"reply"CYN" 來回答他（她）。你還可以跟某一位與你\n"+
			"在同一房間的人講悄悄話 "HIY HBCYN"whisper"CYN" 。江湖上不少人沉迷在武功之中，喜歡打\n"+
			"打殺殺的，然而我覺得還是閒聊交友更有趣。你好自為之吧。"NOR);
		ob->delete_temp("jobask");
		if(ob->query_temp("jobover") != 4) {
			ob->set_temp("jobover", 4);
			command("say 聽說我師兄還有點事情找你，你最好去看一下。"NOR);
			if ( ob->query("combat_exp") < 400 ) {
				ob->add("potential", 20);
				ob->add("combat_exp", 100);
				tell_object(ob,HIW"你聽了戚芳的講解，增加了一百點實戰經驗和二十點潛能，對江湖又多了一分了解。\n"NOR);
			}
		}
		return 1;
	}
	if ( ob->query_temp("jobover") == 4) {
		command("say 我不是都和你說了麼，我師兄有事找你，快去看下吧。");
		return 1;
	}
}
string ask_diyun()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎麼進來這裡的？";
	}
	if(!me->query_temp(QUESTDIR2+"waqiang" ))
	   return "也不知道狄雲現在怎麼樣啊！";
	if(me->query_temp(QUESTDIR2+"askqi" ))
	{
	   command("sigh");
	   command("say");
	   return "也不知道狄雲現在怎麼樣啊！";
	}
	command("say");
	message_vision(HIY"$N臉上露出懷念的神色。\n", ob);
	command("look "+me->query("id"));
	command("say 恩，當年的事情發生的確太突然了，其實我也覺得狄雲不象那種人。");
	command("sigh");
	command("say 也不知道現在狄雲怎麼樣了。");
	me->set_temp(QUESTDIR2+"askqi_diyun",1);
	return "";
}
string ask_tangshi()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎麼進來這裡的？";
	}
	if(!me->query_temp(QUESTDIR2+"askqi_diyun" ))
	{
	   command("doubt");
	   return "你說什麼唐詩選輯？";
	}
	if(me->query_temp(QUESTDIR2+"asktangshi" ))
	{
	   command("say");
	   return "好像在.....！真的忘記了！";
	}
	if(me->query_temp(QUESTDIR2+"askxieyang" ))
	{
	   command("say");
	   return "好像在書房！";
	}
	command("consider");
	message_vision(HIY"$N仔細在腦海裡搜索“唐詩選輯”。\n", ob);
	command("look "+me->query("id"));
	command("say 恩，好像有這麼個名字。可是我有點忘記在哪裡了。");
	me->set_temp(QUESTDIR2+"asktangshi",1);
	return "";
}

string ask_xieyang()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎麼進來這裡的？";
	}
	if(!me->query_temp(QUESTDIR2+"asktangshi" ))
	{
	   command("doubt");
	   return "你說什麼鞋樣？";
	}
	if(me->query_temp(QUESTDIR2+"askxieyang" ))
	{
	   command("say");
	   return "好像在書房！";
	}
	command("en");
	message_vision(HIY"$N慢慢在腦海裡搜索“唐詩選輯”、“鞋樣”，突然似乎想了起來。\n", ob);
	command("look "+me->query("id"));
	command("say 恩，好像有這麼個名字。我記得給狄雲用來做過鞋樣的。");
	command("say 我好像順手隔在書房裡。只是也不知道現在狄雲怎麼樣了。");
	me->set_temp(QUESTDIR2+"askxieyang",1);
	return "";
}
void outwuguan(object me)
{
	object ob=this_object();
	object *inv;
	if(!me) return;
	command("?");
	message_vision(HIY"$N臉上露出疑惑的神色。\n", ob);
	command("say 你怎麼進來這裡的？");
	message_vision(HIR"只聽見一聲來人啊，$N被一陣棍棒給打暈了。\n"NOR, me);
	me->delete("enter_wuguan");
	inv = filter_array(deep_inventory(me), (: userp :));
	if( sizeof(inv))
		inv->move(environment(ob));
	me->unconcious();
	me->move("/d/xiangyang/damen");
	me->delete_temp("quest/busy");//
	me->delete_temp("quest/連城訣");
}

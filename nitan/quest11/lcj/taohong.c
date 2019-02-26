// taohong.c

inherit NPC;
#include <ansi.h>
#include "/d/suzhou/npc/lchj.h";
void outwuguan(object me);
string ask_qiqiang();
string ask_gaotou();
void create()
{
	set_name("中年乞婦", ({ "zhongnian qifu","qifu","zhongnian" }) ); 
	set("gender", "女性" );
	set("age", 33);
	set("long", "一箇中年乞婦，低頭弓背，披頭散髮，衣服污穢破爛。\n"); 
	set("combat_exp", 1000);
 
	setup();

	set("chat_chance", 3);
	set("chat_msg", ({
		"中年乞婦喃喃地道：老爺晚上見鬼，要砌牆，怎麼怪得我？又....又不是我瞎説。\n",
		"中年乞婦驚恐萬分：除了這裏，我什麼地方都不認得，叫我到哪裏去？\n",
		"中年乞婦道：老爺又不是不信，可是...可是....我又沒説，老爺卻趕了我出來。\n",	 
	}));
	set("inquiry", ([
		"狄雲" : "我不認識他，我真的不認識！！",	
		"戚長髮" :  "我不認識他，我真的不認識！！",	
		"砌牆" : (:ask_qiqiang:),  
		"鎬頭" : (:ask_gaotou:),  
	]));
	carry_object(ARMOR_D("cloth"))->wear();
}
string ask_qiqiang()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎麼進來這裏的？";
	}
	if(me->query_temp(QUESTDIR2+"askqiqiang" ))
	{
	   command("say");
	   return "我真的....真的不是瞎説！";
	}
	command("look "+me->query("id"));
	message_vision(HIY"$N臉上露出恐懼的神色。\n", ob);
	command("say 老爺晚上見鬼，拎着鎬頭，要砌牆，怎麼怪得我？");
	command("say 當年肯定是老爺虧心事做多了，又是殺害戚老頭，又是陷害狄什麼雲。");
	command("fear");
	me->set_temp(QUESTDIR2+"askqiqiang",1);
	return "";
}
string ask_gaotou()
{
	command("look "+this_player()->query("id"));
	command("say 吳坎那裏應該有吧。");
	return "";
}
void outwuguan(object me)
{
	object ob=this_object();
	object *inv;
	if(!me) return;
	command("?");
	message_vision(HIY"$N臉上露出疑惑的神色。\n", ob);
	command("say 你怎麼進來這裏的？");
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

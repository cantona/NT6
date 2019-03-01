//wanzhenshan.c 

inherit NPC;
#include <ansi.h>

int ask_liguan(); 
string ask_diyun();
string ask_qi();
#include "/d/suzhou/npc/lchj.h";

void create()
{
	set_name("萬震山", ({ "wan zhenshan","wan","zhenshan", "guanzhu" }));
	set("title", "襄陽武館館主");
	set("nickname", "五雲手");
	set("gender", "男性");
	set("age", 62);
	set("str", 30);
	set("dex", 26);
	set("long", "這人紫金臉龐，面帶威嚴，威武有力，站在那裡就象是一座鐵塔。\n");
	set("combat_exp", 100000);
	set("shen_type", 1);
	set("attitude", "peaceful");
	set("unique", 1);
         
	set_skill("force", 90);
	set_skill("strike", 90);  
	set_skill("dodge", 90);
	set_skill("parry", 90);     
	set_skill("shenzhao-jing", 90);
	map_skill("force","shenzhao-jing");

	set("inquiry", ([
		"工作" : "呵呵，你去找我的大徒弟吧，他會安排你的!",
		"練功" : "東西練武場都可以練的，你去那兒練吧!",
		"離館" : (:ask_liguan:),  
		"狄雲" : (: ask_diyun:),	
		"戚長發" : (: ask_qi:),	
		"唐詩選輯" : "唐詩選輯？......我沒聽說過。",
		"連城訣" : "連城決？......我沒聽說過。",
		"連城劍法" : "什麼連城劍法？我沒聽說過。",
		"言達平" : "他是我師弟。",
		"梅念笙" : "鐵骨墨萼梅念笙老先生啊，正是我師傅。",
		"落花流水":"你說的可是南四奇！",
		"花鐵幹":"“中平槍花鐵幹”！",
		"劉乘風":"“柔雲劍劉乘風”！",
		"陸天抒":"“仁義陸大刀”！",
		"水岱":"“冷月劍水岱”！",
	]));

	setup();
	carry_object(ARMOR_D("jinduan"))->wear();
}

int ask_liguan()
{
	object ob;
	object letter;
	
	ob = this_player();
	if(! ob->query("enter_wuguan")){
		command("say 你不是已經來打聽過了麼？");
		return 1;
	}
	if(ob ->query("combat_exp") >= 3000 && objectp(letter = new(__DIR__"obj/letter")) ) {
		command("nod "+ob->query("id"));
		command("say 這位" + RANK_D->query_respect(ob)+"可以出去闖盪江湖了，江湖險惡，可千萬小心啊。去和我"+
			"四徒弟孫均去說一聲吧，他會安排的。");
		            command("say 江湖險惡，若要防身，非有幾件利器堅甲不可。");
            
            	command("say 老夫當年雲遊江南，曾與一位奇人相交甚好，你可前往尋訪，求得冶鐵□造之術。");
            	command("say 如果你不解冶鐵□造之術，可以使用 help dazao 獲得詳細信息。");
                letter->move(ob);
                message_vision("$n給$N一封「"+letter->query("name")+"」。\n",ob,  this_object());        
                   command("say 我看你基礎武功還不夠紮實，就讓我再指點你幾招，你可要看仔細了。");
ob->set_skill("force", 32);
ob->set_skill("dodge", 32);
ob->set_skill("parry", 32);
ob->set_skill("cuff", 32);
ob->set_skill("strike", 32);
ob->set_skill("leg", 32);
ob->set_skill("finger", 32);
ob->set_skill("blade", 32);
ob->set_skill("sword", 32);
ob->set_skill("staff", 32);
ob->set_skill("hand", 32);
ob->set_skill("club", 32);
ob->set_skill("whip", 32);
ob->set_skill("stick", 32);
ob->set_skill("throwing", 32);
ob->set_skill("claw", 32);
ob->set_skill("yeqiu-quan", 10);
                ob->delete("enter_wuguan");
		ob->delete("wgjob");
		return 1;
	}
	else {
		command("pat "+ob->query("id"));
		command("say 這位" + RANK_D->query_respect(ob)+"的經驗還太差，江湖太危險，你還是乖乖在武館練功吧。");
		return 1;
	}
}
string ask_diyun()
{
	object me,ob;
	me = this_player();
	ob = this_object();
    if(me->query("combat_exp")<10000)
   {
    command("killair");
       return "你問這個幹什麼？";
}
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎麼進來這裡的？";
	}
	if(me->query_temp(QUESTDIR2+"askwan_diyun" ))
	{
	   command("hehe");
	   return "嘿嘿，現在狄雲應該老死在監獄吧！";
	}
	message_vision(HIY"$N臉上露出警惕的神色。\n", ob);
	command("look "+me->query("id"));
	command("heng");
	command("say 恩，當年他師傅妄想刺殺我，而狄雲更是和賤女桃紅苟合，送他去監獄已經是優待他了。");
	command("haha");
	me->set_temp(QUESTDIR2+"askwan_diyun",1);
	if(me->query_temp(QUESTDIR2+"askwan_qi" ))
		tell_object(me,HIG"你總感覺這話中有問題。你更發現萬震山似乎眼神神經兮兮的。\n"NOR);
	return "";
}
string ask_qi()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎麼進來這裡的？";
	}
	if(me->query_temp(QUESTDIR2+"askwan_qi" ))
	{
	   command("say");
	   return "嘿嘿，在哪裡我也不知道......！";
	}
	command("look "+me->query("id"));
	command("haha");
	command("say 當年戚長發妄想刺殺我，幸虧我發現得及時。這些年，也不知道他哪裡去了。");
	message_vision(HIY"$N臉上露出得意的神色。\n", ob);
	command("haha");
	me->set_temp(QUESTDIR2+"askwan_qi",1);
	if(me->query_temp(QUESTDIR2+"askwan_diyun" ))
		tell_object(me,HIG"你總感覺這話中有問題。你更發現萬震山似乎眼神神經兮兮的。\n"NOR);
	return "";
}
void outwuguan(object me)
{
	object ob=this_object();
	object *inv;
        if(!me) return;
   if( me->query("combat_exp") <3000 ) return;
	command("?");
	message_vision(HIY"$N臉上露出疑惑的神色。\n", ob);
	command("say 你怎麼進來這裡的？");
	message_vision(HIR"只聽見一聲來人啊，$N被一陣棍棒給打暈了。\n"NOR, me);
	me->delete("enter_wuguan");
	inv = filter_array(deep_inventory(me), (: userp :));
	if( sizeof(inv))
		inv->move(environment(ob));
	me->unconcious();
if(me->query("combat_exp")>3000)         me->move("/d/xiangyang/damen");
	me->delete_temp("quest/busy");//
	me->delete_temp("quest/連城訣");
}

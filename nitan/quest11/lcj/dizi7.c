//dizi7.c 馮坦 by river
//將原有的di yun的內容搬到這裏
//by tangfeng for 連城訣quest

inherit NPC;

#include <ansi.h>
#include "question.h"
#include "/d/suzhou/npc/lchj.h";

void create()
{
	set_name("馮坦", ({ "feng tan", "feng", "tan"}));
	set("title","襄陽武館七弟子");
	set("long", "他是萬震山的七弟子，沉默寡言，一副尖嘴猴腮的樣子。\n");
	set("gender", "男性");
	set("age", 22); 

	set("combat_exp", 5000);
	set("shen_type", 1);
	set("unique", 1);

	set_skill("force", 35);
	set_skill("strike", 35);
	set_skill("sword", 35);
	set_skill("shenzhao-jing",35);
	map_skill("force", "shenzhao-jing");          

	set("startroom","/d/wuguan/dayuan");

	set("chat_chance", 3);
	set("chat_msg", ({            
		(: random_move :)
	}) );
       
	setup();
	carry_object(ARMOR_D("cloth"))->wear();
}

void init()
{
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	object *inv, where;

	if (!ob) return;
	where = environment(ob);
	if( !ob || environment(ob) != environment() ) return;        
	if ( ob->query("combat_exp") > 3500 && !wizardp(ob) && !ob->query_temp(QUESTDIR2+"start") ){
		command("disapp "+ ob->query("id"));
		command("say 這位" + RANK_D->query_respect(ob)+ "，你已經能到外面的江湖上去闖蕩一翻了，怎麼還想\n"+
			"在武館裏偷懶？武館不希望你再留在此地了。\n");
		message_vision(HIR"只聽見一聲來人啊，$N被一陣棍棒給打暈了。\n"NOR, ob);
		ob->delete("enter_wuguan");
		inv = filter_array(deep_inventory(ob), (: userp :));
		if( sizeof(inv))
			inv->move(where);
		ob->unconcious();
		ob->delete_temp("quest/busy");//
		ob->delete_temp("quest/連城訣");
		ob->move("/d/xiangyang/damen");
		return;
	}
	if( ! ob->query_temp("wgtask") && ob->query("combat_exp") < 400 ) {
		ob->set_temp("wgtask",1);
		ob->set_temp("wgmeet", 1);
		command("bow "+ob->query("id"));
		command("whisper "+ob->query("id")+" 這位" + RANK_D->query_respect(ob) +"初次來到這個神祕的武俠世界，是不是\n"+
			"感覺充滿着新奇和陌生？我可以告訴你怎樣慢慢熟悉這個世界的，請問你是否\n"+
			"需要幫助呢？如果您是個新手，請輸入 "HIY HBCYN"answer y"GRN"，否則就請輸入 "HIY HBCYN"answer n"GRN"。");
	}
	if( ob->query_temp("jobover") == 1) {
		ob->set_temp("jobask",2);
		command("pat "+ob->query("id"));
		command("whisper "+ ob->query("id")+ " 現在對自己和武館的環境有一定了解了吧？不過，\n"+
			"光了解周圍的環境還不夠，還要了解整個世界的情況才行，周圻師兄常年闖蕩\n"+
			"江湖，知道的比較多，你可以去找他問問。他現在在偏廳一帶，你可以按照我\n"+
			"孫均兄弟告訴你的武館地圖（help map wuguan）去找他。");
	}
	if( ob->query_temp("jobover") == 2) {
		ob->set_temp("jobask",3);
		command("smile "+ob->query("id"));
		command("whisper "+ ob->query("id")+ " 瞭解了整個世界，是不是感覺雄心勃勃，想到江湖\n"+
			"中有一番作為呢？那麼，去找我沈城師兄學習下戰鬥知識吧。他現在正在練功\n"+
			"房教人練功呢。"NOR);
	}
	if( ob->query_temp("jobover") == 3) {
		ob->set_temp("jobask",4);
		command("hehehe");
		command("whisper "+ ob->query("id")+ " 行走江湖，光憑好勇鬥狠是不行的，還要注意跟大\n"+
			"家多多交流哦。我師妹最愛嘮叨，有深厚的“聊天功力”，你去找她準沒錯。\n"+
			"她現在在睡房附近，恐怕正想找人聊天呢。"NOR);
	}
	if( ob->query_temp("jobover") == 4 && ob->query_temp("jobask") != 5) {
		ob->set_temp("jobask", 5);
		command("nod");
		command("whisper "+ ob->query("id")+ " 好了，現在你已經對書劍也瞭解的差不多了。武館\n"+
			"有還有很多事情要做，我魯坤師兄正缺人手，你可以到他那找點工作來做。");
	}
	if( ob->query("combat_exp") < 3000 && ob->query_temp("jobover") == 5) {
		command("pat " +ob->query("id"));
		tell_object(ob, CYN"馮坦説道：「這位" + RANK_D->query_respect(ob) +"，我出幾個問題考考你，如果答對了可有獎哦。」\n"NOR);
		tell_object(ob, WHT"\n如果確認回答問題，請輸入 "HIY HBCYN"answer y"WHT" ，不願意回答的話，可以繼續去魯坤師\n"+
				"兄那裏繼續工作，請輸入 "HIY HBCYN"answer n"WHT" 。\n\n");
		ob->set_temp("wgquestion",1);
	}
	return;
}
string replace_number(string msg)
{
	msg = replace_string(msg, "一", "a");
	msg = replace_string(msg, "二", "b");
	msg = replace_string(msg, "三", "c");
	msg = replace_string(msg, "四", "d");
	msg = replace_string(msg, "五", "e");
	msg = replace_string(msg, "六", "f");
	return msg;
}

string *answer_type;

mixed choose_type(object me, string *answer, int j, string right_answer)
{
	int x, y;
	string str;

	for ( x = 0; x < j ; x ++) {
		str = answer[random(j)];
		answer_type = me->query_temp("answer_type");
		if ( ! sizeof(answer_type))
			me->set_temp("answer_type", ({ str }));
		else {
			for(y=0; y < j; y ++) {
				if (member_array(str, answer_type) != -1)
					str = answer[y];
			}
			answer_type = answer_type + ({ str });
			me->set_temp("answer_type", answer_type );
		}
		if ( str == right_answer )
			me->set_temp("answer", replace_number(chinese_number(x+1)));
	}
	return answer_type;
}

int do_question(object me)
{
	string right_answer, str, *answer;
	int i, j, x;
	mapping question;

	if ( me->query_temp("answer_list") && sizeof(keys(me->query_temp("answer_list"))) >= sizeof(question_list)) {
		command("say 不好意思，沒有題目了。");
		return 1;
	}

	i = random(sizeof(question_list));

	if ( me->query_temp("answer_list/"+ i) )
		do_question(me);
	else {
		me->set_temp("answer_list/"+ i , 1);

		question = question_list[i];
		answer = question["choose"] + ({ question["answer"] });
		right_answer = question["answer"];

		j = sizeof(answer);

		choose_type(me, answer, j, right_answer);

		me->add("wgjob/quest", 1);

		tell_object(me, CYN"\n馮坦説道：「現在是第"+chinese_number(me->query("wgjob/quest"))+"題，一共有"+chinese_number(j)+"個選項，請用 "HIY HBCYN"answer 字母"CYN" 回答。」\n"NOR);
		str = "請問：" + question["question"] +"\n";

		for ( x = 0; x < j ; x ++ ) {
			str += sprintf("%s、%-31s%s", 
				capitalize(replace_number(chinese_number(x+1))), 
				answer_type[x], 
				(x+1)%2?"":"\n"
			);
		}

		if ( j % 2)
			str += "\n";
		tell_object(me, str);
		return 1;
	}
}

int do_answer(string arg)
{
	object me = this_player();
	string str;
	float i;

	if ( ! arg ) return 0;
	if ( me->query_temp("wgmeet")) {
		me->delete_temp("wgmeet");
		if ( arg == "y" ) {
			command("nod "+ me->query("id"));
			command("whisper " + me->query("id")+ " 那好，我們先來了解一下一些基本的指令：在書劍\n"+
				"裏移動的命令是e、w、s、n、u、d，分別代表東西南北上下六個基本方向，以\n"+
				"及ne、wd、su、enter、out等組合和特殊命令，它們分別代表東北、西下、南\n"+
				"上等方向以及進入和外出等。好了，現在你可以去找孫均，他會告訴你更多的\n"+
				"常識，他現在應該在門廊一帶，往南走兩步就到了。");
			me->set_temp("jobask",1);
			me->set_temp("need_answer", 1);
		}
		else if ( arg == "n" ) {
			command("nod "+ me->query("id"));
			command("whisper " + me->query("id")+ " 看來你對書劍已經有了一定的瞭解，武館裏還有很\n"+
				"多事情要做，我魯坤師兄正缺人手，你可以到他那找點工作來做。");
			me->set_temp("jobask", 5);
		}
		return 1;
	}
	if ( me->query_temp("wgquestion")) {
		me->delete_temp("need_answer");
		me->delete_temp("wgquestion");
		me->delete_temp("jobover");
		if ( arg == "y") {
			tell_object(me, CYN"馮坦説道：「好吧，不過在回答問題前，我還是要先提醒你一下，你可以通過\n"+
					"指令 "HIY HBCYN"help"CYN" 來了解一下書劍的一些基本情況。下面的一些問題，你可以通過查\n"+
					"詢 help 來得到正確的答案，如果實在找不到答案，也可以通過 "HIY HBCYN"chat"CYN" 來詢問\n"+
					"別人來得到答案。」\n"NOR);
			tell_object(me, HIR"\n\t\t準備好了吧！那我們就開始了。\n\n"NOR);
			call_out("do_question", 0 , me);
		}
		else if ( arg == "n" ) {
			tell_object(me, CYN"馮坦説道：「哎，不過既然你不想回答，那也就算了。」\n"NOR);
		}
		return 1;
	}
	if ( me->query_temp("answer")) {
		if ( arg == "字母")
			return notify_fail(CYN"馮坦説道：「請回答具體的字母，例如回答："HIY HBCYN"answer A"CYN" 。」\n"NOR);
		if ( arg == me->query_temp("answer") || arg == capitalize(me->query_temp("answer"))) {
			me->add("combat_exp", 80 );
			me->add_temp("right", 1);
			if ( me->query_skill("literate", 1) < 30 ) {
				me->set_skill("literate", me->query_skill("literate", 1) + 1);
				str = "和一級讀書寫字。";
			}
			else
				str ="。";
			i = me->query_temp("right")*100.0 / me->query("wgjob/quest");
			tell_object(me, HIW"恭喜你，答對了！你被獎勵了八十點實戰經驗"+str+"\n"NOR);
			tell_object(me, CYN"馮坦説道：「您到目前一共回答了"+chinese_number(me->query("wgjob/quest"))+"題，答對了"+chinese_number(me->query_temp("right"))+"題，成功率為 "+sprintf("%3.2f%%", i)+"。」\n"NOR);
		}
		else tell_object(me, CYN"馮坦説道：「哎，真可惜，你答錯了，正確答案應該是 "+capitalize(me->query_temp("answer"))+" 才對。」\n"NOR);

		me->delete_temp("answer");
		me->delete_temp("answer_type");

		if ( me->query("combat_exp") < 3000 && me->query("wgjob/quest") < 50 ) 
			do_question(me);
		else {
			if ( me->query("combat_exp") >= 3000 ) {
				command("congra "+me->query("id"));
				tell_object(me, CYN"馮坦説道：「你可以去找我師傅萬震山詢問離館的事情了 "HIY HBCYN"ask wan about 離館"CYN" 。」\n"NOR);
			}
			else {
				command("addoil "+ me->query("id"));
				tell_object(me, CYN"馮坦説道：「你可以繼續去到我大師兄那兒找工作做 "HIY HBCYN"ask lu about 工作"CYN" 。」\n"NOR);
			}
		}
		return 1;
	}
	return 0;
}


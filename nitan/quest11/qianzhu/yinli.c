// yinli.c 殷離
// Modify By River@sj 99.06
// Update By River@SJ For Qzs 2002.11.21

inherit NPC;

#include <ansi.h>
string ask_lsd();
string ask_popo();
string ask_qzs();
string ask_zhizhu();

void create()
{
	set_name("殷離", ({ "yin li", "yin", "li" }));
	set("gender", "女性");
	set("age", 19);
	set("long","她是個十七八歲的少女，荊釵布裙，是個鄉村貧女，\n"+
                   "面容黝黑，臉上肌膚浮腫，凹凹凸凸，生得極是醜陋，\n"+
                   "只是一對眸子頗有神采，身材也是苗條纖秀。\n");
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 26);
	set("per", 6);
	set("unique", 1);
	set("location", 1);
	set("combat_exp", 300000);

	set("shen", -500);
	set("attitude", "peaceful");
	set("max_qi",600);
	set("max_jing",600);
	set("neili",800);
	set("max_neili",800);
	set("jiali",20);

	set_skill("unarmed", 60);
	set_skill("parry",60);
	set_skill("piaoyi-shenfa",60);
	set_skill("dodge", 60);
	set_skill("throwing",60);
	set_skill("duoming-jinhua",60);
	set_skill("qianzhu-wandushou", 60);
	set_skill("finger", 60);
	set_skill("force",60);
	set_skill("shenghuo-shengong",60);

	map_skill("force","shenghuo-shengong");
	map_skill("hand","qianzhu-wandushou");
	map_skill("dodge","piaoyi-shenfa");
	map_skill("throwing","duoming-jinhua");
	map_skill("parry","duoming-jinhua");
	prepare_skill("hand","qianzhu-wandushou");
	set("inquiry", ([
		"謝遜" : "是。。。是他的。",
		"靈蛇島"  : (: ask_lsd :),
		"金花婆婆"  : (: ask_popo :),
		"千蛛萬毒手" : (: ask_qzs :),
		"蜘蛛" : (: ask_zhizhu :),
		"修煉" : (: ask_zhizhu :),
	]));
	set("chat_chance", 3);
	set("chat_msg", ({
		(: random_move :),
		CYN"殷離突然自言自語道：“死鬼！我很老了麼？老得像你媽了？”，説完又吃吃地笑了起來。\n"NOR,
		(: random_move :),
		"殷離從地下拾起一根柴枝，在地上亂抽了兩下。\n",
		(: random_move :),
		CYN"殷離突然板着臉道：你取笑我生得醜，你不想活了。\n"NOR,
		(: random_move :),
		CYN"殷離彎過中指，用指節輕輕在你額頭上敲了兩下，笑道：乖兒子，那你叫我媽罷！\n"NOR,
	}));
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	setup();
	carry_object("/d/mingjiao/obj/green-cloth")->wear();
	carry_object(BINGQI_D("feihuangshi"))->wield();
}

string ask_qzs()
{
	object ob, me = this_player();
	mapping quest;
	int i, time;

	if ( me->query("gender") != "女性")
		return "這千蛛萬毒手可不太適合大男人來修煉哦。";

        if ( me->query("combat_exp") < 1200000 )
		return "你的實戰經驗太少了，還是再去鍛鍊一番吧。";

	if ( me->query("con") < 15 || me->query("int") < 20) 
		return "你的先天條件實在太差，不適合修煉千蛛萬毒手。";

        if ( present("goldbox", me))
		return "修煉千蛛萬毒手所用的金盒不是在你這裏麼？還問我作甚？";

	if ( me->query_temp("get_jinhe"))
		return "我不是剛給你金盒了，怎麼還來要啊？？";

	time = time() - me->query("qianzhu_time");
	if ( me->query("qianzhu_time") && time < 86400 && !wizardp(me))
	 	return "嗯？我不是和你説了，過段時間再來問問吧。";

	ob = unew(BOOK_D("jinhe"));
	if( !clonep(ob)) 
		return "哎喲，修煉千蛛萬毒手的金盒不知道給誰拿走了。";

	quest = me->query("quest/qianzhu");

	if ( quest && quest["pass"]) {
		ob->set("xiulian", 10 + random(10));
		ob->move(me);
		me->set_temp("get_jinhe", 1);
		return "嗯，這裏有個我才修煉過的金盒，既然你要就拿去吧。";
	}
	else {
		i = me->query("combat_exp", 1) / 500000;

		if ( me->query("registered") < 3 && quest && quest["fail"] >= 3 ){
			destruct(ob);
			return "你不適合修煉千蛛萬毒手，還是不要再打探了吧。";
		}
		if ( quest && quest["fail"] >= i ) {
			destruct(ob);
			return "你短時間內還不適合修煉千蛛萬毒手，還是過段時間再來打聽吧。";
		}

		if (random(me->query_int(1)) > 30
		 && random(me->query_con(1)) > 35
            && QUEST_D->questing(me,1,0,1)
            && random(me->query_kar()) > (21-(int)me->query("per",1)/10) ) {
			command("look "+ me->query("id"));
			me->set("quest/qianzhu/pass", 1);
			me->delete("qianzhu_time");
			log_file("quest/qianzhu", 
				sprintf(HIR"%-18s失敗%-2d次後，解開千蛛萬毒手，悟：%d，根：%d，福：%d。"NOR,
					me->name(1)+"("+capitalize(getuid(me))+")", 
					me->query("quest/qianzhu/fail"),
					me->query_int(1), 
					me->query_con(1), 
					me->query_kar()
				), me
			);
			ob->move(me);
			return "嗯，你就拿着這個金盒去修煉(xiulian)千蛛萬毒手吧。";
		}
		else {
			command("look "+ me->query("id"));
			me->add("quest/qianzhu/fail", 1);
			me->set("qianzhu_time", time());
			destruct(ob);
			log_file("quest/qianzhu", 
				sprintf("%-18s試圖解開千蛛萬毒手，失敗%-2d次，悟：%d，根：%d，福：%d。\n",
					me->name(1)+"("+capitalize(getuid(me))+")", 
					me->query("quest/qianzhu/fail"),
					me->query_int(1), 
					me->query_con(1), 
					me->query_kar()
				), me
			);
			return "看來你還不適合修煉千蛛萬毒手，過段時間再來問問吧。";
		}
	}
}

string ask_zhizhu()
{
	object me = this_player();

	if ( !me->query("quest/qianzhu/pass"))
		return "你還不適合修煉千蛛萬毒手，問來沒用。";
	else
		return "這金盒中的蜘蛛若是死了，可去星宿海附近抓些新的來。";
}

string ask_popo()
{
	this_player()->set_temp("ask_popo", 1);
	return "金花婆婆待我最好了，我們住在東海靈蛇島上，只是有時來中原看看。";
}

string ask_lsd()
{
	object me=this_player();

	if(!me->query_temp("ask_popo"))
		return "嗯....這我可不清楚耶，你最好問問別人吧。";
	if(me->query("combat_exp") <100000)
		return "你這點身體的基礎，怎麼夠出海呢？";
	if(this_object()->query_temp("waiting"))
		return "我正在玩呢，別煩我。";
	if(this_object()->query_temp("waiting1"))
		return "我正在玩呢，別煩我。";
	if(me->query_temp("yinli_failed"))
		return "哼，你不陪我玩，我才不會告訴你呢。";      
	if(me->query_temp("yinli_ask"))
		return "咦，我不是叫你先陪我玩玩嗎？急什麼急。";
	if(me->query_temp("yinli_ask1"))
		return "咦，我不是叫你跟着我到處去玩玩嗎，還等什麼呀？";
	if(me->query_temp("marks/靈蛇"))
		return "咦，我不是剛剛告訴過你了嗎？";
	if(me->query("luopan/lsd"))
		return "咦，我不是已經告訴你了麼？";
	me->set_temp("yinli_ask1",1);
	command("xixi");
	command("say 我一個人在這裏好無聊啊，你先陪我玩玩好嗎？");
	this_object()->set_temp("waiting", 1);
	remove_call_out("checking");
	call_out("checking", 20, me, this_object());
	return "你跟着(follow)我，我們到處去走走。";
}

int checking(object me, object ob)
{
	ob->delete_temp("waiting");
	if(!me || environment(me)!=environment(ob) || me->query_leader() != ob){
		me->delete_temp("yinli_ask1");
		me->set_temp("yinli_failed",1);           
		command("angry");
		command("say 不陪我就算了，誰稀罕！");
		return 1;
	}
	if(me->is_killing(ob->query("id"))){
		me->delete_temp("yinli_ask1");
		me->set_temp("yinli_failed",1);
		command("hmm "+me->query("id"));
		return 1;
	}
	me->delete_temp("yinli_ask1");
	me->set_temp("yinli_ask",1);
	command("say 好啊！好啊！那我們就到處逛逛吧。");
	ob->set("chat_chance", 35);
	ob->set_temp("waiting1", 1);
	remove_call_out("checking1");
	call_out("checking1", 12*me->query_con(), me, this_object());
	return 1;
}

int checking1(object me, object ob)
{
	ob->delete_temp("waiting1");
	if(!me || environment(me)!=environment(ob) || me->query_leader() != ob){
		me->delete_temp("yinli_ask");
		me->set_temp("yinli_failed",1);
		command("angry");
		command("say 才陪我了一會兒就溜了，誰稀罕！");
		return 1;
	}
	if(me->is_killing(ob->query("id"))){
		me->delete_temp("yinli_ask1");
		me->set_temp("yinli_failed",1);
		command("hmm "+me->query("id"));
		return 1;
	}
	me->delete_temp("yinli_ask");
	me->set_temp("marks/靈蛇",1);
	me->set("luopan/lsd", 1);
	command("say 好啦，我玩夠了。你想知道靈蛇島在什麼地方是吧？");
	command("say 不過我可要先警告你，去那裏很危險的哦！");
	command("whisper "+me->query("id")+" 婆婆的靈蛇島在黃道帶以東一百、以南五個距離的地方。");
	new("/d/mingjiao/obj/luopan")->move(ob);
	command("give luo pan to "+me->query("id"));
	ob->set("chat_chance", 3);
	return 1;
}
                                                                                 

// /d/thd/npc/zhou.c
// Modify By River@SJ about jieyi and hubo
// Modify by Darken for taohua quest 2000
// Modify By River@Sj for jiuyin quest
// Modify by yueying@SJWL屏蔽重復的互搏失敗判斷488-491,否則只能解一次
// Update by JPei 2011 for yunu-xinjing/hubo && Question_Check
inherit NPC;

#include <skill.h> 
#include <ansi.h>
#include "question.h"

int ask_jieyi();
int do_answer(string arg);
int questions(object me);
int ask_jiuyin();
int ask_hubo();
int do_fangyuan();
int do_learn(string arg);
int ask_story();
int ask_skill();
int ask_story2();
int ask_xlv();
void waiting(object ob);
void create()
{
	set_name("周伯通", ({ "zhou botong", "zhou", "botong" }) );
	set("nickname", "老頑童");
	set("long", "他滿頭長發，直垂至地，長眉長須，鼻子嘴巴都被遮掩住了。\n"
		"他須發蒼然，並未全白，只是不知有多少年不剃，就如野人一般毛茸茸地甚是嚇人。\n"
		"他的舉止猶如孩童一樣。\n");
	set("gender", "男性" );
	set("age", 48);
	set("attitude", "peaceful");
	set("apprentice", 1);

	set("str",28);
	set("int",25);
	set("con",30);
	set("dex",29);
	set("unique", 1);
	set("pur", 30);
	set("per", 24);

	set("no_get", "周伯通對你而言太重了。\n");

	set("max_qi", 12000);
	set("max_jing", 10000);
	set("max_neili", 21000);
	set("jiali", 150);
	set("combat_exp", 5600000);
	set("eff_jingli", 9500);
	set("double_attack", 1);
	set("score", 5000);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "sword.qixing" :),
		(: perform_action, "sword.sanqing" :),
		(: perform_action, "cuff.kong" :),
		(: perform_action, "cuff.ming" :),
	}));

	set_skill("force", 380);
	set_skill("xiantian-gong", 380);
	set_skill("dodge", 390);
	set_skill("tiyunzong", 390);
	set_skill("cuff", 380);
	set_skill("kongming-quan", 380);
	set_skill("parry", 380);
	set_skill("sword", 380);
	set_skill("quanzhen-jianfa", 380);
	set_skill("taoism", 200);
	set_skill("literate", 260);

	map_skill("force", "xiantian-gong");
	map_skill("dodge", "tiyunzong");
	map_skill("cuff", "kongming-quan");
	map_skill("sword", "quanzhen-jianfa");
	map_skill("parry", "quanzhen-jianfa");
	prepare_skill("cuff", "kongming-quan");

	set("rank_info/respect", "老頑童");
	set("shen_type", 1);
	create_family("全真教", 2, "弟子");
	set("class", "taoist");

	set("inquiry", ([
		"name": "叫我周伯通就好了。",
		"rumors": "我被那個臭東邪關在這裡十幾年，每天就是一個啞僕來送飯。",
		"here": "這裡是桃花島。寒雨那個小壞蛋在這裡加了無數的ｑｕｅｓｔ，看你能不能找全了。",
		"東邪": "是黃藥師這個無恥的家伙，騙了我的九....去看。",
		"黃藥師": "這個無恥的家伙，騙了我的九....去看。",
		"中神通": "我的師兄是天下武功最高的，第一次華山論劍時公推為第一高手。",
		"王重陽": "我的師兄是天下武功最高的，第一次華山論劍時公推為第一高手。",
		"周伯通": "找我有什麼事嗎？",
		"瑛姑": "四張機，鴛鴦織就欲雙飛....",
		"劉瑛": "四張機，鴛鴦織就欲雙飛....",
		"段皇爺": "老頑童做事對不起他，沒臉再見他了。",
		"段智興": "老頑童做事對不起他，沒臉再見他了。",
		"南帝": "老頑童做事對不起他，沒臉再見他了。",
		"老頑童": "我就是啊，找我有什麼事嗎？",
		"空明拳": "空明拳共七十二路，口訣是：空朦洞鬆、風通容夢、沖窮中弄、童庸弓蟲。",
		"kongming-quan": "空明拳共七十二路，口訣是：空朦洞鬆、風通容夢、沖窮中弄、童庸弓蟲。",
		"黃蓉": "是幾個月前來陪我聊天的那個小姑娘嗎？",
		"郭靖": "那是我的結義兄弟，人雖然傻，心腸倒好。",
		"寒雨": "說起來也是他創造了我，不過這家伙是個造ｑｕｅｓｔ狂。",
		"jpei": "說起來也是他創造了我，不過這家伙是個造ｑｕｅｓｔ狂。",
		"桃花島": "這裡就是桃花島。寒雨那個小壞蛋在這裡加了無數的ｑｕｅｓｔ，看你能不能找全了。",
		"方": "方要正方！",
		"fang": "方要正方！",
		"圓": "圓要渾圓！",
		"yuan": "圓要渾圓！",
		"九陰真經": (: ask_jiuyin :),
		"雙手互搏": (: ask_hubo :),
		"左右互搏": (: ask_hubo :),
		"結義": (: ask_jieyi :),
		"結拜": (: ask_jieyi :),
		"故事": (: ask_story :),
              "小龍女": (: ask_xlv :),
		"後來怎樣": (: ask_story2 :),
		"武功": (: questions :),
		"功夫": (: ask_skill :),
	]));

	setup();

	if(random(2))
		carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/wudang/obj/white-robe")->wear();
}

void init()
{
	object ob = this_player();
	add_action("do_fangyuan","fangyuan");
	add_action("do_draw","draw");
	add_action("do_draw","hua");
	add_action("do_answer","answer");
	add_action("do_learn","learn");
	add_action("do_learn","xue");
	::init();
	if (ob->query("family/family_name") == "全真教") {
		command("angry " + ob->query("id"));
		command("say 怎麼你到今天才來找我？！明天我就去和處機說讓他打你屁股。");
	}
}

void kill_ob(object me)
{
        command("chat* crazy " + me->query("id"));
        ::kill_ob(me);
}

void unconcious()
{
        command("chat* 嘆道：老頑童今日是要歸天了，到陰世玩玩兩只鬼打架，那些大頭鬼、無常鬼一定瞧得莫名其妙，鬼色大變。");
        ::unconcious();
}


int ask_story()
{
        object me = this_player();
        string msg;
        msg = CYN"周伯通聽到$N要他講故事，登時興高採烈。\n"NOR;
        msg+= CYN"周伯通開始講起九陰真經和黃裳的故事。\n"NOR;
        msg+= CYN"周伯通看$N不問後來怎樣，便賭氣不說了。\n"NOR;
        message_vision(msg, me);
        me->set_temp("thd/story",1);
        return 1;
}

int ask_story2()
{
        object me = this_player();
        string msg;
        if (me->query_temp("thd/story") == 1){
                msg = CYN"周伯通一聽$N問他後來怎樣，又口沫橫飛的說起來。\n";
                msg+= CYN"周伯通講完又開始對$N說起他和全真教的故事。\n";
                msg+= CYN"$N聽著，也學到了些全真教練氣的皮毛。\n"NOR;
                msg+= HIW"周伯通說完故事，又無聊的問道：“兄弟，有什麼好玩的武功麼？\n"NOR;
                message_vision(msg, me);
                me->set_temp("thd/story",2);
                return 1;
        }
        message_vision(CYN"周伯通奇怪的問道：“什麼後來怎樣？”\n"NOR, me);
        return 1;
}

int ask_jieyi()
{
	object ob=this_player();
	int i, time;

	i = ob->query("combat_exp") - 1000000;
       i /= 100000;

	time = time() - ob->query("quest/jiebai/time");

	if (ob->query("quest/jiebai/pass")) {
		command("? " + ob->query("id"));
		command("say 咱倆不是結拜過了嗎？");
		return 1;
	}
	if (ob->query("quest/jiebai/fail") >=3 && ob->query("registered") < 3){
		command("hmm");
		command("say 我不是說了，我沒興趣和你結拜啊！");
		return 1;
	}
	if ( ob->query("quest/jiebai/time") && time < 86400 ) {
		command("shake");
		command("say 我現在可沒空，我忙著玩呢。");
      tell_object(ob,HIG"看起來周伯通在"+CHINESE_D->chinese_time(86400-time)+"之內不準備理你。\n"NOR);
		return 1;
	}
        if ( ob->query("quest/jiebai/fail") >= i && !ob->query("cw_exp")){
		command("shake");
		command("say 我現在可沒空，我忙著玩呢。");
		return 1;
	}
        if (!wizardp(ob) && ob->query("age") > 48 && !ob->query("cw_exp")){
		command("shake");
		command("say 我老頑童只喜歡和青年人玩，和你結拜？沒意思，沒意思！");
		return 1;
	}
	if (ob->query("gender") != "男性" && ob->query("gender") != "女性") {
                if (ob->query("age") > 48 && !ob->query("cw_exp")) 
			command("say 我本來也想與你結拜，就是不知是兄弟相稱還是姐弟相稱？");
		else
			command("say 我本來也想與你結拜，就是不知是兄弟相稱還是兄妹相稱？");
		command("laugh");
		return 1;
	}
/*
        if ( ob->query("class") =="bonze" || ob->query("class") == "huanxi"){
		command("monk "+ ob->query("id"));
		command("say "+RANK_D->query_respect(ob)+"，老頑童我可沒有興趣和你結拜。");
		return 1;
}

	if ( ob->query("int") > 25) {
		command("shake");
		command("say 你這個人鬼靈精，保不準打著什麼主意呢。");
		return 1;
	}
*/
	if ( ob->query("shen") < -100000) {
		command("shake");
		command("say 我雖然天性隨便，但師尊教誨不敢忘，于正邪之道還是要分清的。");
		return 1;
	}
	if ( ob->query("combat_exp") < 1000000) {
		command("shake "+ ob->query("id"));
		command("say 這位"+RANK_D->query_respect(ob)+"你的武藝實在太糟糕了，我可沒興趣和你結拜。");
		return 1;
	}
	if (random(ob->query("kar")) < 20 || random(ob->query_int(1)) < 30){
		command("shake");
		command("say 我現在沒有空，要不你先陪我玩玩？");
		ob->add("quest/jiebai/fail", 1);
		ob->set("quest/jiebai/time", time());
		log_file("quest/jiebai",
			sprintf("%-18s想與周伯通結拜，失敗%s次。\n",
				ob->name(1)+"("+capitalize(getuid(ob))+")",
				chinese_number(ob->query("quest/jiebai/fail")) 
			), ob
		);
		return 1;
	}
	command("nod " + ob->query("id"));
	if (ob->query("gender") == "男性") {
		command("say 好吧，你我就結拜為兄弟吧。");
	}
	else if (ob->query("gender") == "女性") {
		if (ob->query("age") > 48)
			command("say 好吧，你我就結拜為姐弟吧。");
		else
			command("say 好吧，你我就結拜為兄妹吧。");
	}
	message_vision("周伯通與$N並肩而跪，朗聲說道：“老頑童周伯通，今日與" + ob->name(1) +"義結金蘭，日後有福共享，有難共當。\n"+
			"若是違此盟誓，教我武功全失，連小狗小貓也打不過。”\n", ob);
	log_file("quest/jiebai",
		sprintf("%-18s失敗%s次後，成功與周伯通結拜，福：%d，悟：%d。\n",
			ob->name(1)+"("+capitalize(getuid(ob))+")",
			chinese_number(ob->query("quest/jiebai/fail")), 
			ob->query("kar"), 
			ob->query_int(1)
		), ob
	);
	ob->set("quest/jiebai/pass", 1);
	ob->set("quest/jiebai/exp", ob->query("combat_exp"));
	return 1;
}

int ask_jiuyin()
{
	object ob = this_player();
	object zhou = this_object();
	object book;
	int i,time;

	i = ob->query("combat_exp") - 2000000;
	i /= 500000;
	time = time()- ob->query("quest/jiuyin1/time");

	if(present("jiuyinzhenjing shangjuan", ob)) {
		command("faint");
		command("say 你不是有了麼？");
		return 1;
	}
	if( zhou->is_busy() || zhou->is_fighting()){
		command("hmm");
		command("say 你沒看見我正忙著麼？");
		return 1;
	}
        if( ob->query("quest/jiuyin1/fail") >= 3 && ob->query("registered") < 3 && !ob->query("quest/jiuyin1/pass")){
		command("say 我正忙著呢。");
		return 1;
	}
        if( time < 86400 && !ob->query("quest/jiuyin1/pass") ) {
		command("say 我正忙著呢,你過一會兒再來吧。");
       tell_object(ob,HIG"看起來周伯通在"+CHINESE_D->chinese_time(86400-time)+"之內不準備理你。\n"NOR);
		return 1;
	}

	if ( ob->query("quest/jiuyin1/fail") >= i && ! ob->query("cw_exp") ) {
		command("say 我正忙著呢，你還是先回去好好學學武藝吧。");
		return 1;
	}

        if (ob->query("quest/jiuyin1/pass")){
		book = unew("/d/thd/obj/jiuyin-book1");
		if(!clonep(book)){
			command("pat");
			command("say 我現在沒有空，「九陰真經上卷」你等會再來要吧。");
			return 1;
		}
		if(clonep(book) && book->violate_unique()){
			destruct(book);
			command("pat");
			command("say 我現在沒有空，「九陰真經上卷」你等會再來要吧。");
			return 1;
		}
		command("consider");
		command("say 又要再抄一份？");
		message_vision(HIW"$N重新抄錄了一份九陰真經的上卷。\n"NOR,ob);
		book->set("owner", ob->query("id"));
		book->move(ob);
		return 1;
	}
	if (ob->query_temp("jyquest") != 3) {
                command("? " + ob->query("id"));
                return 1;
	}
	command("say 九陰真經？那個本來是我師哥的，可是給黃老邪跟他老婆騙了去。");
	command("say 聽她老婆告訴他的上卷殘缺不全，下卷又被他自己徒弟偷了，這個就叫報應。");
	command("laugh zhou");
	ob->set_temp("jyquest", 4);
	command("say 來來來，到洞裡面來，難得有個人找我，你別想跑了。");
	message_vision(HIY"周伯通拉著$N說道：“乖乖的聽我說故事吧。”\n"NOR,ob);
	command("grin");
	ob->move("/d/thd/neidong");
	zhou->move("/d/thd/neidong");
	call_out("waiting", 120, ob);
	return 1;
}

int ask_skill()
{
	object me = this_player();
	object ob = this_object();
	object book;
	object* ppl;
	int i, total, j =0;

	if (me->query_temp("jyquest") != 5) {
		command("? " + ob->query("id"));
		return 1;
	}

	command("hehe zhou");
	command("say 這些功夫是我自己的創作，可厲害的很啊。");
	message_vision(CYN"周伯通卻只是告訴$N如何施展，完全不演練給$N看。\n"NOR,me);

//關于執行效率的問題，如果玩家不滿足條件，那也沒必要去先取list和玩家數據吧。
//讀了llm寫的wiz教程，想想自己的代碼，真是汗顏啊 By Jpei 

ppl = users();
total = me->query("str")+ me->query("int")+ me->query("dex")+ me->query("con"); 
	i = sizeof(ppl);
	while(i--) {
		if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query("quest/jiuyin1/pass"))
		j++;
	} 
	if( me->query("combat_exp") > 2000000
 	   && random(me->query("kar")) > 26
           && random(total) > 78
           && (
                 (!me->query("y-card-vip")&&random(20) == 3) 
               ||( me->query("y-card-vip")&&random(15) == 3)       //這裡年卡月卡一視同仁了。
             )
           && j < 2 ){ 
		message_vision(HIW"\n周伯通在$N練習純熟後，突然哈哈大笑起來。\n"NOR,me);
		command("haha");
		command("laugh");
		command("say 這些厲害武功，怎麼是我自己的功夫？那就是九陰真經啊！");
		command("say 今天我總算看到的這功夫的威力，真是死也瞑目了。");
		book=unew("/d/thd/obj/jiuyin-book1");
		log_file("quest/jiuyin",
			sprintf("%-18s失敗%s次後，得到九陰真經上冊，悟：%d，福：%d，淳：%d。\n",
				me->name(1)+"("+capitalize(getuid(me))+")",
				chinese_number(me->query("quest/jiuyin1/fail")),
				me->query_int(1), 
				me->query("kar"), 
				me->query("pur") 
			), me
		);
		me->delete_temp("jyquest");
		me->set("quest/jiuyin1/pass",1);
		me->set("title",HIR"武林神話"NOR"﹒"HIC"九陰真經傳人"NOR);      //板磚侍候
		if(!clonep(book)){
			command("hungry");
			command("say 好了，都看完了，肚子都餓了，我要吃飯去了。");
			return 1;
		}
		if(clonep(book) && book->violate_unique()){
			destruct(book);
			command("hungry");
			command("say 好了，都看完了，肚子都餓了，我要吃飯去了。");
			return 1;
		}                 
		command("say 反正你已經學會了，這九陰真經上卷讓你抄錄一份去吧。");
		message_vision(HIW"$N將九陰真經的上卷小心的抄錄下來。\n"NOR,me);
		book->set("owner", me->query("id"));
		book->move(me);
		return 1;
	}
	message_vision(CYN"$N無論怎麼練習就是無法成功。\n"NOR,me);
	command("sigh");
	command("say 我這高深武功，你大概別想學了吧。");
	command("disapp");
	me->add("quest/jiuyin1/fail", 1);
	me->set("quest/jiuyin1/time", time());
	log_file("quest/jiuyin",
		sprintf("%-18s想從周伯通處得到九陰真經上冊，失敗%s次。\n",
			me->name(1)+"("+capitalize(getuid(me))+")",
			chinese_number(me->query("quest/jiuyin1/fail"))
		), me
	);
	me->delete_temp("jyquest");
	return 1;
}

void waiting(object ob)
{
	if( ob->query_temp("thd/story")==2 
	 && ob->query_temp("jyquest") == 4
	 && ob->query_temp("jiuyin/question") > 3){
		command("say 你陪我陪了這麼久，一定很無聊吧？");
		command("hmm");
		command("ah zhou");
		command("say 這樣吧，我教你點好玩的功夫！");
		command("grin");
		ob->set_temp("jyquest",5);
		ob->move("/d/thd/cave");
		this_object()->move("/d/thd/cave");
	}
	else {
		command("yawn");
		command("say 你這個人又笨又無聊，出去！出去！");
		ob->delete_temp("jyquest");
		ob->add("jiuyin/failed", 1);
		ob->move("/d/thd/cave");
		destruct(this_object());
	}
}

int ask_hubo()
{
	object ob=this_player();
	int hubo,i,time;

       i = ob->query("combat_exp") - 1000000;
	i /= 200000;
	time = time()- ob->query("quest/hubo/time");

	if(!ob->query("quest/jiebai/pass")){
		tell_object(ob,"周伯通正盯著你看，不知道打些什麼主意。\n");
		command("say 你是誰啊，怎麼莫名其妙地問我雙手互搏的事啊？");
		return 1;
	}               
	if ( ob->query("double_attack")) {
		command("? " + ob->query("id"));
		command("say 你不是已經學會了嗎？");
		return 1;
	}
	if( ob->query("quest/hubo/fail") >= 3 && ob->query("registered")< 3){
		command("disapp " + ob->query("id"));
		command("say 已經試了這麼多次，看來你一輩子也練不會這門功夫了。");
		return 1;
	}
       if ( ob->query("quest/hubo/fail") >= i&&!ob->query("cw_exp") ) {
		command("shake " + ob->query("id"));
		command("say 看來你現在還不適合學這門功夫。");
		return 1;
}
       if ( ob->query("quest/hubo/time") && time < 86400) {
		command("shake " + ob->query("id"));
		command("say 看來你現在還不適合學這門功夫，你過段時間再來試試吧。");
       tell_object(ob,HIG"看起來周伯通在"+CHINESE_D->chinese_time(86400-time)+"之內不準備理你。\n"NOR);
		return 1;
	}
	hubo = ob->query_temp("zuoyou_hubo");
	if (hubo == 22) {
		command("say 接著練第一課！");
		return 1;
	}
	if (hubo == 1) {
		command("say 讓你練你就快練嘛！");
		return 1;
	}
	if (hubo > 1 && hubo <= 21) {
		command("say 怎麼樣，練不會吧？就象黃蓉那女孩兒玲瓏剔透，一顆心兒上生了十七八個竅，可是這門功夫她便始終學不會！");
		return 1;
	}
	if (ob->query_skill("force") < 100 || ob->query("max_neili") < 500 || ob->query("combat_exp") < 50000) {
		command("say 你還是先打好武學基礎再說吧。");
		return 1;
	}
	command("say 這門功夫是我在洞中無聊之時想出來的玩意兒，說難是難到極處，說容易也容易之至。\n"+
		"有的人一學便會，有的人一輩子也學不了，越是聰明，越是不成。");
	command("say 你先練練這第一課：左手畫方(fang)，右手畫圓(yuan)。");
	ob->set_temp("zuoyou_hubo", 1);
	return 1;
}

int do_fangyuan()
{
	object ob=this_player();
	int hubo;

	if (ob->is_busy() || ob->is_fighting())
		return notify_fail("你正忙著呢！\n");

	hubo = ob->query_temp("zuoyou_hubo");
	if (!hubo) return 0;
	if (hubo < 21) {
		message_vision("$N伸出兩根食指在地上劃畫，但畫出來的方塊有點象圓圈，圓圈又有點象方塊。\n", ob);
		ob->add_temp("zuoyou_hubo", 1);
		return 1;
	}
	if (hubo == 21) {
		message_vision("$N伸出兩根食指在地上劃畫，但畫出來的方塊有點象圓圈，圓圈又有點象方塊。\n", ob);
		command("haha " + ob->query("id"));
		command("say 是麼？你這一下便辦不到！");
		ob->add_temp("zuoyou_hubo", 1);
		return 1;
	}
	if (hubo == 22) {
          if( (ob->query_temp("sj_credit/quest/public/hubo")&&random(ob->query("pur"))>18) 
                || random(ob->query("pur")) > 25 
                || ( ob->query("buyvip")&& random(ob->query("pur"))>=22 ) 
                || ( ob->query_temp("sj_credit/quest/public/hubo") &&ob->query("buyvip") && random(ob->query("pur"))>16) ){
				message_vision("$N微微一笑，凝神守一，心地空明，隨隨便便的伸出雙手手指，左手畫了一個方塊，右手畫了一個圓圈，\n"+
					"方者正方，圓者渾圓。\n", ob);
				say("周伯通大吃一驚，過了半晌才道：“這定是你從娘胎裡學來的本領，那便易辦了。”\n");
				message_vision("周伯通將他領悟出來的這門天下無比的奇功，一古腦兒都教給了$N。\n", ob);
                           ob->delete_temp("sj_credit/quest/public/hubo");
				ob->delete_temp("zuoyou_hubo");
				log_file("quest/jiebai",
					sprintf("%-18s失敗%s次後，從周伯通處領悟到雙手互搏，淳：%d。\n",
						ob->name(1)+"("+capitalize(getuid(ob))+")",
						chinese_number(ob->query("quest/hubo/fail")),
						ob->query("pur") 
					), ob
				);
				ob->set("double_attack", 1);
				ob->set("quest/hubo/pass", 1);
				return 1;
		                                                                                                         }

            else {
				ob->delete_temp("zuoyou_hubo");
				message_vision("$N又伸出兩根食指在地上劃畫，但畫出來的仍舊是方塊有點象圓圈，圓圈又有點象方塊。\n", ob);
				write("看來並不是這麼簡單。\n");
                           ob->delete_temp("sj_credit/quest/public/hubo");
				ob->add("quest/hubo/fail", 1);
				ob->set("quest/hubo/time", time());
      		              command("disapp " + ob->query("id"));

				log_file("quest/jiebai",sprintf("%-18s想從周伯通處領悟雙手互搏，失敗%s次。\n",
					ob->name(1)+"("+capitalize(getuid(ob))+")",chinese_number(ob->query("quest/hubo/fail")) ), ob);
				return 1;
	         }
               }
return 0;
}

int do_draw(string arg)
{
	object ob=this_player();

	if (!ob->query_temp("zuoyou_hubo")) return 0;
	if (arg == "fang" || arg == "方" || arg == "yuan" || arg == "圓") 
		return notify_fail("周伯通怒道：讓你同時畫方圓！\n");
	if (arg == "fang yuan" || arg == "方圓") return do_fangyuan();
	return 0;
}

int accept_object(object who, object ob)
{
	if (ob->id("skin") && ob->query("material") == "paper") {
		if ((who->query_temp("thd/onquest") == 7)&&(who->query_temp("thd/story")==2)) {
			message_vision(CYN"周伯通將人皮仔細查看，發現是九陰真經！\n"NOR, who);
			message_vision(CYN"你正想拿去交給黃藥師，卻被周伯通攔住。\n"NOR, who);
			command("say 這個等等再說，先來玩玩吧！");
			command("sing");
			command("say 好久沒人來陪我玩啦，你跟我練練吧！");
			command("hit " + who->query("id"));
			call_out("finish",5, who);
			return notify_fail("");
		}
		else {
			command("? " + who->query("id"));
			command("say 給我這個做什麼？\n");
			return notify_fail("");
		}
	}
	else if (who->query_temp("jyquest")==2 && ob->id("fan he") && ob->query("material") == "wood") {
		command("ah " + who->query("id"));
		command("say 是黃老邪的小丫頭叫你幫忙送飯來麼？");
		message_vision(CYN"周伯通不等$N回答，已經開始將食物塞進嘴中。\n"NOR,who);
		message_vision(CYN"周伯通吃完，幹笑了一下，才對$N問道：“不知道你吃過了沒有？”\n"NOR,who);
		who->set_temp("jyquest", 3);
		command("say 黃老邪想要我的九陰真經，把我關了十五年啦。");
		command("sing3");
call_out("destructing", 1, ob);
                return 1;
	}

       else if(ob->query("id") == "yufeng zhen" && who->query("family/family_name")=="古墓派") {
       command("ah ");
       command("say 一定是龍姑娘讓你來找我的吧。 ");
       command("say 當年我被金輪法王的毒蛛咬中，多虧這小小的金針解毒。 ");
       who->set_temp("marks/yufengzhen",1);
             call_out("destructing", 1, ob); 
                return 1; 
            }



	return 0;
}

int prevent_learn(object ob, string skill)
{
	if (skill == "kongming-quan")
		return 0;
	return 1;
}
 
int is_apprentice_of(object ob)
{
	return 1;
}
 
int recognize_apprentice(object ob)
{
	return 1;
}

void finish(object who)
{
	string msg;
	msg = HIC"周伯通說道：“挨打沒關系，多打你就習慣啦，好久沒跟人打架了。”\n";
	msg+= HIY"周伯通說著，便向$N打來。\n";
	msg+= HIC"周伯通高興的道：“快還手啊。”\n";
	msg+= HIR"$N的武功不及他，終于承受不了，暈了過去。\n"; 

	message_vision(msg, who); 
	who->set_temp("thd/onquest",8);
	who->unconcious();
}




int ask_xlv()
{
	object me=this_player();


	command("tsk ");
	command("say 龍姑娘和楊過兩個小家伙可了不得，真是一對神仙眷侶。");
 
if( me->query_temp("marks/yufengzhen") && !me->query("gmhb") )
{
	message_vision(HIY"周伯通一聽你問起小龍女的事情，不由得眉飛色舞。\n"+
			"周伯通給你講起當年他和小龍女被金輪法王的毒蜘蛛困在山洞之中，小龍女\n"+
    	"學會左右互博，一手全真劍一手玉女劍打的金輪法王落荒而逃，說到精彩之處，\n"+
    	"不由得手舞足蹈，口沫四濺。\n"+
    "周伯通盯著你看了看，饒有興趣的問道：“不知道龍姑娘有沒有教你這門功夫？”\n"NOR, me);
    me->set_temp("marks/askzhou",1);
    me->delete_temp("marks/yufengzhen");
}
	return 1;

}


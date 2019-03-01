// /d/mr/npc/murong-fu.c  慕容復
// by leontt /12/05/2000
// by tiantian@sj 6/3/2000 fix mr job bug
// Modify By River@SJ 修正 job，另外門派drug全部cut 12/08/Y2k
// cut gold by augx@sj 9/27/2001
// Modify By tangfeng@SJ 8/15/2004
// 增加復興天下篇，tlbb內容
// By Spiderii@ty加入bishen quest

inherit NPC;
#include <job_mul.h>
#include <ansi.h>
#include <combat.h>
#include "skill.h"
#include "murong-fu.h";

#define QUESTDIR "quest/天龍八部/"
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"
#define QUESTDIR3 "quest/天龍八部/蕭峰身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"

int ask_fuming(string arg);
mixed ask_bo();
string ask_fenglu();
mixed ask_sword2();
string ask_skill();
string ask_wang();
string ask_learn();
string ask_ge();
string ask_sword();
string ask_book();
string ask_book2();
string ask_times();
int ask_fangqi();
string ask_fuxing();
string ask_yuxi();
int ask_bishen();

string* npc_where = ({"/d/mr/mtl/qianyuan","/d/mr/mtl/xiaojing7","/d/mr/mtl/liulin3","/d/mr/mtl/hc2","/d/mr/mtl/keting","/d/mr/mtl/cl","/d/mr/mtl/hhyuan",});                    
                     
void create()
{
	object weapon;
	set_name("慕容復",({"murong fu","murong","fu"}));
	set("title","姑蘇慕容公子");
	set("nick","以彼之道 還施彼身");
	set("long",
		"他就是天下號稱以彼之道，還施彼身的姑蘇慕容復。\n"
		"他臉上帶著不可一世的笑容。\n");
	set("age", 27);
	set("attitude", "friendly");
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("no_get", "慕容復背不起來。\n");

	set("max_qi",4500);
	set("max_jing", 3000);
	set("eff_jingli", 4000);
	set("neili",5500);
	set("max_neili", 3500);
	set("jiali", 1);
	set("combat_exp", 2500000);
	set("dan", 10);
	set("shen", -1000);
	set("no_bark",1);
	set("chat_chance_combat", 25);
	set("chat_msg_combat", ({
		(: exert_function, "shenyuan" :),
		(: perform_action, "strike.riyue" :),
		(: perform_action, "finger.ci" :),
		(: perform_action, "sword.lianhuan" :),
	}));
	set_skill("strike",170);
	set_skill("finger",170);
	set_skill("dodge",180);
	set_skill("force", 170);
	set_skill("canhe-zhi", 160);
	set_skill("murong-jianfa",170);
	set_skill("shenyuan-gong", 180);
	set_skill("yanling-shenfa", 160);
	set_skill("xingyi-zhang",170);
	set_skill("douzhuan-xingyi", 180);
	set_skill("parry", 180);
	set_skill("sword", 270);
	set_skill("literate", 170);
	set_skill("murong-daofa", 160);
	set_skill("blade",160);
	set_skill("xingyi-jianzhen",170);

	map_skill("blade", "murong-daofa");
	map_skill("finger", "canhe-zhi");
	map_skill("force", "shenyuan-gong");
	map_skill("dodge", "yanling-shenfa");
	map_skill("strike", "xingyi-zhang");
	map_skill("parry", "murong-jianfa");
	map_skill("sword", "murong-jianfa");

	prepare_skill("finger","canhe-zhi");
	prepare_skill("strike","xingyi-zhang");

	create_family("姑蘇慕容", 2, "弟子");

	set("inquiry", ([
		"name" : "我就是以彼之道，還施彼身的姑蘇慕容復。\n",
		"here" : "這裡是大名鼎鼎的燕子塢，難道你沒有聽說過？\n",
		"rumors" : "家父突染惡疾，我連他老人家最後一面都沒見到，此事頂有蹊蹺！\n",
		"姑媽" : "我的姑媽住在曼佗羅山莊，那裡有聞名天下的娘繯玉洞。\n",
		"虛竹" : "你說的可是少林弟子虛竹？我不認識......\n",
		"葉二娘" : "我不認識......你找錯人問了。\n",
		"還施水閣" : (: ask_ge :),
		"慕容博" : (: ask_bo :),
		"領悟" : (: ask_book :),
	//	"俸祿" : (: ask_fenglu :),
		"王語嫣" : (: ask_wang :),
		"碧玉劍" : (: ask_sword2 :),
		"寶劍" : (: ask_sword :),
		"次數" : (: ask_times :),
		"鬥轉星移"  : (: ask_skill :),
		"圖解" : (: ask_book2 :),
		"武學" : (: ask_learn :),
		"復命" : (: ask_fuming :),
		"放棄" : (: ask_fangqi :),
		"復興天下" : (: ask_fuxing :),//tlbb quest
		"大燕國" : (: ask_fuxing :),
		"復國" : (: ask_fuxing :),	
		"大燕國玉璽" : (: ask_yuxi :),
		"秘密" : (: ask_yuxi :),		
		"玉璽" : (: ask_yuxi :),	
              "以彼之道還施彼身" : (: ask_bishen :),
	
	]));
	set("dan_count", 2);
	set("book_count",1);
	set("book2_count" ,1);
	set("dan1_count", 2);
	setup();
	if (clonep()) {
		weapon = unew(BINGQI_D("sword/biyu-jian"));
		if (!weapon)
			weapon = new(BINGQI_D("changjian"));
		weapon->move(this_object());
		weapon->wield();
		carry_object(__DIR__"obj/cloth3")->wear();
		add_money("gold", 2);
	}
}

void init()
{
	object ob;
	::init();
	ob = this_player();
	if (interactive(ob = this_player()) 
		&&ob->query(QUESTDIR5+"start")
		&&!ob->query(QUESTDIR5+"over")
		&&ob->query_temp(QUESTDIR5+"dagouzhen")
		&&ob->query_temp(QUESTDIR5+"zhenfa")
		&&ob->query_temp(QUESTDIR5+"shaolinzhen")) {
			ob->start_busy(2);
			remove_call_out("greeting");
			call_out("greeting", 2, ob);
		}
        add_action("do_lingwu","taojiao");
	add_action("do_jiaoliang", "jiaoliang");
}
void greeting(object me)
{
	int i,p;
	if(!me) return;
	if (!me->query(QUESTDIR5+"start") 
		|| me->query(QUESTDIR5+"over")
		|| !me->query_temp(QUESTDIR5+"dagouzhen")
		|| !me->query_temp(QUESTDIR5+"zhenfa")
		|| !me->query_temp(QUESTDIR5+"shaolinzhen"))
		return;
	if(environment(me)!=environment(this_object())) 
	{
		message_vision(HIC"\n$n疑惑地問道：$N，人呢？\n"NOR,me,this_object()); 
		me->delete_temp("quest/天龍八部");
		me->delete_temp("quest/busy");//任務沖突標志取消
		return;
	}
	command("whisper "+me->query("id")+" 沒想到"+ RANK_D->query_respect(me) +"竟然有如此實力，獨闖少林，連破少林伏魔陣和丐幫打狗陣！");
	command("whisper "+me->query("id")+" 更沒有想到"+ RANK_D->query_respect(me) +"竟然能夠擊敗無名神僧和蕭峰的聯手！\n");
	command("chat* admire "+me->query("id"));
	command("pat "+me->query("id"));
	command("whisper "+me->query("id")+" 有"+ RANK_D->query_respect(me) +"的幫助，想來復興我大燕國指日可待！");
	command("haha "+me->query("id"));
	command("whisper "+me->query("id")+" "+ RANK_D->query_respect(me) +"，等朕興復大燕，身登大寶，人人皆有封賞。");

	command("addoil "+me->query("id"));
	command("crazy");

	me->set(QUESTDIR5+"over",1);
	me->delete_temp("quest/天龍八部");
	me->delete_temp("quest/busy");//任務沖突標志取消
	//獎勵
        p=10+random(100);
	me->add("max_neili",p);
        me->add("combat_exp",me->query_skill("force")*2+500);
        i=100+random(100);
	me->add("mana",i);
        tell_object(me,HIY"\n你于"+NATURE_D->game_time()+"幫助慕容復打敗少林丐幫，實現復興天下的計劃，獲得"+p+"點最大內力、"+((int)me->query_skill("force")*2+500)+"點經驗獎勵、"+i+"點聲望。\n"NOR);   
        log_file("quest/TLBB", sprintf("%s(%s) 復興天下篇完成。獎勵：%d點最大內力，%d點經驗，%d點聲望。\n", me->name(1),me->query("id"), p,(me->query_skill("force")*2+500),i ) );
}
void attempt_apprentice(object ob)
{
	if (ob->query_skill("parry", 1) < 120) {
		command("say 我姑蘇慕容以彼之道、還施彼身對招架要求甚高。");
		command("say " + RANK_D->query_respect(ob) + "的功力不夠，還是請回吧。");
		return;
	}

	if (ob->query_skill("shenyuan-gong", 1) < 100) {
		command("say 我姑蘇慕容以彼之道、還施彼身對內功心法要求甚高。");
		command("say " + RANK_D->query_respect(ob) + "的功力不夠，還是請回吧。");
		return;
	}

	command("say 嗯，看你還是個學武的料，我就收下你吧！");
	command("say 蒼天在上，讓我姑蘇慕容又得一良材，為復興我大燕多了一份力量。");
	command("chat* 朗聲說道：公子我又收一良材，大燕興復指日可待啦！");
	command("chat* haha");
	command("recruit " + ob->query("id"));
	ob->set("title","姑蘇慕容第三代弟子");
}
string ask_fuxing()
{
	object ob=this_player();
	object *obj;
	int x;

	mapping fam = ob->query("family");
	if ( !fam )
		return "這位"+ RANK_D->query_respect(ob) +"無門無派，此話從何說起？";
	if( !ob->query(QUESTDIR3+"bad"))
		return "我與"+ RANK_D->query_respect(ob) +"向來沒什麼往來，此話從何說起？"; 		

	if( ob->query(QUESTDIR5+"over"))
	{
		command("haha");
		command("whisper "+ob->query("id")+" 有"+ RANK_D->query_respect(ob) +"的幫助，想來復興我大燕國指日可待！");
		if (random(2))return "今天天氣就是好，就是好。";
		return "今天天氣真不錯。";
	}
	if( ob->query(QUESTDIR5+"start"))
	{
		command("nod " + ob->query("id"));
		command("whisper "+ob->query("id")+" 唯上之策，先從少林下手了。玄慈的事情正是個機會。");
		if (random(2))return "今天天氣就是好，就是好。";
		return "今天天氣真不錯。";
	}
	if( ob->query_temp(QUESTDIR5+"yuxi") && !ob->query(QUESTDIR5+"start"))
	{
		command("addoil " + ob->query("id"));
		command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"，不是告訴盡快將玉璽找回？");
		if (random(2))return "今天天氣就是好，就是好。";
		return "今天天氣真不錯。";
	}
	if( ob->query_temp(QUESTDIR5+"give_shouji") && !ob->query(QUESTDIR5+"start"))
	{
		command("addoil " + ob->query("id"));
		command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"，確實不錯。");
		if (random(2))return "今天天氣就是好，就是好。";
		return "今天天氣真不錯。";
	}		
    
	command("addoil "+ob->query("id"));
	command("say "+ RANK_D->query_respect(ob) +"幫我把蕭峰趕出中原，已經幫我大忙了！");
	//增加時間和經驗間隔限制
	//時間一天，經驗500K
	if(ob->query(QUESTDIR+"time")&&time()-ob->query(QUESTDIR+"time")<86400)
		return "不過，"+ RANK_D->query_respect(ob) +"今天很忙了，先行休息去吧！";
	if(ob->query(QUESTDIR+"combat_exp")&&ob->query("combat_exp")-ob->query(QUESTDIR+"combat_exp")<500000)
		return "以"+ RANK_D->query_respect(ob) +"目前的經驗就算目前有情況，也幫不上什麼忙，還是抓緊練功吧！";
	//只能一個人做
	obj = users();
	x = sizeof(obj);
	while(x--) {
		if ( obj[x]->query_temp(QUESTDIR5+"askfu") && obj[x]!=ob) 
		{
			command("sigh "+ob->query("id"));
			return "只是關于這件事情，已經有"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"幫我了.........";
		}
	}
	//設定標志
	ob->set(QUESTDIR+"time",time());
	ob->set(QUESTDIR+"combat_exp",ob->query("combat_exp"));  

	command("whisper " + ob->query("id")+" 恩，只是所謂復興天下，談何容易，而且......");
	command("look " + ob->query("id"));
	command("whisper " + ob->query("id")+" 當今，天下武林所謂正派有“兩派一幫”之說，就是少林派、武當派與丐幫。");
	command("whisper " + ob->query("id")+" 其中少林、武當人稱武林泰山北鬥，臥龍藏虎之輩層出不窮，無名神僧和張三豐人稱不死老怪物。");
	command("whisper " + ob->query("id")+" 而丐幫乃天下第一大幫，從前任幫主蕭峰，到大俠郭靖、還是神丐洪七，都是名震一方的高手。");
	command("consider");
	command("whisper " + ob->query("id")+" 近年來，張無忌掌教西域明教，大有凌駕中原武林之勢，且因武當關系緊密，影響力日益加劇。");
	command("whisper " + ob->query("id")+" 西南大理，枯榮復出，六脈重現，段譽更被稱為青年第一高手，挾皇室之威，隱約成為江南武林之尊。");
	command("whisper " + ob->query("id")+" 因此，要復興天下，必須掃除這“兩派一幫一教一世家”。對付丐幫少林，我已經有了一個完全之策。");
	command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"竟然立志復興天下，就先帶張三豐、張無忌或枯榮三個中任意一個人頭回來見我，以明心志！");
	log_file("quest/TLBB", sprintf("%s(%s)為復興天下需要砍人了，特此紀錄。經驗：%d。\n", ob->name(1),ob->query("id"), ob->query("combat_exp")) );
	command("addoil " + ob->query("id"));
	ob->set_temp(QUESTDIR5+"askfu",1);
	ob->set_temp("quest/busy",1);//與任務系統沖突標志
	if (random(2))		return "今天天氣就是好，就是好。";
	return "今天天氣真不錯。";
}
string ask_yuxi()
{
	string where;
	object room,mrdizi,ob=this_player();
	object *obj;
	int x;

	mapping fam = ob->query("family");
	if ( !fam )
		return "這位"+ RANK_D->query_respect(ob) +"無門無派，此話從何說起？";
	if( !ob->query(QUESTDIR3+"bad"))
		return "我與"+ RANK_D->query_respect(ob) +"向來沒什麼往來，此話從何說起？"; 		

	if( ob->query(QUESTDIR5+"over"))
	{
		command("haha");
		command("whisper "+ob->query("id")+" 有"+ RANK_D->query_respect(ob) +"的幫助，想來復興我大燕國指日可待！");
		if (random(2))return "今天天氣就是好，就是好。";
		return "今天天氣真不錯。";
	}
	if( ob->query(QUESTDIR5+"start"))
	{
		command("nod " + ob->query("id"));
		command("whisper "+ob->query("id")+" 唯上之策，先從少林下手了。玄慈的事情正是個機會。");
		if (random(2))return "今天天氣就是好，就是好。";
		return "今天天氣真不錯。";
	}

	if( ob->query_temp(QUESTDIR5+"yuxi") && !ob->query(QUESTDIR5+"start"))
	{
		command("? " + ob->query("id"));
		command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"，不是告訴盡快將玉璽找回？");
		if (random(2))return "今天天氣就是好，就是好。";
		return "今天天氣真不錯。";
	}
	if(!ob->query_temp(QUESTDIR5+"give_shouji") && !ob->query(QUESTDIR5+"start"))
	{
		command("? " + ob->query("id"));
		command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"，你哪裡知道玉璽這回事情？");
		if (random(2))return "今天天氣就是好，就是好。";
		return "今天天氣真不錯。";
	}

	command("nod "+ob->query("id"));
	command("whisper " + ob->query("id")+" 既然如此，我就坦誠以開，我其實就是大燕國慕容氏皇裔，興復燕國的大業是從古繼來的大業。");
	command("whisper " + ob->query("id")+" 雖然艱難萬分，但依舊鞠躬盡瘁，竭力以赴。為此已經付出幾代人的努力。\n");
	command("shrug "+ob->query("id"));
    command("whisper " + ob->query("id")+" 前一段時間，有慕容三代弟子背叛我慕容，更可惡的是竟然偷走大燕國玉璽。");
	//只能一個人做
	obj = users();
	x = sizeof(obj);
	while(x--) {
		if ( obj[x]->query_temp(QUESTDIR5+"yuxi") && obj[x]!=ob) 
		{
			command("sigh "+ob->query("id"));
			return "還好，已經有"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"幫我了.........";
		}
	}
	ob->set(QUESTDIR+"time",time());
	ob->set(QUESTDIR+"combat_exp",ob->query("combat_exp"));  

	where=npc_where[random(sizeof(npc_where))];  
	if(!room=find_object(where))
		room=load_object(where);
	if(!room) room=load_object("/d/mr/mtl/midao");
	mrdizi=new(__DIR__"mrdizi");
	mrdizi->set("party","mr"); 
	mrdizi->set("fight_id",ob->query("id")); 
	if(random(2)) mrdizi->move(room);
	mrdizi=new(__DIR__"mrdizi");
	mrdizi->set("party","mr"); 
	mrdizi->set("fight_id",ob->query("id")); 
	mrdizi->move(room);  
	mrdizi=new(__DIR__"mrdizi");
	mrdizi->set("party","mr"); 
	mrdizi->set("fight_id",ob->query("id")); 
	mrdizi->set("yuxi_have",1);//帶玉璽的弟子
	mrdizi->move(room);
	ob->set_temp("quest/busy",1);//與任務系統沖突標志
	tell_room(environment(mrdizi), HIB"\n"+mrdizi->name()+"匆匆地來到"+room->query("short")+"，神色大是慌張。\n"NOR);
	command("whisper " + ob->query("id")+" 我已經在燕子屋布下天羅地網，剛才探子回報，叛徒很在曼陀羅山莊"+room->query("short")+"出現過！");
	log_file("quest/TLBB", sprintf("%s(%s)為復興天下需要尋找玉璽，特此紀錄。經驗：%d。\n", ob->name(1),ob->query("id"), ob->query("combat_exp")) );
	command("addoil "+ob->query("id"));
	if(wizardp(ob)) tell_object(ob,"\n"+where+"\n");
	ob->set_temp(QUESTDIR5+"yuxi",1);
	if (random(2))		return "今天天氣就是好，就是好。";
	return "今天天氣真不錯。";
}
string ask_fenglu()
{
	object ob=this_player();
	mapping fam = ob->query("family");
	int gold = 0, fenglu;

	if ( !fam || fam["family_name"] != "姑蘇慕容")
		return "這位"+ RANK_D->query_respect(ob) +"不是我慕容弟子，此話從何說起？";
        switch ( fam["generation"] ) {
		case 2:
			gold += 500;
		case 3:
			gold += 800;
			break;
		default:
			return "這位"+ RANK_D->query_respect(ob) +"在我姑蘇慕容的身份太低，現在還沒有資格領取俸祿。";
	}
	fenglu = ob->query("age") * 12 + ob->query("month");
	if (ob->query("fenglu") >= fenglu)
		return "這位"+RANK_D->query_respect(ob) +"本月已經領過俸祿了，還是等下個月再來吧。";
	gold *= ob->query_skill("shenyuan-gong",1);
           if (ob->query_skill("shenyuan-gong", 1) < 216)  return "你這個月沒有俸祿。";
	ob->set("fenglu", fenglu);
	command ("addoil " + ob->query("id"));
	ob->add("balance", gold);
	return "你本月的俸祿"+MONEY_D->money_str(gold)+"已經存入錢莊了，但願這位"+ RANK_D->query_respect(ob) +"不要使我失望，好好幹吧！";
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BINGQI_D("sword/biyu-jian")))) {
		ob->move(this_object());
		command("wield biyu jian");
	}
}

mixed ask_sword2()
{
	object me=this_player(), weapon;

	if ( me->query("family/family_name") != "姑蘇慕容")
		return RANK_D->query_respect(me)+"與本派素無來往，不知此話從何談起？";

	if ( me->query("family/generation") > 3 )
		return "碧玉劍是本派寶物，不知道這位" + RANK_D->query_respect(me) + "打聽這個幹嘛？";

	weapon = present("biyu jian", this_object());
	if (!objectp(weapon))
		return "碧玉劍已經被人拿走了, 現在不在我手裡。";
	command("unwield biyu jian");
	command("give biyu jian to " + me->query("id"));
	return 1;
}

string ask_wang()
{
	mapping fam;

	if (!fam = this_player()->query("family") || fam["family_name"] !="姑蘇慕容")
		return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？";
	return "語嫣是我表妹，一直被姑媽管的很嚴，連我都很長時間沒有見到她了。";
}

string ask_skill()
{
	mapping fam;

	if (!(fam = this_player()->query("family"))|| fam["family_name"] != "姑蘇慕容")
		return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？";
	return "鬥轉星移是我慕容家的絕學，最是注重招架和身法。";
}

string ask_ge()
{
	mapping fam;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑蘇慕容")
		return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？";
	return "還施水閣是我慕容收藏天下秘籍之所在，在我的書……";
}

string ask_sword()
{
	mapping fam;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑蘇慕容")
		return RANK_D->query_respect(this_player()) + "與本派素無來往，不知此話從何談起？";
	return "碧玉劍是家父身後的遺物，我讓阿朱姑娘收起來好好保管！";
}

string ask_book()
{
	object me = this_player();
	object ob;

	if (me->query("family/family_name") != "姑蘇慕容")
		return RANK_D->query_respect(me) +
		"與本派素無來往，不知此話從何談起？";

	if (me->query_skill("parry",1) < 121)
		return RANK_D->query_respect(me) + "功力不夠，何以談及領悟？";
	if (present("douzhuan xingyi", me))
		return RANK_D->query_respect(me) +
		"現在身上不是有鬥轉星移的武籍了嗎？怎麼又來要了？ 真是貪得無厭！";

	ob = unew("/d/mr/obj/shu1");
	if(!clonep(ob))
		return "鬥轉星移武籍已經被別人要走了。";

	ob->move(me);

	message_vision("$N得到一本鬥轉星移的武功秘籍。\n", me);
	return "好吧，看你為慕容家忠心耿耿，這本書就賜于你吧。";
}

string ask_book2()
{
	object me = this_player();
	object ob;

	if (me->query("family/family_name") != "姑蘇慕容")
		return RANK_D->query_respect(me) +
		"與本派素無來往，不知此話從何談起？";

	if (me->query_skill("parry",1) < 121)
		return RANK_D->query_respect(this_player()) + "功力不夠，何以談及領悟？";

	if (me->query_skill("douzhuan-xingyi",1)<50)
		return RANK_D->query_respect(me) +
		"功力不夠，何以談及領取圖解？";
	if (present("douzhuan xingyi", me))
		return RANK_D->query_respect(this_player()) +
		"你現在身上不是有鬥轉星移的武籍了嘛，怎麼又來要了？ 真是貪得無厭！";

	ob = unew("/d/mr/obj/shu2");
	if (!clonep(ob))
		return "對不起，鬥轉星移的武籍已經被別人要走了。";

	ob->move(this_player());
	message_vision("$N得到一本鬥轉星移的武功秘籍。\n", me);
	return "好吧，看你為慕容家忠心耿耿，這本書就賜于你吧。";
}

mixed ask_bo()
{
	object me = this_player();
	object ob = this_object();

	if (me->query_temp("marks/失敗")) {
		message_vision(
			"$N眼中發出兩道寒光直射$n，一字一字地說道：已經較量過了，你怎麼還不回去安心練功呢！\n",
			ob, me
		);
		return 1;
	}
	if (me->query("family/family_name") != "姑蘇慕容")
		return RANK_D->query_respect(me) + "與本派素無來往，不知此話從何談起？";

	if (me->query("family/generation") != 3)
		return RANK_D->query_respect(me) + "為何開這等玩笑？";

	if (me->query_temp("marks/bai_bo"))
		return "你已經可以去見家父，不用再向我學了！";

	message_vision(
		"$N眼中發出兩道寒光直射$n，一字一字地說道：家父現在身處少林，那裡藏龍臥虎，\n"
		"你若武功未成，最好不要去自取其辱；如果你有信心，就和我較量一下。(jiaoliang)\n",
		ob, me
	);

	me->set_temp("marks/jiao", 1);
	return 1;
}

int do_jiaoliang()
{
	object me, obj, jiaxin;
	int current_qi;
	int i;

	me = this_object();
	obj = this_player();

	if (obj->query_temp("marks/jiao")) {
		message_vision("$N對$n說：好吧，那就請師父指點幾招。\n", obj, me);
		set("max_qi", 4500);
		set("jiali", 50);
		set("neili", 6500);
		set("max_neili", 4500);
		current_qi = set("qi", 4500);

		i=10;
		obj->delete_temp("marks/jiao");
		while ((obj->query("qi")*100 / (int)obj->query("max_qi")) > 30) {
			if (!present(obj, environment()))
				return 1;
			i--;
			COMBAT_D->do_attack(obj, me, obj->query_temp("weapon"), 1);
			if (!i || (me->query("qi")*100/current_qi) < 30) {
				message_vision(
					"$N對$n說道：不想我慕容世家又出良材，我這就寫封家信，你馬上動身前去少林，\n"
					"把它交給家父。希望你能不負眾望，振興慕容世家，光復大燕國。\n",
					me, obj
				);
				jiaxin = new("/d/mr/obj/jiaxin");
				jiaxin->move(obj);
				obj->set_temp("marks/bai_bo", 1);
				message_vision("$N交給$n一封家信\n", me, obj);
				return 1;
			}
			COMBAT_D->do_attack(me, obj, me->query_temp("weapon"), 1);
		}
		message_vision(
			"$N對著$n冷冷說道：你武功未成，就好高騖遠，你還是安心練功去吧！\n",
			me, obj
		);
		obj->set_temp("marks/失敗", 1);
	}
	return 1;
}

string ask_learn()
{
	int j=random(sizeof(my_skills));
	mapping skill = my_skills[j];
	int i;
	object me = this_player();

	i = 7+random(5);
	if (me->query("family/family_name") != "姑蘇慕容" && !wizardp(me)) // 必須是慕容派弟子
		return RANK_D->query_respect(me) + "與本派素無來往，不知此話從何談起？";

	if (me->query("combat_exp") > 2000000  && !wizardp(me))
		return RANK_D->query_respect(me)
		+ "你已經盡數掌握了精深奧妙的武學訣要，我可不敢勞您的大架了。";

	if (me->query_skill("parry", 1) < 100 ) // 招架必須大于等于100級
		return RANK_D->query_respect(me) +
		"于本門武學尚不能運用自如，如何談及天下之武學？";
	if (me->query_skill("douzhuan-xingyi", 1) < 100 )  // 鬥轉星移必須大于等于100級
		return RANK_D->query_respect(me) +
		"于本門武學尚不能運用自如，如何談及天下之武學？";
	if (me->query_condition("mr_job") )
		return RANK_D->query_respect(me) +"還沒完成我交給你的任務呢。";
	if (is_fighting())
		return "嚷什麼嚷，沒看見我這正忙著呢嗎？";
	if (me->query("job_name") =="慕容偷學" && !wizardp(me))
		return RANK_D->query_respect(me) +
		"先等等吧，我現在沒有什麼感興趣的武功想學。";
	if (me->query_condition("wait_mr_job", 1) > 0
	 || me->query_condition("job_busy"))
		return RANK_D->query_respect(me) +"先等等吧，我現在沒有什麼感興趣的武功想學。";

	if(!skill["skill_id"])
		return sprintf("SKILL.H文件在第%d個技能出錯，請通知巫師修改。\n",j);
	me->set_temp("skill_target", skill["skill_name"]);  // 此標記表明此次偷學目標技能的中文名字
	me->set_temp("skill_id", skill["skill_id"]); // 此標記表明此次偷學目標技能的英文名字
	me->set_temp("skill_type", skill["skill_type"]); // 此標記表明此次偷學目標技能的英文類型
	me->set_temp("skill_lvl", i); // 此標記表明此次偷學目標技能所需要的級別
	me->apply_condition("mr_job", 30+random(15)); // 設置此次任務必須在所需時間內完成;
	me->apply_condition("job_busy",10);
	command( "whisper "+me->query("id") + " 我姑蘇慕容傲視天下所有武功，但也不乏為之羨慕的。");
	command("whisper "+ me->query("id")
	+ " 好吧，"+"「"+skill["skill_name"]+"」"+"「"+skill["skill_id"]+"」我垂涎已久，你們把它學回來，我大大的有賞。");

	if ( !present("murong paper", me))
		new("/d/mr/obj/paper")->move(me);

	if (random(2))
		return "今天天氣就是好，就是好。";
	return "今天天氣真不錯。";
}

int ask_fuming(string arg)
{
	object me, ob;
	int bouns,My_exp,Target_exp,pot;
	float rate;

	me = this_player();
	ob = this_object();

	if( !arg)
	{
		command("say 你要展示什麼？");
		return 1;
	}

	if( !me->query_condition("mr_job"))
	{
		command("say 你現在沒有任務吧？");
		return 1;
	}

	if( me->is_busy())
	{
		command("say 你正忙著呢，有什麼事情呆會再說。");
		return 1;
	}

	if( me->is_fighting())
	{
		command("say 你正打架呢，有什麼事情呆會再說。");
		return 1;
	}

	if(!me->query_temp("job_done"))
	{
		command("say 你學到什麼東西了？還有臉敢回來？");
		return 1;
	}

	if( this_object()->is_fighting())
	{
		command("say 嚷什麼嚷，沒看見我這正忙著呢嗎？");
		return 1;
	}
	me->set("job_name", "慕容偷學");
/*
	Target_exp = me->query_temp("master_exp");
	My_exp= me->query("combat_exp");

	bouns = me->query_temp("skill_lvl")*5/2;
	bouns +=  me->query_skill("douzhuan-xingyi",1) * 5 / 3;

	rate = to_float(Target_exp)/to_float(My_exp);
	if (rate > 2) rate = 2;
	if (rate < 0.6) rate = 0.6;
	bouns *= rate;
             
              if (bouns > 300) bouns = 250 + random(50);		
	bouns = me->add_exp_combat(bouns,this_object(),"慕容");
	pot = bouns/5+random(bouns/10);        
	if (me->add("potential", pot) > me->query("max_pot"))
		me->set("potential", me->query("max_pot"));
	write(GRN"你獲得了"+CHINESE_D->chinese_number(bouns)+"點經驗和"+CHINESE_D->chinese_number(pot)+"點潛能的獎勵。\n"NOR);
	write(GRN"你已經為慕容世家做了"+me->query("job_time/慕容")+"次任務!\n"NOR);

	log_file("job/touxue",sprintf("%8s%-10s偷學 %s, 經驗：%3d，潛能：%2d，次%3d，目前經驗：%d。\n",
		me->name(1), "("+geteuid(me)+")", me->query_temp("skill_target"),
		bouns,pot,me->query("job_time/慕容"),me->query("combat_exp")), me);
*/
          
	message_vision(CYN"慕容復仔細研究著$N記在紙卷上的武功精要，情不自禁地說道：好一個"+me->query_temp("skill_target")+"。\n"NOR, me);
              TASKREWARD_D->get_reward(me,"慕容",0,0,0,16+ random(5),0,0,0,this_object());
	message_vision(CYN"慕容復拍了拍$N的頭，對$P說道：辛苦你了，下去休息吧。\n"NOR, me);


	me->improve_skill("douzhuan-xingyi", me->query_int()*2);

	me->delete_temp("skill_target");
	me->delete_temp("skill_id");
	me->delete_temp("skill_type");
	me->delete_temp("skill_lvl");
	me->delete_temp("job_done");

	me->clear_condition("mr_job");
	me->apply_condition("wait_mr_job", random(10)+5);

	if(present("paper", me)){
		destruct(present("paper",me));
	}
	return 1;
}

int ask_fangqi()
{
	object me=this_player(),obj;

	if( !me->query_condition("mr_job")){
		command("say 你現在沒有任務吧？");
		return 1;
	}

	command( "say 也好，那麼你先下去休息一會吧。" );
	command( "disapp");
	command( "sigh "+me->query("id"));
	obj=me->query_temp("dizi");
	if( objectp(obj) )
		destruct(obj);
	me->delete_temp("skill_target");
	me->delete_temp("skill_id");
	me->delete_temp("skill_type");
	me->delete_temp("skill_lvl");
	me->delete_temp("job_done");

	me->clear_condition("mr_job");
	me->apply_condition("wait_mr_job", random(2)+2);
	me->add("combat_exp",-(20+random(30)));
	return 1;
}

string ask_times()
{
	object ob;
	ob = this_player();
	if(!ob->query("job_time/慕容"))
		return "很遺憾，"+ob->name()+"，你好象沒有為慕容做過貢獻！";
	return ""+ob->name()+"，你已經完成了"+CHINESE_D->chinese_number((int)ob->query("job_time/慕容"))+"次慕容偷學任務！";
}

int accept_object(object who, object ob)
{
   if(userp(ob)) return 0;        
   if(ob->query("id") == "yu xi")
   {
      if(who->query_temp(QUESTDIR5+"yuxi")
		  &&!who->query(QUESTDIR5+"start")) 
	  {
      	if( ob->query("owner")==who->query("id"))
        {
           command("smile "+who->query("id"));
  	       command("whisper "+who->query("id")+" 不錯，看你如此用心，這裡有個天大的秘密可以告訴你。");
  	       command("whisper "+who->query("id")+" 二十年前，江南葉家莊葉二姑娘離奇失蹤，幾年後江湖上出現所謂四大惡人，其中一個就叫葉二娘。");
		   command("smile "+who->query("id"));
  	       command("whisper "+who->query("id")+" 沒有人想到，葉二娘就是當年葉二姑娘。而這一切罪魁禍首就是當今的少林主持玄慈！");
		   command("smoke");
  	       command("whisper "+who->query("id")+" 二十年前，還是少年的玄慈曾經夜宿葉家莊，勾引葉二姑娘，幾年後葉二姑娘更為他生下一子。");
  	       command("whisper "+who->query("id")+" 這是我們天大的機會。這個孩子就是少林三十六代弟子虛竹。他屁股上的胎記可以証明一切！！");
		   command("claw");
  	       command("whisper "+who->query("id")+" 如此一來，少林名譽掃地，之後趁丐幫蕭峰離走內亂之際滅其丐幫，之後武林便是你我的天下！");
           command("crazy");
           command("addoil "+who->query("id"));
           who->set(QUESTDIR5+"start",1);
		   log_file("quest/TLBB", sprintf("%s(%s)為復興天下找到玉璽。經驗：%d。\n", who->name(1),who->query("id"), who->query("combat_exp")) );
        }
        else
        {
           command("? "+who->query("id"));
  	       command("whisper "+who->query("id")+" 這不是你要找的玉璽，這塊你從哪裡得來的？");
  	       command("heng "+who->query("id"));
		   command("whisper "+who->query("id")+" 竟然隨便找來一塊就來胡弄我.........");
		   log_file("quest/TLBB", sprintf("%s(%s)找的玉璽不是本人的，失敗。經驗：%d。\n", who->name(1),who->query("id"), who->query("combat_exp")) );
           who->set(QUESTDIR+"time",time());
           who->set(QUESTDIR+"combat_exp",who->query("combat_exp"));
           who->delete_temp("quest/天龍八部/復興天下篇");
        }
	  }
	  else command("thank "+who->query("id"));
	  call_out("destroying", 1, ob);
	  return 1;
   }
   if(ob->query("id") == "shouji" 
	   && ob->query("kill_by")
	   && ob->query("kill_by")==who
	   && (ob->query("victim_id")=="zhang sanfeng"
	       ||ob->query("victim_id")=="zhang wuji"
		   ||ob->query("victim_id")=="kurong zhanglao"))
   {

      if(who->query_temp(QUESTDIR5+"askfu")
		  &&!who->query_temp(QUESTDIR5+"give_shouji")) 
	  {
		  command("smile "+who->query("id"));	  
		  if(ob->query("victim_id")=="zhang sanfeng")
			  command("whisper "+who->query("id")+" 不錯，武當那個老雜毛沒想到也有今天，這裡有個天大的秘密可以告訴你。");
		  if(ob->query("victim_id")=="zhang wuji")
			  command("whisper "+who->query("id")+" 不錯，明教那個小家伙沒想到也有今天，這裡有個天大的秘密可以告訴你。");
		  if(ob->query("victim_id")=="kurong zhanglao")
			  command("whisper "+who->query("id")+" 不錯，大理那個死禿子沒想到也有今天，這裡有個天大的秘密可以告訴你。");
		  command("addoil "+who->query("id"));
		  who->set_temp(QUESTDIR5+"give_shouji",1);
		  log_file("quest/TLBB", sprintf("%s(%s)為復興天下殺死一個掌門人。經驗：%d。\n", who->name(1),who->query("id"), who->query("combat_exp")) );
	  }
	  else
	  {
		  command("nod "+who->query("id"));
		  command("admire "+who->query("id"));
	  }
	  call_out("destroying", 1, ob);
	  return 1;
   }
   return 0;
}
int ask_bishen()
{
	object ob=this_player();
       mapping fam;
	int i, time;
        i = ob->query("combat_exp") - 500000;
        i /= 500000;

	time = time() - ob->query("quest/bishen/time");


      if (!(fam = this_player()->query("family")) || fam["family_name"] !="姑蘇慕容"){
		command("? " + ob->query("id"));
             command("say 你與本派素無來往，不知為何有此一問？");
             return 0;
        }
	if (ob->query("quest/bishen/pass")) {
		command("? " + ob->query("id"));
		command("say 你不是已經明白其中的奧妙了嗎？");
		return 1;
	}
	if (ob->query("quest/bishen/fail") >=3 && ob->query("registered") < 3){
		command("hmm");
		command("say 你受天資所限,看來此生無望了！");
		return 1;
	}
	if ( ob->query("quest/bishen/time") && time < 86400 ) {
		command("shake");
		command("say 你解迷時間未到,請稍後再來。");
		return 1;
	}
	if ( ob->query("quest/hubo/fail") >= i ){
		command("shake");
		command("say 你解迷時機未到,請稍後再來。");
		return 1;
	}
        if ( ob->query("combat_exp") < 1000000) {
		command("shake "+ ob->query("id"));
		command("say 這位"+RANK_D->query_respect(ob)+"你的武功過于浮躁,現在還不是告訴你的時候。");
		return 1;
	}
	if (random(ob->query("kar")) < 26 && ob->query("int") < 25){
	       command("look " + ob->query("id"));
		command("poor");
		command("say 看來你還是未到明白其中奧妙所在的時候!");
		ob->add("quest/bishen/fail", 1);
		ob->set("quest/bishen/time", time());
		log_file("quest/bishen",
			sprintf("%-18s想從慕容復處領悟鬥轉星移的精髓所在失敗，失敗%s次。\n",
				ob->name(1)+"("+capitalize(getuid(ob))+")",
				chinese_number(ob->query("quest/bishen/fail")) 
			), ob
		);
		return 1;
	}
	command("look " + ob->query("id"));
	command("nod " + ob->query("id"));
	command("say 好吧,我就將其中的奧妙告訴你吧。");
       command("chat* 縱聲長笑道：我姑蘇慕容又有一人領悟鬥轉星移精髓所在,何愁復國大業不成！");
       command("chat* yeah");
	log_file("quest/bishen",
		sprintf("%-18s失敗%s次後，成功從慕容復處領悟鬥轉星移精髓所在，福：%d，悟：%d。\n",
			ob->name(1)+"("+capitalize(getuid(ob))+")",
			chinese_number(ob->query("quest/bishen/fail")), 
			ob->query("kar"), 
			ob->query_int(1)
		), ob
	);
	ob->set("quest/bishen/pass", 1);
	ob->set("quest/bishen/exp", ob->query("combat_exp"));
	return 1;
}



void destroying(object ob)
{     
	destruct(ob);
	return;
}     

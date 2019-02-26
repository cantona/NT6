#include <ansi.h>;
inherit F_DEALER;
inherit NPC;

int ask_puti();
int ask_yuqing();
int ask_jinchuang();
int ask_yangjing();
int ask_jifeng();
int ask_jiuhua();
int ask_xieqi();
int ask_zhengqi();
int ask_longxi();
int ask_xiaoke();



void create()
{
    	set_name("胡青牛", ({ "hu qingniu", "hu", "qingniu" }));
    	set("title", YEL"蝶谷醫仙"NOR);
    	set("gender", "男性");
    	set("long", "他就是醫術高超的「蝶谷醫仙」胡青牛。\n");
    	set("age", 65);
    	set("int", 30);
    	set("qi", 1000);
    	set("max_qi", 1000);
    	set("jing", 1000);
    	set("max_jing", 1000);
    	set("shen_type", 0);
    	set("combat_exp", 500000);
    	set("attitude", "heroism");
    	set_skill("unarmed", 80);
    	set_skill("dodge", 80);
    	set_skill("parry", 60);
    	set_temp("apply/attack", 70);
    	set_temp("apply/defense", 70);
    	set_temp("apply/damage", 50);
       set("inquiry", 
	([
    		"菩提子":(:ask_puti:),
    		"玉清散":(:ask_yuqing:),
    		"金創藥":(:ask_jinchuang:),
    		"養精丹":(:ask_yangjing:),
		"九花玉露丸":(:ask_jiuhua:),
		"疾風驟雨丹":(:ask_jifeng:),
		"正人君子丹":(:ask_zhengqi:),
		"心狠手辣丹":(:ask_xieqi:),
		"龍犀百草丹":(:ask_longxi:),
		"消渴止餓丹":(:ask_xiaoke:),

       ]));
     	set("vendor_goods", 	({
     		__DIR__"axe",
     		__DIR__"blade",
     		__DIR__"yaochu",
     		__DIR__"dinglu",
                   __DIR__"bottle",
     		__DIR__"yao/huazhong",
     		__DIR__"yao/guozhong",

     	}));

    	setup();
    	carry_object("/clone/cloth/changpao")->wear();
} 
void init()
{
       add_action("do_list", "list");
       add_action("do_buy", "buy");
}

int accept_object(object who, object ob)
{
    
       if( !query("peifang", who) )
       	return notify_fail("胡青牛皺眉説道：你不是明教弟子，給我錢，我就會給你治病嗎？\n");

    	if( query("money_id", ob) && ob->value()<100000 )
    	{
	       return notify_fail("胡青牛皺眉説道：這麼一點點錢，還不夠給煉藥童子的零用呢！\n");
    	}

    	else if( query("money_id", ob) && ob->value() >= 100000 )
    	{
        	message_vision ("胡青牛説道："+RANK_D->query_respect(who)+"，上次的配方煉不出來？沒關係，我這裏的藥方還多着呢。\n");
        delete("peifang", 	who);
        delete("mubiao", 	who);
        	return 1;
    	}
    	return 0;
}


int ask_puti()
{
    	object gen, mu, cao, hua, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 200)
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，你的煉丹能力不足，不能煉製菩提子。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，我上次給你的配方煉好了嗎？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "putizi", 	who);

   	message_vision("$N露出深思的神色，對$n説道：菩提子的配方嗎？我這裏正好有一個，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"、"+query("name", hua)+"、"+query("name", guo)+"這五味藥材才能煉成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	destruct(guo);
	return 1;
}

int ask_yuqing()
{
    	object gen, mu, cao, hua, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 200)
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，你的煉丹能力不足，不能煉製玉清散。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，我上次給你的配方煉好了嗎？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "yuqingsan", 	who);


   	message_vision("$N露出深思的神色，對$n説道：玉清散的配方嗎？我這裏正好有一個，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"、"+query("name", hua)+"、"+query("name", guo)+"這五味藥材才能煉成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	destruct(guo);
	return 1;
}

int ask_yangjing()
{
    	object gen, mu;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");

	if( query("peifang", who) )
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，我上次給你的配方煉好了嗎？\n",me);
		return 1;
	}

	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);

set("peifang", peifang, 	who);
set("mubiao", "yangjing", 	who);


   	message_vision("$N露出深思的神色，對$n説道：養精丹的配方嗎？我這裏正好有一個，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"這兩味藥材才能煉成。\n",me,who);
	destruct(gen);
	destruct(mu);
	return 1;
}
int ask_jinchuang()
{
    	object gen, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	cao=new(__DIR__"/yao/caolei");

	if( query("peifang", who) )
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，我上次給你的配方煉好了嗎？\n",me);
		return 1;
	}

	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", cao);

addn("peifang", peifang, 	who);
set("mubiao", "jinchuang", 	who);


   	message_vision("$N露出深思的神色，對$n説道：金創藥的配方嗎？我這裏正好有一個，但是需要"+query("name", gen)+"、"
	+query("name", cao)+"這兩味藥材才能煉成。\n",me,who);
	destruct(gen);
	destruct(cao);
	return 1;
}

int ask_jiuhua()
{
    	object gen, mu, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");

	if((int)who->query_skill("liandan-shu",1) < 50)
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，你的煉丹能力不足，不能煉製九花玉露丸。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，我上次給你的配方煉好了嗎？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);

set("peifang", peifang, 	who);
set("mubiao", "jiuhuawan", 	who);


   	message_vision("$N露出深思的神色，對$n説道：九花玉露丸的配方嗎？我這裏正好有一個，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"這三味藥材才能煉成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	return 1;
}

int ask_jifeng()
{
    	object gen, mu, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");

	if((int)who->query_skill("liandan-shu",1) < 50)
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，你的煉丹能力不足，不能煉製疾風驟雨丹。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，我上次給你的配方煉好了嗎？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);

set("peifang", peifang, 	who);
set("mubiao", "jifengdan", 	who);


   	message_vision("$N露出深思的神色，對$n説道：疾風驟雨丹的配方嗎？我這裏正好有一個，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"這三味藥材才能煉成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	return 1;
}

int ask_zhengqi()
{
    	object gen, mu, cao, hua;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");

	if((int)who->query_skill("liandan-shu",1) < 100)
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，你的煉丹能力不足，不能煉製正人君子丹。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，我上次給你的配方煉好了嗎？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);

set("peifang", peifang, 	who);
set("mubiao", "zhengrendan", 	who);


   	message_vision("$N露出深思的神色，對$n説道：正人君子丹的配方嗎？我這裏正好有一個，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"、"+query("name", hua)+"這四味藥材才能煉成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	return 1;
}
int ask_xieqi()
{
    	object gen, mu, cao, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 100)
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，你的煉丹能力不足，不能煉製心狠手辣丹。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，我上次給你的配方煉好了嗎？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "xinhendan", 	who);


   	message_vision("$N露出深思的神色，對$n説道：心狠手辣丹的配方嗎？我這裏正好有一個，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"、"+query("name", guo)+"這四味藥材才能煉成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(guo);
	return 1;
}

int ask_longxi()
{
    	object gen, mu, cao, hua, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 200)
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，你的煉丹能力不足，不能煉製龍犀百草丹。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，我上次給你的配方煉好了嗎？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "longxidan", 	who);


   	message_vision("$N露出深思的神色，對$n説道：龍犀百草丹的配方嗎？我這裏正好有一個，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"、"+query("name", hua)+"、"+query("name", guo)+"這五味藥材才能煉成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	destruct(guo);
	return 1;
}

int ask_xiaoke()
{
    	object gen, mu, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");

	if((int)who->query_skill("liandan-shu",1) < 50)
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，你的煉丹能力不足，不能煉製消渴止餓丹。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N説道："+RANK_D->query_respect(who)+"，我上次給你的配方煉好了嗎？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);

set("peifang", peifang, 	who);
set("mubiao", "xiaokedan", 	who);


   	message_vision("$N露出深思的神色，對$n説道：消渴止餓丹的配方嗎？我這裏正好有一個，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"這三味藥材才能煉成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	return 1;
}
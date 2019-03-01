// linzhennan.c 林震南
// modified by XiaoYao 98/12/16
// Modify by Lklv 2001.10.12

#include <ansi.h>

inherit NPC;
#include "hubiao.h";

int ask_fuwei();
int ask_yuantu();
int ask_pixie();
int ask_tong();

void create()
{
	set_name("林震南", ({ "lin zhennan", "lin", "zhennan" }));
	set("gender", "男性");
	set("age", 45);
	set("long", "他就是「福威鏢局」的總鏢頭－－林震南。\n");

	set("combat_exp", 30000);
	set("shen_type", 1);

	set("max_neili", 500);
	set("jiali", 10);
	set("no_get","林震南對你來說太重了。\n");

	set_skill("force", 40);
	set_skill("sword", 50);
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("parry", 50);

	set("inquiry", ([
		"向陽老宅" : "那是我家從前的宅院，已經沒有人住了。",
		"福威鏢局" : (: ask_fuwei :),
		"遠圖公" : (: ask_yuantu :),
		"林遠圖" : "哼！小孩子這麼沒禮貌，直呼先人名諱！",
		"辟邪劍法" : (: ask_pixie:),
		"銅錢" : (: ask_tong:),
		"銅板" : (: ask_tong:),
		"押鏢" : (: test_dart :),
		"護鏢" : (: test_dart :),
		"job" : (: test_dart :),
	]) );

	set("chat_chance", 2);
	set("chat_msg", ({
		CYN"林震南說道：「這個月鏢局生意不錯！」\n"NOR,
	}) );
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/damage", 15);

	setup();
	carry_object(BINGQI_D("changjian"))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
        carry_object(ARMOR_D("shoes"))->wear();
}

int ask_fuwei()
{
	say(CYN"林震南炫耀地說：「我們林家三代走鏢，一來仗著先祖遠圖公當年闖下的威名，\n"
	"二來靠著我們林家家傳的玩藝兒不算含糊，這才有今日的局面，成為大江以南\n"
	"首屈一指的大鏢局。江湖上提到『福威鏢局』四字，誰都要翹起大拇指，說一\n"
	"聲：『好福氣！好威風！』哈哈，哈哈！」\n"NOR);
	this_player()->set_temp("marks/林1", 1);
	return 1;
}

int ask_yuantu()
{
	if (this_player()->query_temp("marks/林1")) {
		say(CYN"林震南磕一磕煙鬥，說道：「遠圖公是我的祖父，福威鏢局是他一手創辦的。\n"
		"當年祖父以七十二路辟邪劍法開創鏢局，當真是打遍黑道無敵手。其時白道上\n"
		"英雄見他太過威風，也有去找他比試武藝的，青城派掌門余觀主的師父長青子\n"
		"少年之時便在他辟邪劍法下輸了幾招。」\n"NOR);
		this_player()->set_temp("marks/林2", 1);
		return 1;
	}
	say(CYN"林震南說道：「遠圖公是我的祖父。」\n"NOR);
	return 1;
}

int ask_pixie()
{
	int p1, p2, p3, p4;

	if (this_player()->query("combat_exp") < 100000) {
		message_vision(CYN"$N勃然大怒，喝道：「你也窺視我們林家的辟邪劍譜？！我跟你拼了！」\n" NOR, this_object());
		kill_ob(this_player());
	} 
	else {
		if (this_player()->query("quest/pixie/pxj_passwd"))
			say(CYN"林震南不悅地說道：「我不是都告訴你了嗎？我的劍法不及先祖。」\n"NOR);
		else if (this_player()->query_temp("marks/林2")) {
			say(CYN"林震南一驚，說道：「你怎麼知道的？噢，我剛才說露嘴了。嗨，在下的功夫\n"
			"外人不知底細，其實及不上先祖。」\n"NOR);
			write(CYN"林震南頓一頓，接著低聲說道：「先祖去世前，曾給家父留下");
			p1=random(4)+1;
			p2=random(4)+1;
			p3=random(4)+1;
			p4=random(4)+1;
			this_player()->set("quest/pixie/pxj_passwd", p1*1000+p2*100+p3*10+p4);
			write(chinese_number(this_player()->query("quest/pixie/pxj_passwd")));
			write("\n個銅錢，我一直未解其中奧秘。」\n"NOR);
		}
		else {
			message_vision(CYN"$N勃然大怒，喝道：「你也窺視我們林家的辟邪劍譜？！我跟你拼了！」\n" NOR,this_object());
			kill_ob(this_player());
		}
		this_player()->delete_temp("marks/林1");
		this_player()->delete_temp("marks/林2");
	}
	return 1;
}

int ask_tong()
{
	int p;

	if (!(p=this_player()->query("quest/pixie/pxj_passwd")))
		say(CYN"林震南一臉譏笑的樣子，說：「怎麼混到這一步了到處要錢？」\n"NOR);
	else {
		write(CYN"林震南低聲說：「先祖去世前，曾給家父留下");
 		write(chinese_number(p));
 		write("個銅錢，我一直\n未解其中奧秘。」\n"NOR);
	}
	return 1;
}

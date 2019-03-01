// zhang3.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int do_skills(string arg);
int do_join(string arg);

void create()
{
	set_name("章老三", ({ "zhang laosan", "zhang" }));
	set("title", HIY"神龍教"NOR"小頭目");
	set("gender", "男性");
	set("age", 44);
	set("str", 25);
	set("dex", 20);
	set("long", "這是一個乾瘦老頭，一雙小眼睛賊閃發光。\n");
	set("combat_exp", 25000);
	set("score", 2000);
	set("shen_type", -1);
	set("attitude", "peaceful");

	set_skill("force", 50);
	set_skill("unarmed", 70);
	set_skill("dodge", 70);
	set_skill("parry", 70);
	set_skill("yixingbu", 40);
	set_skill("shenlong-bashi", 50);
	map_skill("parry", "shenlong-bashi");
	map_skill("dodge", "yixingbu");

	set_temp("apply/attack", 15);
	set_temp("apply/defense", 15);
	set_temp("apply/armor", 10);
	set_temp("apply/damage", 10);
	set("neili", 500); 
	set("max_neili", 500);
	set("jiali", 10);
	set("inquiry", ([
		"神龍教" : "一般人是入不了我神龍教的(join shenlongjiao)。",
		"入教"   : "一般人是入不了我神龍教的(join shenlongjiao)。",
		"洪安通" : "教主脾氣不好，要討他歡心才好。",
		"教主"   : "教主脾氣不好，要討他歡心才好。",
		"口號"   : "萬年不老！永享仙福！壽與天齊！文武仁聖！",
	]));
	set("chat_msg", ({
"章老三高聲叫道：教主寶訓，時刻在心，建功克敵，無事不成！\n",
"章老三高聲叫道：眾志齊心可成城，威震天下無比倫！\n",
"章老三高聲叫道：神龍飛天齊仰望，教主聲威蓋八方！\n",
"章老三高聲叫道：乘風破浪逞英豪，教主如同日月光！\n",
"章老三高聲叫道：教主永享仙福，壽與天齊！\n",
	}) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_join", "join");
}

#include "/kungfu/class/shenlong/shenlong.h"
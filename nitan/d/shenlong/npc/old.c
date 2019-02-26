// old.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("老者", ({"old man", "old", "man"}));
	set("title",HIY "神龍教" NOR "老者");
	set("long", @LONG
這是一個神龍教老者，太陽穴高聳，兩眼炯炯有神，顯然武功甚高。
然而神色鬱郁，對一幫年輕男女頗為有禮，似乎害怕什麼，樣子十分可憐。
LONG );
	set("gender", "男性");
	set("attitude", "peaceful");

	set("age", 30 + random(50));

	set("shen_type", -1);

	set("str", 25 + random(10));
	set("dex", 25 + random(10));

	set("max_qi", 800 + random(800));
	set("max_jing", 400 + random(400));
	set("max_neili", 1000 + random(1000));
	set("jiaji", 15 + random(15));
	set("combat_exp", 50000 + random(50000));

	set_skill("force", 80);
	set_skill("dodge", 80);
	set_skill("unarmed", 80);
	set_skill("parry", 80);
	set_skill("sword", 80);

	set_temp("apply/damage", 20);
	set_temp("apply/defense", 20);

	setup();
	carry_object("/d/shenlong/obj/xionghuang")->wield();
	carry_object("/clone/misc/cloth")->wear();
}

#include "sldizi.h"
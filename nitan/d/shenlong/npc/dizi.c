// dizi.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("弟子", ({"dizi"}));
	set("title", HIY"神龍教"NOR);
	set("long",
	        "這是一個神龍教弟子，混身透着一股邪氣。\n"
	);

	set("gender", "男性");
	set("attitude", "peaceful");

	set("age", 20 + random(30));
	set("shen_type", -1);
	set("str", 25 + random(10));
	set("dex", 25 + random(10));
	set("max_qi", 200);
	set("max_jing", 150);
	set("neili", 200);
	set("max_neili", 200);
	set("jiaji", 5 + random(5));
	set("combat_exp", 10000 + random(10000));

	set_skill("force", 40);
	set_skill("dodge", 40);
	set_skill("unarmed", 40);
	set_skill("parry", 40);
	set_skill("sword", 50);
	set_skill("blade", 50);
        set("chat_chance", 3);
        set("chat_msg", ({
"年輕弟子忽然高聲叫道：教主寶訓，時刻在心，建功克敵，無事不成！\n",
"年輕弟子忽然齊聲叫道：眾志齊心可成城，威震天下無比倫！\n",
"年輕弟子忽然齊聲叫道：神龍飛天齊仰望，教主聲威蓋八方！\n",
"年輕弟子忽然齊聲叫道：乘風破浪逞英豪，教主如同日月光！\n",
"年輕弟子齊聲叫道：教主永享仙福，壽與天齊！\n",
        }) );

	setup();
        carry_object("/d/shenlong/obj/xionghuang")->wield();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
}

#include "sldizi.h"
// majiajun.c 馬家駿

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("馬家駿", ({ "ma jiajun", "ma", "jiajun"}));
        set("gender", "男性");
        set("age", 35);
        set("long", 
"他一張臉胡子剃得精光，面目頗為英俊，在時明時暗的
火把光芒下，看來一片慘白，全無血色。他就是暗算師
父瓦耳拉齊後避仇哈薩克部，裝扮成計爺爺的馬家俊。\n");
        set("combat_exp", 50000);
        set("shen_type", 1);

        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 10);

        set_skill("force", 40);
        set_skill("sword", 50);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);

        set("inquiry", ([
                "李文秀" : "你問的是阿秀吧。\n",
        ]) );

        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);

        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

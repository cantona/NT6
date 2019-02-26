// jingxuan.c

inherit NPC;

void create()
{
        set_name("淨玄", ({"jing xuan", "monk" }));
        set("title","寶象寺長老");
        set("gender", "男性");
        set("age", 80);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 30);
        set("int", 30);
        set("max_qi", 700);
        set("max_jing", 700);
        set("neili", 800);
        set("max_neili", 800);
        set("jiali", 30);
        set("max_jingli", 800);
        set("jingli", 800);
        set("combat_exp", 120000);
        set_skill("unarmed", 70);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set_skill("force", 70);

        setup();
        carry_object("/d/changan/npc/obj/sengpao")->wear();
}

int accept_fight(object me)
{
        command("say 這位"+ RANK_D->query_respect(me) +
                "你我無冤無仇，這樣又是何必呢？");        
        return 0;
}
// shi.c 史青山

inherit NPC;

void create()
{
        set_name("史青山", ({ "shi qingshan", "shi" }));
        set("title", "揚州守將");
        set("gender", "男性");
        set("age", 33);
        set("str", 25);
        set("dex", 16);
        set("long", "史青山曾經是武當山的俗家弟子，不知為何吃上了朝廷飯。\n");
        set("combat_exp", 200000);
        set("shen_type", 1);
        set("attitude", "heroism");

        set_skill("unarmed", 70);
        set_skill("force", 70);
        set_skill("sword", 70);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set_skill("taiji-jian", 50);
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/damage", 20);

        set("max_qi", 700);
        set("neili", 700); 
        set("max_neili", 700);
        set("jiali", 20);

        setup();
        carry_object("/d/city/npc/obj/gangjian")->wield();
        carry_object("/d/city/npc/obj/tiejia")->wear();
}

int accept_fight(object me)
{
        command("say 老夫久未和江湖人動手過招了，今日也不想破例。");
        return 0;
}
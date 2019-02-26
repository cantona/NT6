// yuhuan.c 程玉環 

inherit NPC;

void create()
{
        set_name("程玉環", ({ "cheng yuhuan", "cheng", "yuhuan" }));
        set("long", 
                "她就是程知府的獨生女兒，長得如花似玉，貌賽天仙的程玉環。\n"
                "據説她曾經在武當門下學過劍法。\n");
                
        set("title", "知府千金");
        set("nickname", "玉仙姑");
        set("gender", "女性");
        set("age", 18);
        set("shen_type", 1);

        set("neili", 400);
        set("max_neili", 400);
        set("max_qi", 400);
        set("max_jing", 200);
        set("jiali", 10);

        set_skill("force", 50);
        set_skill("unarmed", 40);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_skill("sword", 60);
        set_skill("taiji-jian", 40);
        map_skill("sword", "taiji-jian");
        map_skill("parry", "taiji-jian");

        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 15);

        set("combat_exp", 50000);

        setup();
        carry_object("/d/city/npc/obj/goldring")->wear();
        carry_object("/d/city/npc/obj/necklace")->wear();
        carry_object("/d/city/npc/obj/changjian")->wield();
        carry_object("/d/city/npc/obj/pink_cloth")->wear();
        carry_object("/d/city/npc/obj/flower_shoe")->wear();
}
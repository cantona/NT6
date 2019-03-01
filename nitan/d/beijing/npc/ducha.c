inherit NPC;

void create()
{
        set_name("城門督察", ({ "du cha", "du", "cha" }));
        set("long",
                "一個身材高大、滿臉橫肉的督察，城門便是由\n"
              "他負責監守。\n");
        set("gender", "男性");
        set("age", 42);
        set("attitude", "heroism");
        set("shen_type", 1);

        set("str", 30);
        set("int", 30);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 500);
        set("max_jing", 500);
        set("neili", 400);
        set("max_neili", 400);

        set("combat_exp", 50000);

        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("unarmed", 80);
        set_skill("parry", 80);
        set_skill("sword", 80);

        setup();
        carry_object("/d/beijing/npc/obj/sword4")->wield();
        carry_object("/d/beijing/npc/obj/guanfu5")->wear();
}
